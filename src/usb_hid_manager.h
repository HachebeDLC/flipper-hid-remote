#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Initializes the USB HID profile. Returns 0 on success.
int FlipperUsbHidInit(void);

// Deinitializes the USB HID profile. Returns 0 on success.
int FlipperUsbHidDeinit(void);

#ifdef __cplusplus
}
#endif
