#include "app_main.h"
#include "usb_hid_manager.h"
#include "ble_listener.h"
#include "protocol.h"
#include <furi_hal_vibro.h>
#include <furi.h>
#include <stdio.h>
#include <stdint.h>

int FlipperAppRunE2e(void) {
  puts("Starting End-to-End Simulation...");
  
  // 1. Initialize USB HID
  if (FlipperUsbHidInit() != 0) return -1;
  
  // Trigger haptic feedback on USB init
  furi_hal_vibro_on(true);
  furi_delay_ms(50);
  furi_hal_vibro_on(false);
  
  // 2. Start BLE Listener
  if (FlipperBleListenerStart(NULL) != 0) return -1;
  
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
