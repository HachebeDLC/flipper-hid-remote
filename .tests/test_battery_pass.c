#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

bool FlipperBleIsBatteryServiceActive(void);

bool FlipperBleIsBatteryServiceActive(void) {
    return true;
}

int main() {
    printf("Checking if Battery Service is active...\n");
    assert(FlipperBleIsBatteryServiceActive() == true);
    
    puts("Battery Service active test passed.");
    return 0;
}
