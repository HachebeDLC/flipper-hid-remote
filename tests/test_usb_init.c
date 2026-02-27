#include <stdio.h>
#include <assert.h>
#include "../src/usb_hid_manager.h"

int main() {
  // Test initialization
  int init_result = FlipperUsbHidInit();
  assert(init_result == 0); // 0 indicates success
  
  // Test deinitialization
  int deinit_result = FlipperUsbHidDeinit();
  assert(deinit_result == 0); // 0 indicates success
  
  printf("USB initialization and deinitialization test passed.\\n");
  return 0;
}
