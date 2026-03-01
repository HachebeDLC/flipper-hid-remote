#include "gui_manager.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
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
    manager->packets_received++;
    if (manager->ble_buffer_size > 0) {
        manager->last_byte = manager->ble_buffer[0];
    }
    
    char buf[16];
    snprintf(buf, sizeof(buf), "Pkts: %lu", manager->packets_received);
    variable_item_set_current_value_text(manager->ble_status_item, buf);
    
    snprintf(buf, sizeof(buf), "0x%02X", manager->last_byte);
    variable_item_set_current_value_text(manager->last_byte_item, buf);
    
    // HUGE DATA INDICATOR
    submenu_set_header(manager->submenu, "DATA RECEIVED!");

    furi_hal_vibro_on(true);
    furi_delay_ms(10);
    furi_hal_vibro_on(false);

    FlipperProtocolParse(manager->ble_buffer, manager->ble_buffer_size);
    
    return true;
  }
  return false;
}

void GuiManagerHandleBleData(GuiManager* manager, const uint8_t* data, size_t size) {
  furi_assert(manager);
  if (size == 0) return;

  size_t to_copy = size > sizeof(manager->ble_buffer) ? sizeof(manager->ble_buffer) : size;
  memcpy(manager->ble_buffer, data, to_copy);
  manager->ble_buffer_size = to_copy;
  
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
  view_dispatcher_free(manager->view_dispatcher);
  furi_record_close(RECORD_GUI);
  free(manager);
}

void GuiManagerShowMenu(GuiManager* manager) {
  furi_assert(manager);
  view_dispatcher_switch_to_view(manager->view_dispatcher, GuiManagerViewMenu);
}
