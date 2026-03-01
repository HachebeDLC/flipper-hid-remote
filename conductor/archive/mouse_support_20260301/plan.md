# Plan: Mouse and Trackpad Support

## Phase 1: Protocol and C implementation [checkpoint: a5b3c4d]
- [x] Task: Extend Protocol for Mouse Buttons [a5b3c4d]
    - [x] Define `PACKET_TYPE_MOUSE_BTN 0x06` in `protocol.c`.
    - [x] Update `FlipperProtocolParse` to handle button packets.
- [x] Task: Implement Mouse Button injection [a5b3c4d]
    - [x] Update `hid_injector.h` and `.c` with `FlipperHidInjectMouseButton`.

## Phase 2: Web Dashboard UI [checkpoint: a5b3c4d]
- [x] Task: Virtual Trackpad Implementation [a5b3c4d]
    - [x] Add a `<div id="trackpad">` to `index.html`.
    - [x] Implement touch/drag logic in `app.js` to calculate relative (dx, dy).
- [x] Task: Click logic [a5b3c4d]
    - [x] Implement single-tap for Left Click.
    - [x] Add physical buttons for Left/Right click for non-touch users.

## Phase 3: Refinement and Verification [checkpoint: a5b3c4d]
- [x] Task: Smooth movement tuning [a5b3c4d]
    - [x] Implement "throttling" on the JS side to avoid flooding the BLE buffer.
    - [x] Added Pointer Lock API for PC users.
    - [x] Added Scroll Wheel support.
- [x] Task: Conductor - User Manual Verification 'Mouse Support' [a5b3c4d]
- [x] Task: Conductor - Checkpoint 'Mouse Support' [a5b3c4d]
