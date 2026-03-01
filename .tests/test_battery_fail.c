#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// Mocking the interface we WANT to have
bool FlipperBleIsBatteryServiceActive(void);

// Dummy implementation that fails
bool FlipperBleIsBatteryServiceActive(void) {
    return false;
}

int main() {
    printf("Checking if Battery Service is active...\n");
    assert(FlipperBleIsBatteryServiceActive() == true);
    
    puts("Battery Service active test passed.");
    return 0;
}
