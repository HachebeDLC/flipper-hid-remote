#include "hid_injector.h"
#include <stdio.h>

int flipper_hid_inject_key(char key) {
    // In a real Flipper environment, this would build a HID report and call:
    // furi_hal_usb_hid_keyboard_press(key);
    // furi_hal_usb_hid_keyboard_release(key);
    printf("Simulating Furi USB HID key injection: '%c'", key);
    puts("");
    return 0; // Success
}

int flipper_hid_inject_mouse(int dx, int dy) {
    // In a real Flipper environment, this would call:
    // furi_hal_usb_hid_mouse_move(dx, dy);
    printf("Simulating Furi USB HID mouse movement: dx=%d, dy=%d", dx, dy);
    puts("");
    return 0; // Success
}
