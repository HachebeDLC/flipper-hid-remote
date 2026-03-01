#include "gui_manager.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_vibro.h>

typedef enum {
  GuiManagerViewMenu,
  GuiManagerViewStatus,
} GuiManagerView;

typedef enum {
  GuiManagerEventStartRemote = 0,
  GuiManagerEventBleDataReceived = 100,
} GuiManagerEvent;

static uint32_t StatusViewBackCallback(void* context) {
  UNUSED(context);
  FlipperBleListenerStop();
  FlipperUsbHidDeinit();
  return GuiManagerViewMenu;
}

static void SubmenuCallback(void* context, uint32_t index) {
  GuiManager* manager = context;
  view_dispatcher_send_custom_event(manager->view_dispatcher, index);
}

static bool CustomEventCallback(void* context, uint32_t event) {
  GuiManager* manager = context;
  if (event == GuiManagerEventStartRemote) { 
    FlipperBleListenerStart(manager);
    FlipperUsbHidInit();
    view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewStatus);
    return true;
  } else if (event == GuiManagerEventBleDataReceived) {
    uint8_t packet[2];
    // Pull ALL pending packets from the queue
    while (furi_message_queue_get(manager->command_queue, packet, 0) == FuriStatusOk) {
        manager->packets_received++;
        manager->last_byte = packet[1];
        
        // Process HID injection
        FlipperProtocolParse(packet, 2);
    }

    // Update Screen
    char buf[32];
    snprintf(buf, sizeof(buf), "Pkts: %lu", manager->packets_received);
    variable_item_set_current_value_text(manager->ble_status_item, buf);
    
    // Show translated code for the very last byte received
    uint16_t hid_key = TranslateToSpanish((char)manager->last_byte);
    snprintf(buf, sizeof(buf), "'%c' -> HID 0x%02X", (char)manager->last_byte, (uint8_t)(hid_key & 0xFF));
    variable_item_set_current_value_text(manager->last_byte_item, buf);

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

  // Push the 2-byte command packet into the queue
  furi_message_queue_put(manager->command_queue, data, 0);
  
  view_dispatcher_send_custom_event(manager->view_dispatcher, GuiManagerEventBleDataReceived);
}

static uint32_t MenuBackCallback(void* context) {
  UNUSED(context);
  return VIEW_NONE;
}

GuiManager* GuiManagerAlloc(void) {
  GuiManager* manager = calloc(1, sizeof(GuiManager));
  
  manager->gui = furi_record_open(RECORD_GUI);
  manager->view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_attach_to_gui(manager->view_dispatcher, manager->gui, ViewDispatcherTypeFullscreen);
  view_dispatcher_set_event_callback_context(manager->view_dispatcher, manager);
  view_dispatcher_set_custom_event_callback(manager->view_dispatcher, CustomEventCallback);

  // Initialize command queue (stores 2-byte packets)
  manager->command_queue = furi_message_queue_alloc(16, 2);
  
  manager->submenu = submenu_alloc();
  submenu_set_header(manager->submenu, "HID Remote");
  submenu_add_item(manager->submenu, "Start Remote", 0, SubmenuCallback, manager);
  submenu_add_item(manager->submenu, "Settings", 1, SubmenuCallback, manager);
  
  view_set_previous_callback(submenu_get_view(manager->submenu), MenuBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewMenu, submenu_get_view(manager->submenu));
  
  manager->variable_item_list = variable_item_list_alloc();
  manager->ble_status_item = variable_item_list_add(manager->variable_item_list, "BLE", 0, NULL, NULL);
  variable_item_set_current_value_text(manager->ble_status_item, "Pkts: 0");
  
  manager->last_byte_item = variable_item_list_add(manager->variable_item_list, "Last", 0, NULL, NULL);
  variable_item_set_current_value_text(manager->last_byte_item, "0x00");
  
  view_set_previous_callback(variable_item_list_get_view(manager->variable_item_list), StatusViewBackCallback);
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewStatus, variable_item_list_get_view(manager->variable_item_list));
  
  return manager;
}

void GuiManagerFree(GuiManager* manager) {
  furi_assert(manager);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewMenu);
  view_dispatcher_remove_view(manager->view_dispatcher, GuiManagerViewStatus);
  submenu_free(manager->submenu);
  variable_item_list_free(manager->variable_item_list);
  
  furi_message_queue_free(manager->command_queue);
  
  view_dispatcher_free(manager->view_dispatcher);
  furi_record_close(RECORD_GUI);
  free(manager);
}

void GuiManagerShowMenu(GuiManager* manager) {
  furi_assert(manager);
  view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewMenu);
}
