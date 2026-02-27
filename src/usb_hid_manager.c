#include "usb_hid_manager.h"
#include <furi.h>
#include <furi_hal_usb.h>

int FlipperUsbHidInit(void) {
  if (furi_hal_usb_set_config(&usb_hid, NULL)) {
    return 0;
  }
  return -1;
}

int FlipperUsbHidDeinit(void) {
  if (furi_hal_usb_set_config(NULL, NULL)) {
    return 0;
  }
  return -1;
}
