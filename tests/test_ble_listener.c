#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "../src/ble_listener.h"

int main() {
  // Test starting the BLE listener thread
  int start_result = FlipperBleListenerStart();
  assert(start_result == 0);
  
  // Test the command dispatcher with a dummy packet
  uint8_t dummy_packet[] = {0x01, 0x02, 0x03, 0x04};
  int dispatch_result = FlipperBleDispatchPacket(dummy_packet, sizeof(dummy_packet));
  assert(dispatch_result == 0);
  
  // Test stopping the BLE listener thread
  int stop_result = FlipperBleListenerStop();
  assert(stop_result == 0);
  
  puts("BLE Listener tests passed.");
  return 0;
}
