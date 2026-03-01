#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_usb_hid.h>
#include <furi_hal_vibro.h>

int FlipperHidInjectKey(char key) {
  uint16_t hid_key = HID_ASCII_TO_KEY(key);
  if (hid_key != HID_KEYBOARD_NONE) {
    // Vibrate briefly (non-blocking if possible, but keep it very short or remove)
    // Removed vibro and delays here because this executes in the BT thread context!
    
    furi_hal_hid_kb_press(hid_key);
    // Removed delay: the host might miss it if polling rate is slow, but we prevent a hard crash
    furi_hal_hid_kb_release(hid_key);
    return 0;
  }
  return -1;
}

int FlipperHidInjectMouse(int dx, int dy) {
  if (furi_hal_hid_mouse_move(dx, dy)) {
    return 0;
  }
  return -1;
}
