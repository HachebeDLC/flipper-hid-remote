#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration
struct GuiManager;

// Starts the BLE serial listener thread. Returns 0 on success.
int FlipperBleListenerStart(void* gui_manager);

// Stops the BLE serial listener thread. Returns 0 on success.
int FlipperBleListenerStop(void);

// Dispatches an incoming BLE packet to the appropriate handler.
int FlipperBleDispatchPacket(const uint8_t* data, size_t length);

// Notifies that the buffer is empty
void FlipperBleNotifyEmpty(void);

#ifdef __cplusplus
}
#endif
