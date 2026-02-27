#include <stdio.h>
#include <assert.h>
#include "../src/app_main.h"

int main() {
    // Run the end to end lifecycle simulation
    int result = flipper_app_run_e2e();
    assert(result == 0);
    
    puts("End-to-End lifecycle tests passed.");
    return 0;
}
