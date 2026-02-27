#include <stdio.h>
#include <assert.h>
#include "../src/hid_injector.h"

int main() {
  // Test injecting a simple key press
  int key_result = FlipperHidInjectKey('a');
  assert(key_result == 0); // 0 indicates success
  
  // Test injecting a mouse movement
  int mouse_result = FlipperHidInjectMouse(10, 5); // move x by 10, y by 5
  assert(mouse_result == 0); // 0 indicates success
  
  puts("HID Injection tests passed.");
  return 0;
}
