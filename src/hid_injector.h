#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Injects a single keystroke. Returns 0 on success.
int FlipperHidInjectKey(char key);

// Injects mouse movement. Returns 0 on success.
int FlipperHidInjectMouse(int dx, int dy);

#ifdef __cplusplus
}
#endif
