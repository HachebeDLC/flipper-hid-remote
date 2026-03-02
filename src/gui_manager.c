#include "gui_manager.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
#include "hid_injector.h"
#include "settings.h"
#include <furi.h>
#include <furi_hal_vibro.h>
#include <furi_hal_power.h>
#include <storage/storage.h>
#include <dialogs/dialogs.h>
#include <string.h>

#define TAG "GuiManager"

typedef enum {
  GuiManagerViewMenu,
  GuiManagerViewStatus,
  GuiManagerViewSettings,
} GuiManagerView;

typedef enum {
  GuiManagerEventStartRemote = 0,
  GuiManagerEventOpenSettings = 1,
  GuiManagerEventBleDataReceived = 100,
  GuiManagerEventLoadLayout = 10,
} GuiManagerEvent;

static uint32_t ViewBackToMenuCallback(void* context) {
  UNUSED(context);
  return GuiManagerViewMenu;
}

static uint32_t StatusViewBackCallback(void* context) {
  FURI_LOG_D(TAG, "StatusViewBackCallback triggered");
  UNUSED(context);
  FlipperBleListenerStop();
  FlipperUsbHidDeinit();
  return GuiManagerViewMenu;
}

static uint32_t MenuBackCallback(void* context) {
  FURI_LOG_D(TAG, "MenuBackCallback triggered");
  UNUSED(context);
  return VIEW_NONE;
}

static void SubmenuCallback(void* context, uint32_t index) {
  GuiManager* manager = context;
  view_dispatcher_send_custom_event(manager->view_dispatcher, index);
}

static const char* get_layout_display_name(const char* path) {
    if (strcmp(path, "default") == 0) return "US (Default)";
    const char* last_slash = strrchr(path, '/');
    return last_slash ? last_slash + 1 : path;
}

static void VibroChangeCallback(VariableItem* item) {
    GuiManager* manager = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    manager->config.vibro_enabled = (index == 1);
    variable_item_set_current_value_text(item, manager->config.vibro_enabled ? "ON" : "OFF");
    FlipperKbConfigSave(&manager->config);
}

static void AccelChangeCallback(VariableItem* item) {
    GuiManager* manager = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    manager->config.accel_enabled = (index == 1);
    variable_item_set_current_value_text(item, manager->config.accel_enabled ? "ON" : "OFF");
    FlipperKbConfigSave(&manager->config);
}

static uint8_t current_modifiers_mask = 0;

static bool CustomEventCallback(void* context, uint32_t event) {
  GuiManager* manager = context;
  if (event == GuiManagerEventStartRemote) { 
    FURI_LOG_I(TAG, "Starting Remote View...");
    FlipperBleListenerStart(manager);
    FlipperUsbHidInit();
    view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewStatus);
    return true;
  } else if (event == GuiManagerEventOpenSettings) {
    FURI_LOG_I(TAG, "Opening Settings View...");
    view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewSettings);
    return true;
  } else if (event == GuiManagerEventLoadLayout) {
    DialogsFileBrowserOptions browser_options;
    dialog_file_browser_set_basic_options(&browser_options, ".kl", NULL);
    browser_options.base_path = "/ext/badusb/assets/layouts";
    FuriString* path = furi_string_alloc();
    furi_string_set(path, "/ext/badusb/assets/layouts");
    
    if (dialog_file_browser_show(manager->dialogs, path, path, &browser_options)) {
        if (FlipperHidLayoutLoadFile(furi_string_get_cstr(path))) {
            strncpy(manager->config.layout_path, furi_string_get_cstr(path), sizeof(manager->config.layout_path));
            FlipperKbConfigSave(&manager->config);
            char menu_buf[64];
            snprintf(menu_buf, sizeof(menu_buf), "Layout: %s", get_layout_display_name(manager->config.layout_path));
            submenu_change_item_label(manager->submenu, 2, menu_buf);
        }
    }
    furi_string_free(path);
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
        } else if (packet[0] == 0x05) {
            current_modifiers_mask = packet[1];
            snprintf(buf, sizeof(buf), "Mods: 0x%02X", current_modifiers_mask);
            variable_item_set_current_value_text(manager->last_byte_item, buf);
        } else {
            snprintf(buf, sizeof(buf), "0x%02X", manager->last_byte);
            variable_item_set_current_value_text(manager->last_byte_item, buf);
        }
        
        // FURI_LOG_D(TAG, "Parsing packet type 0x%02X", packet[0]);
        FlipperProtocolParse(packet, packet_len);
    }
    snprintf(buf, sizeof(buf), "Pkts: %lu", manager->packets_received);
    variable_item_set_current_value_text(manager->ble_status_item, buf);
    
    FuriString* header_str = furi_string_alloc();
    furi_string_set(header_str, "HID:");
    if (current_modifiers_mask & 0x01) furi_string_cat(header_str, " ^");
    if (current_modifiers_mask & 0x02) furi_string_cat(header_str, " S");
    if (current_modifiers_mask & 0x04) furi_string_cat(header_str, " A");
    if (current_modifiers_mask & 0x08) furi_string_cat(header_str, " G");
    if (current_modifiers_mask == 0) furi_string_cat(header_str, " Ready");
    variable_item_set_current_value_text(manager->ble_status_item, furi_string_get_cstr(header_str));
    furi_string_free(header_str);

    if (manager->config.vibro_enabled) {
        furi_hal_vibro_on(true); furi_delay_ms(10); furi_hal_vibro_on(false);
    }
    FlipperBleNotifyEmpty();
    return true;
  }
  return false;
}

