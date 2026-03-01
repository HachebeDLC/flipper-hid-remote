#include "f7_mock.h"
#include <stdio.h>

void furi_delay_ms(uint32_t ms) {
    (void)ms;
}

bool furi_hal_hid_kb_press(uint16_t key) {
    printf("Mock: Keyboard Press 0x%04X\n", key);
    return true;
}

bool furi_hal_hid_kb_release(uint16_t key) {
    printf("Mock: Keyboard Release 0x%04X\n", key);
    return true;
}

bool furi_hal_hid_mouse_move(int8_t dx, int8_t dy) {
    printf("Mock: Mouse Move %d, %d\n", (int)dx, (int)dy);
    return true;
}

void furi_hal_vibro_on(bool value) {
    printf("Mock: Vibro %s\n", value ? "ON" : "OFF");
}

BleServiceBattery* ble_svc_battery_start(bool auto_update) {
    printf("Mock: Battery Service Start (auto_update=%d)\n", auto_update);
    return (BleServiceBattery*)0x1234;
}

void ble_svc_battery_stop(BleServiceBattery* service) {
    printf("Mock: Battery Service Stop %p\n", (void*)service);
}
