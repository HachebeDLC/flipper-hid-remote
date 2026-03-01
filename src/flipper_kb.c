#include <furi.h>
#include <furi_hal.h>
#include "gui_manager.h"

int32_t flipper_kb_app(void* p) {
    UNUSED(p);

    // Initialize the GUI Manager
    GuiManager* gui_manager = GuiManagerAlloc();
    if (gui_manager == NULL) {
        return -1;
    }

    // Show the main menu
    GuiManagerShowMenu(gui_manager);

    // Keep the application running and processing events
    // This is a minimal event loop placeholder
    view_dispatcher_run(gui_manager->view_dispatcher);

    // Free resources upon exit
    GuiManagerFree(gui_manager);

    return 0;
}
