#include <stdio.h>
#include <assert.h>
#include "../src/hid_descriptors.h"

int main() {
    // Check that we have a defined keyboard report descriptor
    assert(sizeof(hid_report_descriptor_keyboard) > 0);
    // Check that we have a defined mouse report descriptor
    assert(sizeof(hid_report_descriptor_mouse) > 0);
    
    printf("HID Descriptors test passed.\n");
    return 0;
}
