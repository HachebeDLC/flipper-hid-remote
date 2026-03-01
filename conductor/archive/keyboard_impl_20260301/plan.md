# Implementation Plan: Full Keyboard Implementation

## Phase 1: Protocol and Core Extension [checkpoint: 5ff32f8]
- [x] Task: Extend Protocol for Modifiers [4941530]
    - [x] Update `protocol.h` and `protocol.c` to support modifier masks.
    - [x] Implement `Key Down` and `Key Up` packet types.
- [x] Task: Update HID Injector [4941530]
    - [x] Modify `hid_injector.c` to maintain a persistent modifier state.
    - [x] Update injection functions to apply active modifiers to keystrokes.
- [x] Task: Conductor - User Manual Verification 'Phase 1: Protocol and Core Extension' (Protocol in workflow.md) [5ff32f8]

## Phase 2: Web Dashboard Keyboard UI [checkpoint: afbec2c]
- [x] Task: Native Keyboard Trigger [2e78bb2]
    - [x] Implement a hidden input and keyboard icon to focus/unfocus native keyboard.
    - [x] Map native `keydown` events to our BLE protocol packets.
- [x] Task: Modifier and Shortcut UI [2e78bb2]
    - [x] Create a "Sticky Keys" panel for Ctrl, Alt, Shift, Cmd.
    - [x] Add a "Quick Shortcuts" grid (Copy, Paste, Undo, etc.).
- [x] Task: Conductor - User Manual Verification 'Phase 2: Web Dashboard Keyboard UI' (Protocol in workflow.md) [afbec2c]

## Phase 3: Integration and Polish [checkpoint: 443796a]
- [x] Task: End-to-End Keyboard Test [65431f3]
    - [x] Verify that typing "Hello World" on the phone appears correctly on the computer.
    - [x] Verify that "Shift + a" results in an uppercase "A".
- [x] Task: Conductor - User Manual Verification 'Phase 3: Integration and Polish' (Protocol in workflow.md) [443796a]

## Phase 4: Character Mapping and Bug Fixes [checkpoint: 82781e7]
- [x] Task: Fix Special Character Mappings [82781e7]
    - [x] Investigate why question mark '?' maps to underscore '_'.
    - [x] Update `HID_ASCII_TO_KEY` logic or character handling in `hid_injector.c`.
- [x] Task: Expand Special Character Support [82781e7]
    - [x] Ensure all common punctuation marks are correctly injected.
- [x] Task: Conductor - User Manual Verification 'Phase 4: Character Mapping and Bug Fixes' (Protocol in workflow.md) [82781e7]