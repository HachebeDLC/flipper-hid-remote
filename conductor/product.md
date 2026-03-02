# Initial Concept\n\nA Flipper Zero application that acts as USB Mouse and keyboard, and that is controlled via bluetooth by a phone

# Product Guide: Flipper HID Remote

## Vision
A versatile Flipper Zero application that bridges a smartphone and a computer. The smartphone acts as the primary controller over Bluetooth Low Energy (BLE), sending HID commands to the Flipper, which then emulates a USB Mouse and Keyboard to the target host.

## Target Users
- **IT/Sysadmins**: Professionals requiring a portable, remote input solution for system administration, server management, or presentations.
- **Enthusiasts**: Users looking to expand their Flipper's utility as a secondary, customizable input device for home automation or media control.

## Core Features
- **Remote Keyboard**: Full alphanumeric input capability sent from the phone and injected via USB HID.
- **Remote Mouse**: High-precision mouse cursor movement and button clicks controlled via a touch interface on the phone.
- **Dynamic Layouts**: Support for multiple keyboard languages using standard Flipper .kl files.
- **Multimedia Keys**: Dedicated controls for system volume, media playback (Play/Pause/Skip), and presentation slide navigation.
- **USB-HID Emulation**: The Flipper appears as a standard "Plug and Play" HID device to any host computer, requiring no special drivers.
- **BLE Control Link**: Low-latency communication between the phone and Flipper using standard Flipper BLE serial protocols.
- **Hardware Reporting**: Current Flipper battery status is reported to the connected host via BLE.

## Customization & Persistence
- **Persistent Settings**: User preferences for keyboard layouts, vibration, and mouse acceleration are saved to the SD card.
- **Adaptive Input**: Toggleable non-linear mouse acceleration for smoother trackpad navigation.
- **Web Themes**: Dark and Light mode support in the dashboard, persisted in the browser.

## User Experience
- **Phone Interface**: Primary control is handled via a smartphone. We will leverage existing Flipper Bluetooth Serial protocols to allow control via the official Flipper Mobile App (using custom CLI commands) or a dedicated Web Bluetooth dashboard.
- **Flipper UI**: The Flipper screen will maintain a **Minimal Status Display**, showing connectivity icons (Bluetooth link status, USB connection state) and a brief log of active inputs to ensure the user knows what is being sent.
