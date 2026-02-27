#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Parses a binary protocol packet and dispatches the command.
// Returns 0 if successfully parsed and dispatched, non-zero otherwise.
int flipper_protocol_parse(const uint8_t* packet, size_t length);

#ifdef __cplusplus
}
#endif
