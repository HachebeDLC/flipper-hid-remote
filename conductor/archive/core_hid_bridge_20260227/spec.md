# Specification: Core USB-HID Emulation and BLE Control Bridge

## Overview
This track focuses on the foundational architecture of the Flipper HID Remote. It involves setting up the USB HID descriptors on the Flipper, establishing a BLE serial link for receiving commands, and creating a basic Web Bluetooth interface for the phone to send those commands.

## Requirements
- **USB HID**: Configure the Flipper as a composite HID device (Keyboard + Mouse).
- **BLE Link**: Implement a Serial-over-BLE listener using the Furi BLE API.
- **Protocol**: Define a simple Protobuf-based or binary command set for mouse/keyboard actions.
- **Web App**: Create a minimal HTML/JS page using Web Bluetooth to connect and send "Hello World" or mouse move commands.

## Success Criteria
- Flipper is recognized as a Keyboard/Mouse by a host PC.
- Phone can pair and connect to the Flipper via the Web Dashboard.
- Sending a command from the phone results in an actual HID input on the host PC.
