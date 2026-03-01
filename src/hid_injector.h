#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Injects a single keystroke (press + release). Returns 0 on success.
int FlipperHidInjectKey(char key);

// Injects a key down event. Returns 0 on success.
int FlipperHidInjectKeyDown(uint16_t key);

// Injects a key up event. Returns 0 on success.
int FlipperHidInjectKeyUp(uint16_t key);

// Sets the current modifier mask. Returns 0 on success.
int FlipperHidSetModifiers(uint8_t modifiers);

// Loads the default US layout.
void FlipperHidLayoutLoadDefault(void);

// Loads a layout from a .kl file. Returns true on success.
bool FlipperHidLayoutLoadFile(const char* path);

// Injects mouse movement. Returns 0 on success.
int FlipperHidInjectMouse(int dx, int dy);

#ifdef __cplusplus
}
#endif
