#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_usb_hid.h>
#include <furi_hal_vibro.h>

static uint16_t current_modifiers = 0;

uint16_t TranslateToSpanish(char ascii) {
    switch(ascii) {
        case '?': return HID_KEYBOARD_MINUS | KEY_MOD_LEFT_SHIFT;
        case '@': return HID_KEYBOARD_2 | KEY_MOD_RIGHT_ALT;
        case '!': return HID_KEYBOARD_1 | KEY_MOD_LEFT_SHIFT;
        case '"': return HID_KEYBOARD_2 | KEY_MOD_LEFT_SHIFT;
        case '#': return HID_KEYBOARD_3 | KEY_MOD_RIGHT_ALT;
        case '$': return HID_KEYBOARD_4 | KEY_MOD_LEFT_SHIFT;
        case '%': return HID_KEYBOARD_5 | KEY_MOD_LEFT_SHIFT;
        case '&': return HID_KEYBOARD_6 | KEY_MOD_LEFT_SHIFT;
        case '/': return HID_KEYBOARD_7 | KEY_MOD_LEFT_SHIFT;
        case '(': return HID_KEYBOARD_8 | KEY_MOD_LEFT_SHIFT;
        case ')': return HID_KEYBOARD_9 | KEY_MOD_LEFT_SHIFT;
        case '=': return HID_KEYBOARD_0 | KEY_MOD_LEFT_SHIFT;
        case '\'': return HID_KEYBOARD_MINUS;
        case '.': return HID_KEYBOARD_DOT;
        case ',': return HID_KEYBOARD_COMMA;
        case '-': return HID_KEYBOARD_SLASH;
        case '_': return HID_KEYBOARD_SLASH | KEY_MOD_LEFT_SHIFT;
        case ':': return HID_KEYBOARD_DOT | KEY_MOD_LEFT_SHIFT;
        case ';': return HID_KEYBOARD_COMMA | KEY_MOD_LEFT_SHIFT;
        default: return HID_ASCII_TO_KEY(ascii);
    }
}

int FlipperHidInjectKey(char key) {
  uint16_t hid_key = TranslateToSpanish(key);
  if (hid_key != HID_KEYBOARD_NONE) {
    uint16_t key_with_mods = hid_key | current_modifiers;
    furi_hal_hid_kb_press(key_with_mods);
    furi_delay_ms(60); // INCREASED HOLD TIME FOR IPHONE
    furi_hal_hid_kb_release(key_with_mods);
    return 0;
  }
  return -1;
}

int FlipperHidInjectKeyDown(uint16_t key) {
  if (furi_hal_hid_kb_press(key | current_modifiers)) return 0;
  return -1;
}

int FlipperHidInjectKeyUp(uint16_t key) {
  if (furi_hal_hid_kb_release(key | current_modifiers)) return 0;
  return -1;
}

int FlipperHidSetModifiers(uint8_t modifiers) {
  current_modifiers = ((uint16_t)modifiers << 8);
  return 0;
}

int FlipperHidInjectMouse(int dx, int dy) {
  if (furi_hal_hid_mouse_move(dx, dy)) return 0;
  return -1;
}
