#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "../src/ble_listener.h"

int main() {
    // Test starting the BLE listener thread
    int start_result = flipper_ble_listener_start();
    assert(start_result == 0);
    
    // Test the command dispatcher with a dummy packet
    uint8_t dummy_packet[] = {0x01, 0x02, 0x03, 0x04};
    int dispatch_result = flipper_ble_dispatch_packet(dummy_packet, sizeof(dummy_packet));
    assert(dispatch_result == 0);
    
    // Test stopping the BLE listener thread
    int stop_result = flipper_ble_listener_stop();
    assert(stop_result == 0);
    
    puts("BLE Listener tests passed.");
    return 0;
}
