# Implementation Plan: Full Keyboard Implementation

## Phase 1: Protocol and Core Extension
- [ ] Task: Extend Protocol for Modifiers
    - [ ] Update `protocol.h` and `protocol.c` to support modifier masks.
    - [ ] Implement `Key Down` and `Key Up` packet types.
- [ ] Task: Update HID Injector
    - [ ] Modify `hid_injector.c` to maintain a persistent modifier state.
    - [ ] Update injection functions to apply active modifiers to keystrokes.
- [ ] Task: Conductor - User Manual Verification 'Phase 1: Protocol and Core Extension' (Protocol in workflow.md)

## Phase 2: Web Dashboard Keyboard UI
- [ ] Task: Native Keyboard Trigger
    - [ ] Implement a hidden input and keyboard icon to focus/unfocus native keyboard.
    - [ ] Map native `keydown` events to our BLE protocol packets.
- [ ] Task: Modifier and Shortcut UI
    - [ ] Create a "Sticky Keys" panel for Ctrl, Alt, Shift, Cmd.
    - [ ] Add a "Quick Shortcuts" grid (Copy, Paste, Undo, etc.).
- [ ] Task: Conductor - User Manual Verification 'Phase 2: Web Dashboard Keyboard UI' (Protocol in workflow.md)

## Phase 3: Integration and Polish
- [ ] Task: End-to-End Keyboard Test
    - [ ] Verify that typing "Hello World" on the phone appears correctly on the computer.
    - [ ] Verify that "Shift + a" results in an uppercase "A".
- [ ] Task: Conductor - User Manual Verification 'Phase 3: Integration and Polish' (Protocol in workflow.md)