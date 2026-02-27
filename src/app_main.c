#include "app_main.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
#include <stdio.h>
#include <stdint.h>

int FlipperAppRunE2e(void) {
  puts("Starting End-to-End Simulation...");
  
  // 1. Initialize USB HID
  if (FlipperUsbHidInit() != 0) return -1;
  
  // 2. Start BLE Listener
  if (FlipperBleListenerStart() != 0) return -1;
  
  // 3. Simulate receiving a valid Keyboard packet from the phone
  puts("Simulating BLE RX: Valid Keyboard Packet ('z')...");
  uint8_t dummy_packet[] = {0x01, 'z'};
  if (FlipperProtocolParse(dummy_packet, sizeof(dummy_packet)) != 0) return -1;
  
  // 4. Stop BLE Listener
  if (FlipperBleListenerStop() != 0) return -1;
  
  // 5. Deinitialize USB HID
  if (FlipperUsbHidDeinit() != 0) return -1;
  
  puts("End-to-End Simulation completed successfully.");
  return 0; // Success
}
