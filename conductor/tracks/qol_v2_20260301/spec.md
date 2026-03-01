# Spec: Quality of Life Improvements v2

## Overview
Building upon the initial QoL track, this feature set focuses on deeper hardware integration (Battery), input refinement (Mouse Acceleration), and UI polish (BT Name selection, Sub-menus, and Web Themes).

## Functional Requirements
1. **Custom Bluetooth Name:**
   - Add a "Bluetooth Name" setting in the Flipper app.
   - Allow selection from predefined names: "Flipper HID", "Control Center", "Universal Remote", "Stealth Input".
   - This name must be reflected in the BLE advertising packet.

2. **Battery Level Reporting:**
   - Update the BLE profile to report the Flipper Zero's current battery level to the connected host (computer/phone).
   - This allows the host to show the Flipper's battery status in its Bluetooth settings.

3. **Mouse Acceleration:**
   - Implement a toggle for "Mouse Acceleration" in the settings.
   - When enabled, the `dx` and `dy` values sent to the host should be scaled non-linearly based on movement velocity (delta per update).

4. **Settings Reorganization:**
   - Refactor `GuiManager` to use sub-menus for settings:
     - **Connectivity:** Bluetooth Name, Auto-Reconnect (placeholder).
     - **Input:** Keyboard Layout, Mouse Sensitivity, Mouse Acceleration.
     - **Feedback:** Vibration.

5. **Web Themes:**
   - Add a theme toggle (Light/Dark) to the Web Dashboard.
   - Persist the theme choice in `localStorage`.

## Non-Functional Requirements
- **Low Latency:** Mouse acceleration logic must not introduce perceptible lag.
- **Memory Efficiency:** Sub-menu implementation should remain within Flipper's RAM constraints.

## Acceptance Criteria
- Flipper can change its name and be discovered as the new name on a PC/Phone.
- Host device correctly displays Flipper battery percentage.
- Mouse movement feels "faster" during quick swipes when acceleration is ON.
- Web dashboard correctly toggles between light and dark themes.
