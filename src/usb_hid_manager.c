#include "usb_hid_manager.h"
#include <furi.h>
#include <furi_hal_usb.h>

static FuriHalUsbInterface* prev_usb_mode = NULL;

int FlipperUsbHidInit(void) {
  // Save previous mode
  prev_usb_mode = furi_hal_usb_get_config();
  
  furi_hal_usb_unlock();
  bool success = furi_hal_usb_set_config(&usb_hid, NULL);
  
  return success ? 0 : -1;
}

int FlipperUsbHidDeinit(void) {
  if (prev_usb_mode != NULL) {
    furi_hal_usb_set_config(prev_usb_mode, NULL);
  } else {
    // Fallback if unknown
    furi_hal_usb_set_config(&usb_cdc_single, NULL);
  }
  
  // Re-lock the USB mode switch
  furi_hal_usb_lock();
  
  return 0;
}
