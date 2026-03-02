# Flipper Zero HID Remote 🐬⌨️🖱️

Turn your Flipper Zero into a robust USB HID Bridge, allowing you to control any computer using your smartphone or PC via a web-based Bluetooth dashboard.

[**Launch Dashboard**](https://flipper-hid-remote.netlify.app/)

## Features

- **Full Keyboard Bridge**: Type on your phone or PC and inject keystrokes into the target computer via the Flipper's USB port.
- **Precision Trackpad**: Use your phone screen as a mouse trackpad with adjustable sensitivity and non-linear acceleration.
- **Dynamic Layouts**: Full support for international keyboard layouts (Spanish, French, etc.) using standard Flipper `.kl` files.
- **Pro PC Remote**: Pointer Lock API support—bind your physical mouse to the dashboard for infinite scrolling and movement.
- **Cross-Platform Shortcuts**: Automatic remapping of PC shortcuts (Ctrl+C/V) to native iOS/Mac shortcuts (Cmd+C/V).
- **Persistent Settings**: Your layout, vibration, and mouse preferences are saved directly to the Flipper's SD card.
- **Hardware Info**: View real-time Flipper battery percentage and active modifier keys on the Flipper screen.

## Installation

### 1. Build and Flash
Ensure you have `ufbt` installed, then run:
```bash
ufbt launch
```

### 2. Prepare SD Card (Optional for Custom Layouts)
Copy your preferred `.kl` files to `/ext/badusb/assets/layouts/` on your Flipper's SD card.

## Usage

1. Open the **HID Remote** app on your Flipper Zero.
2. Select **Start Remote**. Wait for the confirmation vibration.
3. Open the [Web Dashboard](https://flipper-hid-remote.netlify.app/) in a compatible browser:
    - **Android/PC**: Chrome, Edge, or any Chromium-based browser.
    - **iOS**: Use the **Bluefy** app (Standard Safari does not support Web Bluetooth).
4. Click **Connect** and select your Flipper.
5. Control your computer!

## Privacy & Security

- **Zero-Install**: No app store downloads required.
- **No Data Collection**: All communication happens locally between your device, the Flipper, and the target computer.
- **Open Source**: Built with standard Furi C API and Web Bluetooth standards.

---
Built with ❤️ for the Flipper Zero Community.
