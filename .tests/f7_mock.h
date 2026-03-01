#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Furi Mocks
#define UNUSED(x) (void)(x)
#define furi_check(x) assert(x)
void furi_delay_ms(uint32_t ms);

// HID Mocks
#define HID_KEYBOARD_NONE 0x00
#define HID_ASCII_TO_KEY(x) (uint16_t)(x)

bool furi_hal_hid_kb_press(uint16_t key);
bool furi_hal_hid_kb_release(uint16_t key);
bool furi_hal_hid_mouse_move(int8_t dx, int8_t dy);

// Vibro Mocks
void furi_hal_vibro_on(bool value);

// Battery Service Mocks
typedef struct BleServiceBattery BleServiceBattery;
BleServiceBattery* ble_svc_battery_start(bool auto_update);
void ble_svc_battery_stop(BleServiceBattery* service);

// Protocol Types
#define PACKET_TYPE_KEYBOARD 0x01
#define PACKET_TYPE_MOUSE    0x02
#define PACKET_TYPE_KEY_DOWN  0x03
#define PACKET_TYPE_KEY_UP    0x04
#define PACKET_TYPE_SET_MODS  0x05
