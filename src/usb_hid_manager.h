#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Initializes the USB HID profile. Returns 0 on success.
int flipper_usb_hid_init(void);

// Deinitializes the USB HID profile. Returns 0 on success.
int flipper_usb_hid_deinit(void);

#ifdef __cplusplus
}
#endif
