#include "gui_manager.h"
#include <furi.h>

typedef enum {
  GuiManagerViewMenu,
  GuiManagerViewStatus,
} GuiManagerView;

static void SubmenuCallback(void* context, uint32_t index) {
  UNUSED(context);
  UNUSED(index);
  // Handle menu selection
}

GuiManager* GuiManagerAlloc(void) {
  GuiManager* manager = malloc(sizeof(GuiManager));
  
  // Initialize GUI
  manager->gui = furi_record_open(RECORD_GUI);
  
  // Initialize View Dispatcher
  manager->view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_attach_to_gui(manager->view_dispatcher, manager->gui, ViewDispatcherTypeFullscreen);
  
  // Initialize Submenu
  manager->submenu = submenu_alloc();
  submenu_set_header(manager->submenu, "HID Remote");
  submenu_add_item(manager->submenu, "Start Remote", 0, SubmenuCallback, manager);
  submenu_add_item(manager->submenu, "Settings", 1, SubmenuCallback, manager);
  
  view_dispatcher_add_view(manager->view_dispatcher, GuiManagerViewMenu, submenu_get_view(manager->submenu));
  
  // Initialize Status View (using VariableItemList for now as a placeholder)
  manager->variable_item_list = variable_item_list_alloc();
  variable_item_list_add(manager->variable_item_list, "BLE", 0, NULL, NULL);
  variable_item_list_add(manager->variable_item_list, "USB", 0, NULL, NULL);
  
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
