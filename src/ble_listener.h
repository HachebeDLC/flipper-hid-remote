#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Starts the BLE serial listener thread. Returns 0 on success.
int flipper_ble_listener_start(void);

// Stops the BLE serial listener thread. Returns 0 on success.
int flipper_ble_listener_stop(void);

// Dispatches an incoming BLE packet to the appropriate handler.
int flipper_ble_dispatch_packet(const uint8_t* data, size_t length);

#ifdef __cplusplus
}
#endif
