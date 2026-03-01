#include "protocol.h"
#include "hid_injector.h"

// Define packet types
#define PACKET_TYPE_KEYBOARD 0x01
#define PACKET_TYPE_MOUSE    0x02
#define PACKET_TYPE_KEY_DOWN  0x03
#define PACKET_TYPE_KEY_UP    0x04
#define PACKET_TYPE_SET_MODS  0x05

int FlipperProtocolParse(const uint8_t* packet, size_t length) {
  if (packet == NULL || length == 0) {
      return -1; // Invalid packet
  }

  uint8_t type = packet[0];

  if (type == PACKET_TYPE_KEYBOARD) {
      // Expecting [Type][Char]
      if (length < 2) return -1;
      char key = (char)packet[1];
      return FlipperHidInjectKey(key);
  } 
  else if (type == PACKET_TYPE_MOUSE) {
      // Expecting [Type][dx][dy]
      if (length < 3) return -1;
      int dx = (int8_t)packet[1];
      int dy = (int8_t)packet[2];
      return FlipperHidInjectMouse(dx, dy);
  }
  else if (type == PACKET_TYPE_KEY_DOWN) {
      // Expecting [Type][HID KeyCode]
      if (length < 2) return -1;
      uint16_t key = (uint16_t)packet[1];
      return FlipperHidInjectKeyDown(key);
  }
  else if (type == PACKET_TYPE_KEY_UP) {
      // Expecting [Type][HID KeyCode]
      if (length < 2) return -1;
      uint16_t key = (uint16_t)packet[1];
      return FlipperHidInjectKeyUp(key);
  }
  else if (type == PACKET_TYPE_SET_MODS) {
      // Expecting [Type][Modifier Mask]
      if (length < 2) return -1;
      uint8_t mods = packet[1];
      return FlipperHidSetModifiers(mods);
  }
  
  return -1; // Unknown packet type
}
