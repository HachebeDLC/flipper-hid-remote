#include "hid_injector.h"
#include <furi.h>
#include <furi_hal_usb_hid.h>
#include <furi_hal_vibro.h>
#include <storage/storage.h>

static uint16_t current_modifiers = 0;
static uint16_t active_layout[128];

// Helper to convert 8-bit BadUSB modifiers to 16-bit FuriHal modifiers
static uint16_t ConvertModifiers(uint8_t kl_mods) {
    uint16_t furi_mods = 0;
    if (kl_mods & (1 << 0)) furi_mods |= KEY_MOD_LEFT_CTRL;
    if (kl_mods & (1 << 1)) furi_mods |= KEY_MOD_LEFT_SHIFT;
    if (kl_mods & (1 << 2)) furi_mods |= KEY_MOD_LEFT_ALT;
    if (kl_mods & (1 << 3)) furi_mods |= KEY_MOD_LEFT_GUI;
    if (kl_mods & (1 << 4)) furi_mods |= KEY_MOD_RIGHT_CTRL;
    if (kl_mods & (1 << 5)) furi_mods |= KEY_MOD_RIGHT_SHIFT;
    if (kl_mods & (1 << 6)) furi_mods |= KEY_MOD_RIGHT_ALT;
    if (kl_mods & (1 << 7)) furi_mods |= KEY_MOD_RIGHT_GUI;
    return furi_mods;
}

void FlipperHidLayoutLoadDefault(void) {
    for (int i = 0; i < 128; i++) {
        active_layout[i] = HID_ASCII_TO_KEY(i);
    }
}

bool FlipperHidLayoutLoadFile(const char* path) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_alloc(storage);
    bool success = false;

    if (storage_file_open(file, path, FSAM_READ, FSOM_OPEN_EXISTING)) {
        uint16_t raw_layout[128];
        if (storage_file_read(file, raw_layout, 256) == 256) {
            // Convert each entry from KL format to FuriHal format
            for (int i = 0; i < 128; i++) {
                uint8_t scancode = raw_layout[i] & 0xFF;
                uint8_t mods = (raw_layout[i] >> 8) & 0xFF;
                active_layout[i] = scancode | ConvertModifiers(mods);
            }
            success = true;
        }
    }

    storage_file_close(file);
    storage_file_free(file);
    furi_record_close(RECORD_STORAGE);
    return success;
}

int FlipperHidInjectKey(char key) {
  if ((uint8_t)key >= 128) return -1;
  
  uint16_t hid_key = active_layout[(uint8_t)key];
  if (hid_key != HID_KEYBOARD_NONE) {
    uint16_t key_with_mods = hid_key | current_modifiers;
    furi_hal_hid_kb_press(key_with_mods);
    furi_delay_ms(60); 
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
