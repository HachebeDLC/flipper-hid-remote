#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_usb_hid.h>

int FlipperHidInjectKey(char key) {
  uint16_t hid_key = HID_ASCII_TO_KEY(key);
  if (hid_key != HID_KEYBOARD_NONE) {
    furi_hal_hid_kb_press(hid_key);
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
