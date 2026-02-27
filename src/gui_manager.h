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
} GuiManager;

// Initializes the GUI manager. Returns a pointer to the manager or NULL on failure.
GuiManager* GuiManagerAlloc(void);

// Frees the GUI manager and its resources.
void GuiManagerFree(GuiManager* manager);

// Switches to the main menu view.
void GuiManagerShowMenu(GuiManager* manager);
