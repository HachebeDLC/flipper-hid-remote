# Specification: Full Keyboard Implementation

## Overview
This track expands the Flipper HID Remote to support a complete keyboard experience. It focuses on enabling native text input from the phone's keyboard, supporting modifier keys (Ctrl, Alt, Shift, Cmd), and implementing common shortcut macros.

## Functional Requirements
- **Web Interface**: 
  - Implement a hidden text input field in the Web Dashboard to trigger the phone's native keyboard.
  - Add a dedicated UI section for modifier keys (Sticky Keys) that can be toggled on/off.
  - Add quick-access buttons for common shortcuts (Ctrl+C, Ctrl+V, Alt+Tab, etc.).
- **Protocol Expansion**:
  - Extend the binary protocol to support "Key Down" and "Key Up" events for modifier persistence.
  - Support high-level "Shortcut" commands for pre-defined macros.
- **Flipper Implementation**:
  - Update `hid_injector.c` to handle modifier masks.
  - Implement logic to combine modifiers with incoming characters for real-time injection.

## Acceptance Criteria
- Tapping the keyboard icon in the browser opens the phone's native keyboard.
- Typing any character on the phone keyboard results in that character being typed on the target computer via the Flipper.
- Enabling a modifier (e.g., Shift) in the browser UI correctly modifies subsequent keystrokes on the computer.
- Clicking a "Ctrl+C" shortcut button in the browser successfully triggers a copy command on the target computer.