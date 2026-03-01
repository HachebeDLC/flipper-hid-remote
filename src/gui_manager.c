#include "gui_manager.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_vibro.h>
#include <storage/storage.h>
#include <dialogs/dialogs.h>

typedef enum {
  GuiManagerViewMenu,
  GuiManagerViewStatus,
  GuiManagerViewSettings,
} GuiManagerView;

typedef enum {
  GuiManagerEventStartRemote = 0,
  GuiManagerEventOpenSettings = 1,
  GuiManagerEventBleDataReceived = 100,
} GuiManagerEvent;

static uint32_t StatusViewBackCallback(void* context) {
  UNUSED(context);
  FlipperBleListenerStop();
  FlipperUsbHidDeinit();
  return GuiManagerViewMenu;
}

static uint32_t SettingsViewBackCallback(void* context) {
  UNUSED(context);
  return GuiManagerViewMenu;
}

static void SubmenuCallback(void* context, uint32_t index) {
  GuiManager* manager = context;
  view_dispatcher_send_custom_event(manager->view_dispatcher, index);
}

static void LayoutChangeCallback(VariableItem* item) {
    GuiManager* manager = variable_item_get_context(item);
    
    DialogsFileBrowserOptions browser_options;
    dialog_file_browser_set_basic_options(&browser_options, ".kl", NULL);
    browser_options.base_path = "/ext/badusb/assets/layouts";

    FuriString* path = furi_string_alloc();
    furi_string_set(path, "/ext/badusb/assets/layouts");

    if (dialog_file_browser_show(manager->dialogs, path, path, &browser_options)) {
        if (FlipperHidLayoutLoadFile(furi_string_get_cstr(path))) {
            size_t last_slash = furi_string_search_rchar(path, '/');
            const char* filename = (last_slash != FURI_STRING_FAILURE) ? 
                furi_string_get_cstr(path) + last_slash + 1 : furi_string_get_cstr(path);
            variable_item_set_current_value_text(item, filename);
        } else {
            variable_item_set_current_value_text(item, "Load Fail");
        }
    }
    furi_string_free(path);
}

static bool CustomEventCallback(void* context, uint32_t event) {
  GuiManager* manager = context;
  if (event == GuiManagerEventStartRemote) { 
    FlipperBleListenerStart(manager);
    FlipperUsbHidInit();
    view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewStatus);
    return true;
  } else if (event == GuiManagerEventOpenSettings) {
    view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewSettings);
    return true;
  } else if (event == GuiManagerEventBleDataReceived) {
    uint8_t packet[3];
    char buf[32];
    
    while (furi_message_queue_get(manager->command_queue, packet, 0) == FuriStatusOk) {
        manager->packets_received++;
        manager->last_byte = packet[1];
        
        size_t packet_len = (packet[0] == 0x02) ? 3 : 2;
        
        if (packet[0] == 0x02) {
            snprintf(buf, sizeof(buf), "Mouse: %d, %d", (int8_t)packet[1], (int8_t)packet[2]);
            variable_item_set_current_value_text(manager->last_byte_item, buf);
        } else {
            snprintf(buf, sizeof(buf), "0x%02X", manager->last_byte);
            variable_item_set_current_value_text(manager->last_byte_item, buf);
        }
        
        FlipperProtocolParse(packet, packet_len);
    }

    snprintf(buf, sizeof(buf), "Pkts: %lu", manager->packets_received);
    variable_item_set_current_value_text(manager->ble_status_item, buf);

    furi_hal_vibro_on(true);
    furi_delay_ms(10);
    furi_hal_vibro_on(false);

    FlipperBleNotifyEmpty();
    return true;
  }
  return false;
}

void GuiManagerHandleBleData(GuiManager* manager, const uint8_t* data, size_t size) {
  furi_assert(manager);
  if (size < 2) return;

  uint8_t packet_to_queue[3] = {0};
  size_t to_copy = (size > 3) ? 3 : size;
  memcpy(packet_to_queue, data, to_copy);

  furi_message_queue_put(manager->command_queue, packet_to_queue, 0);
  view_dispatcher_send_custom_event(manager->view_dispatcher, GuiManagerEventBleDataReceived);
}

static uint32_t MenuBackCallback(void* context) {
  UNUSED(context);
  return VIEW_NONE;
}

GuiManager* GuiManagerAlloc(void) {
  GuiManager* manager = calloc(1, sizeof(GuiManager));
  FlipperHidLayoutLoadDefault();
  
  manager->gui = furi_record_open(RECORD_GUI);
  manager->dialogs = furi_record_open(RECORD_DIALOGS);
  
  manager->view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_attach_to_gui(manager->view_dispatcher, manager->gui, ViewDispatcherTypeFullscreen);
  view_dispatcher_set_event_callback_context(manager->view_dispatcher, manager);
  view_dispatcher_set_custom_event_callback(manager->view_dispatcher, CustomEventCallback);

  manager->command_queue = furi_message_queue_alloc(16, 3);
  
  manager->submenu = submenu_alloc();
  submenu_set_header(manager->submenu, "HID Remote");
  submenu_add_item(manager->submenu, "Start Remote", GuiManagerEventStartRemote, SubmenuCallback, manager);
  submenu_add_item(manager->submenu, "Layout Settings", GuiManagerEventOpenSettings, SubmenuCallback, manager);
  view_set_previous_callback(submenu_get_view(manager->submenu), MenuBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewMenu, submenu_get_view(manager->submenu));
  
  manager->variable_item_list = variable_item_list_alloc();
  manager->ble_status_item = variable_item_list_add(manager->variable_item_list, "BLE", 0, NULL, NULL);
  variable_item_set_current_value_text(manager->ble_status_item, "Pkts: 0");
  manager->last_byte_item = variable_item_list_add(manager->variable_item_list, "Last", 0, NULL, NULL);
  variable_item_set_current_value_text(manager->last_byte_item, "0x00");
  view_set_previous_callback(variable_item_list_get_view(manager->variable_item_list), StatusViewBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewStatus, variable_item_list_get_view(manager->variable_item_list));

  manager->settings_list = variable_item_list_alloc();
  manager->layout_item = variable_item_list_add(manager->settings_list, "Layout", 0, LayoutChangeCallback, manager);
  variable_item_set_current_value_text(manager->layout_item, "US (Default)");
  view_set_previous_callback(variable_item_list_get_view(manager->settings_list), SettingsViewBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewSettings, variable_item_list_get_view(manager->settings_list));
  
  return manager;
}

void GuiManagerFree(GuiManager* manager) {
  furi_assert(manager);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewMenu);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewStatus);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewSettings);
  
  submenu_free(manager->submenu);
  variable_item_list_free(manager->variable_item_list);
  variable_item_list_free(manager->settings_list);
  furi_message_queue_free(manager->command_queue);
  view_dispatcher_free(manager->view_dispatcher);
  furi_record_close(RECORD_DIALOGS);
  furi_record_close(RECORD_GUI);
  free(manager);
}

void GuiManagerShowMenu(GuiManager* manager) {
  furi_assert(manager);
  view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewMenu);
}
