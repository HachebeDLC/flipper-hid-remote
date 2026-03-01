#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FLIPPER_KB_CONFIG_PATH "/ext/apps/USB/flipper_kb.conf"

typedef struct {
    char layout_path[256];
    bool vibro_enabled;
} FlipperKbConfig;

// Loads the configuration from the SD card.
// If file doesn't exist, initializes with defaults.
void FlipperKbConfigLoad(FlipperKbConfig* config);

// Saves the configuration to the SD card.
void FlipperKbConfigSave(FlipperKbConfig* config);

#ifdef __cplusplus
}
#endif
