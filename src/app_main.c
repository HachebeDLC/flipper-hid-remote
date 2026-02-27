#include "app_main.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
#include <stdio.h>
#include <stdint.h>

int flipper_app_run_e2e(void) {
    puts("Starting End-to-End Simulation...");
    
    // 1. Initialize USB HID
    if (flipper_usb_hid_init() != 0) return -1;
    
    // 2. Start BLE Listener
    if (flipper_ble_listener_start() != 0) return -1;
    
    // 3. Simulate receiving a valid Keyboard packet from the phone
    puts("Simulating BLE RX: Valid Keyboard Packet ('z')...");
    uint8_t dummy_packet[] = {0x01, 'z'};
    if (flipper_protocol_parse(dummy_packet, sizeof(dummy_packet)) != 0) return -1;
    
    // 4. Stop BLE Listener
    if (flipper_ble_listener_stop() != 0) return -1;
    
    // 5. Deinitialize USB HID
    if (flipper_usb_hid_deinit() != 0) return -1;
    
    puts("End-to-End Simulation completed successfully.");
    return 0; // Success
}
