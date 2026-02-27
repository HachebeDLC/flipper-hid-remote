#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "../src/protocol.h"

int main() {
    // Test parsing a valid keyboard packet
    // Format: 0x01 (Keyboard Type), 'a' (Payload)
    uint8_t kb_packet[] = {0x01, 'a'};
    int kb_result = flipper_protocol_parse(kb_packet, sizeof(kb_packet));
    assert(kb_result == 0); // 0 indicates success
    
    // Test parsing a valid mouse packet
    // Format: 0x02 (Mouse Type), 10 (dx), 5 (dy)
    uint8_t mouse_packet[] = {0x02, 10, 5};
    int mouse_result = flipper_protocol_parse(mouse_packet, sizeof(mouse_packet));
    assert(mouse_result == 0); // 0 indicates success
    
    // Test parsing an invalid packet type
    uint8_t invalid_packet[] = {0x03, 0x00};
    int invalid_result = flipper_protocol_parse(invalid_packet, sizeof(invalid_packet));
    assert(invalid_result != 0); // Should fail validation
    
    puts("Protocol parsing tests passed.");
    return 0;
}
