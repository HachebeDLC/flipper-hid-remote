#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Injects a single keystroke. Returns 0 on success.
int flipper_hid_inject_key(char key);

// Injects mouse movement. Returns 0 on success.
int flipper_hid_inject_mouse(int dx, int dy);

#ifdef __cplusplus
}
#endif
