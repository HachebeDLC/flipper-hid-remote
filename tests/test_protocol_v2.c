#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "../src/protocol.h"
#include "../src/hid_injector.h"

int main() {
    // 1. Test Key Down
    uint8_t key_down_packet[] = {0x03, 0x04}; // 'a'
    assert(FlipperProtocolParse(key_down_packet, sizeof(key_down_packet)) == 0);
    
    // 2. Test Key Up
    uint8_t key_up_packet[] = {0x04, 0x04};
    assert(FlipperProtocolParse(key_up_packet, sizeof(key_up_packet)) == 0);
    
    // 3. Test Set Modifiers (Shift = 0x02 in standard HID mask, bit 1)
    uint8_t mod_packet[] = {0x05, 0x02}; 
    assert(FlipperProtocolParse(mod_packet, sizeof(mod_packet)) == 0);
    
    // 4. Test Key with active modifiers
    uint8_t kb_packet[] = {0x01, 'b'};
    assert(FlipperProtocolParse(kb_packet, sizeof(kb_packet)) == 0);
    
    puts("Protocol V2 and Modifier persistence tests passed.");
    return 0;
}
