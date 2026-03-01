#pragma once

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/modules/variable_item_list.h>

typedef struct {
  Gui* gui;
  ViewDispatcher* view_dispatcher;
  Submenu* submenu;
  VariableItemList* variable_item_list;
  
  VariableItem* ble_status_item;
  VariableItem* last_byte_item;
  
  uint8_t ble_buffer[4];
  size_t ble_buffer_size;
  
  // Debug counters
  uint32_t packets_received;
  uint8_t last_byte;
} GuiManager;

GuiManager* GuiManagerAlloc(void);
void GuiManagerFree(GuiManager* manager);
void GuiManagerShowMenu(GuiManager* manager);
void GuiManagerHandleBleData(GuiManager* manager, const uint8_t* data, size_t size);