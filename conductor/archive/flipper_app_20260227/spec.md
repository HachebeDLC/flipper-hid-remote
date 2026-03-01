# Specification: Implement Flipper Application

## Overview
This track focuses on transitioning our local simulation code into a real, deployable Flipper Zero application (.fap). We will set up the `ufbt` build system, implement a GUI with a Menu System, and connect our logic to the actual hardware APIs (FuriHal) for USB, BLE, and Haptics.

## Functional Requirements
- **Build System**: Configure the project to build using the standalone `ufbt` toolchain.
- **GUI (Menu System)**: Implement a user interface using the Furi GUI framework, providing a menu to start/stop the remote and view connection status.
- **Hardware Integration**:
  - Replace simulated USB HID routines with actual `furi_hal_usb_hid` calls.
  - Replace simulated BLE Serial routines with actual `furi_hal_bt_serial` calls.
  - Integrate the Haptics engine (`furi_hal_vibro`) to provide tactile feedback on Bluetooth connect/disconnect and USB initialization.

## Acceptance Criteria
- Project successfully compiles into a `.fap` file using `ufbt`.
- Running the application on a Flipper Zero displays the interactive menu.
- Activating the remote via the menu successfully starts broadcasting BLE and initializes USB HID.
- Connecting via the Web Bluetooth dashboard successfully triggers haptic feedback on the Flipper.
- Sending commands from the Web dashboard successfully injects HID events into the host computer.