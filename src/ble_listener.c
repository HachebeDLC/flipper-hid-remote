#include "ble_listener.h"
#include <stdio.h>

int flipper_ble_listener_start(void) {
    // In a real app, this would spawn a Furi Thread using furi_thread_alloc
    // and initialize the FuriHal BLE UART service.
    puts("Simulating Furi BLE Listener Thread start...");
    return 0; // Success
}

int flipper_ble_listener_stop(void) {
    // In a real app, this would signal the thread to exit and free resources.
    puts("Simulating Furi BLE Listener Thread stop...");
    return 0; // Success
}

int flipper_ble_dispatch_packet(const uint8_t* data, size_t length) {
    // In a real app, this would parse the Protobuf or binary packet
    // and call the corresponding hid_injector functions.
    printf("Simulating packet dispatch: received %zu bytes.", length);
    puts("");
    return 0; // Success
}