void GuiManagerHandleBleData(GuiManager* manager, const uint8_t* data, size_t size) {
  if (size < 2) return;
  uint8_t packet[3] = {0};
  memcpy(packet, data, size > 3 ? 3 : size);
  furi_message_queue_put(manager->command_queue, packet, 0);
  view_dispatcher_send_custom_event(manager->view_dispatcher, GuiManagerEventBleDataReceived);
}

GuiManager* GuiManagerAlloc(void) {
  FURI_LOG_D(TAG, "Allocating GuiManager...");
  GuiManager* manager = calloc(1, sizeof(GuiManager));
  FlipperKbConfigLoad(&manager->config);
  if (strcmp(manager->config.layout_path, "default") == 0 || !FlipperHidLayoutLoadFile(manager->config.layout_path)) {
      FlipperHidLayoutLoadDefault();
  }
  manager->gui = furi_record_open(RECORD_GUI);
  manager->dialogs = furi_record_open(RECORD_DIALOGS);
  manager->view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_attach_to_gui(manager->view_dispatcher, manager->gui, ViewDispatcherTypeFullscreen);
  view_dispatcher_set_event_callback_context(manager->view_dispatcher, manager);
  view_dispatcher_set_custom_event_callback(manager->view_dispatcher, CustomEventCallback);
  manager->command_queue = furi_message_queue_alloc(16, 3);
  
  manager->submenu = submenu_alloc();
  submenu_set_header(manager->submenu, "HID Bridge");
  submenu_add_item(manager->submenu, "Start Remote", GuiManagerEventStartRemote, SubmenuCallback, manager);
  submenu_add_item(manager->submenu, "Settings", GuiManagerEventOpenSettings, SubmenuCallback, manager);
  char layout_buf[64];
  snprintf(layout_buf, sizeof(layout_buf), "Layout: %s", get_layout_display_name(manager->config.layout_path));
  submenu_add_item(manager->submenu, layout_buf, GuiManagerEventLoadLayout, SubmenuCallback, manager);
  view_set_previous_callback(submenu_get_view(manager->submenu), MenuBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewMenu, submenu_get_view(manager->submenu));
  
  manager->variable_item_list = variable_item_list_alloc();
  manager->ble_status_item = variable_item_list_add(manager->variable_item_list, "Status", 0, NULL, NULL);
  variable_item_set_current_value_text(manager->ble_status_item, "Ready");
  manager->last_byte_item = variable_item_list_add(manager->variable_item_list, "Last", 0, NULL, NULL);
  variable_item_set_current_value_text(manager->last_byte_item, "0x00");
  view_set_previous_callback(variable_item_list_get_view(manager->variable_item_list), StatusViewBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewStatus, variable_item_list_get_view(manager->variable_item_list));

  manager->settings_input = variable_item_list_alloc();
  manager->vibro_item = variable_item_list_add(manager->settings_input, "Vibration", 2, VibroChangeCallback, manager);
  variable_item_set_current_value_index(manager->vibro_item, manager->config.vibro_enabled ? 1 : 0);
  variable_item_set_current_value_text(manager->vibro_item, manager->config.vibro_enabled ? "ON" : "OFF");
  manager->accel_item = variable_item_list_add(manager->settings_input, "Mouse Accel", 2, AccelChangeCallback, manager);
  variable_item_set_current_value_index(manager->accel_item, manager->config.accel_enabled ? 1 : 0);
  variable_item_set_current_value_text(manager->accel_item, manager->config.accel_enabled ? "ON" : "OFF");
  VariableItem* batt = variable_item_list_add(manager->settings_input, "Battery", 0, NULL, NULL);
  char batt_str[16]; snprintf(batt_str, 16, "%d%%", furi_hal_power_get_pct());
  variable_item_set_current_value_text(batt, batt_str);
  view_set_previous_callback(variable_item_list_get_view(manager->settings_input), ViewBackToMenuCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewSettings, variable_item_list_get_view(manager->settings_input));
  FURI_LOG_D(TAG, "GuiManager allocation complete.");
  return manager;
}

void GuiManagerFree(GuiManager* manager) {
  FURI_LOG_D(TAG, "Freeing GuiManager...");
  furi_assert(manager);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewMenu);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewStatus);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewSettings);
  submenu_free(manager->submenu);
  variable_item_list_free(manager->variable_item_list);
  variable_item_list_free(manager->settings_input);
  furi_message_queue_free(manager->command_queue);
  view_dispatcher_free(manager->view_dispatcher);
  furi_record_close(RECORD_DIALOGS); furi_record_close(RECORD_GUI);
  free(manager);
  FURI_LOG_D(TAG, "GuiManager freed.");
}

void GuiManagerShowMenu(GuiManager* manager) {
  view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewMenu);
}
