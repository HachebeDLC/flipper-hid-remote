#include <furi.h>
#include <furi_hal.h>
#include "app_main.h"

int32_t flipper_kb_app(void* p) {
    UNUSED(p);
    // This is the real entry point for the Flipper Zero application.
    // For now, we call our simulation entry point which we will later refactor.
    int result = FlipperAppRunE2e();
    return (int32_t)result;
}
