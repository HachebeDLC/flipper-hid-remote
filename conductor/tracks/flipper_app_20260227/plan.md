# Implementation Plan: Implement Flipper Application

## Phase 1: Build System and Project Structure [checkpoint: 6385484]
- [x] Task: Set up `ufbt` and `application.fam` [3fad99c]
    - [x] Create the `application.fam` file to define the Flipper application package.
    - [x] Restructure source files (if necessary) to comply with `ufbt` conventions.
- [x] Task: Conductor - User Manual Verification 'Phase 1: Build System and Project Structure' (Protocol in workflow.md) [6385484]

## Phase 2: GUI and Menu System [checkpoint: 7154f1b]
- [x] Task: Implement Furi GUI Menu [aa3a083]
    - [x] Set up the main view dispatcher and view modules.
    - [x] Create an interactive menu view to start/stop the remote.
    - [x] Create a status view to display BLE and USB connection states.
- [x] Task: Conductor - User Manual Verification 'Phase 2: GUI and Menu System' (Protocol in workflow.md) [7154f1b]

## Phase 3: Hardware Integration (USB, BLE, Haptics)
- [ ] Task: Refactor Mock Implementations to FuriHal
    - [ ] Update `usb_hid_manager` and `hid_injector` to use actual FuriHal USB APIs.
    - [ ] Update `ble_listener` to use actual FuriHal BT Serial APIs.
    - [ ] Integrate `furi_hal_vibro` to trigger haptic feedback on connection events.
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Hardware Integration (USB, BLE, Haptics)' (Protocol in workflow.md)