#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_usb_hid.h>
#include <furi_hal_vibro.h>

static uint16_t current_modifiers = 0;

int FlipperHidInjectKey(char key) {
  uint16_t hid_key = HID_ASCII_TO_KEY(key);
  if (hid_key != HID_KEYBOARD_NONE) {
    // Apply current sticky modifiers
    uint16_t key_with_mods = hid_key | current_modifiers;
    
    furi_hal_hid_kb_press(key_with_mods);
    furi_hal_hid_kb_release(key_with_mods);
    return 0;
  }
  return -1;
}

int FlipperHidInjectKeyDown(uint16_t key) {
  // Apply sticky modifiers to the key down event
  if (furi_hal_hid_kb_press(key | current_modifiers)) {
    return 0;
  }
  return -1;
}

int FlipperHidInjectKeyUp(uint16_t key) {
  // We should release the key with the modifiers it was pressed with?
  // Actually HID release usually just needs the keycode, but HAL might want both.
  if (furi_hal_hid_kb_release(key | current_modifiers)) {
    return 0;
  }
  return -1;
}

int FlipperHidSetModifiers(uint8_t modifiers) {
  // Map standard HID bitmask (8 bits) to Furi bits (shifted by 8)
  current_modifiers = ((uint16_t)modifiers << 8);
  return 0;
}

int FlipperHidInjectMouse(int dx, int dy) {
  if (furi_hal_hid_mouse_move(dx, dy)) {
    return 0;
  }
  return -1;
}
