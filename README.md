# Flipper Zero HID Remote 🐬⌨️🖱️

Turn your Flipper Zero into a professional USB HID Bridge. Control any computer using your smartphone or PC via a web-based Bluetooth dashboard with full keyboard, mouse, and multi-layout support.

[**Launch Dashboard**](https://flipper-hid-remote.netlify.app/)

## Features

- **Full Keyboard Bridge**: Type on your phone or PC and inject keystrokes into the target computer via the Flipper's USB port.
- **Precision Trackpad**: High-precision mouse movement with adjustable sensitivity and non-linear acceleration.
- **Dynamic Layouts**: Full support for international keyboard layouts (Spanish, French, etc.) using standard Flipper `.kl` files.
- **Self-Healing Connection**: Dashboard automatically handles Bluetooth bonding and reconnection.
- **Momentum Optimized**: Safely overrides the Bluetooth name to `HID_[DeviceName]` and provides real-time battery reporting.
- **Persistent Settings**: Your layout, vibration, and mouse preferences are saved directly to the Flipper's SD card.
- **Hardware Status**: View active modifier icons (`^ S A G`) and battery percentage on the Flipper screen.

## Installation

### Method A: Standalone Build (ufbt)
If you have `ufbt` installed, run:
```bash
ufbt launch
```

### Method B: Firmware Integrated (Momentum/fbt)
1. Copy the project to your firmware's `applications_user` folder:
   ```bash
   cp -r . /path/to/Momentum-Firmware/applications_user/flipper_kb
   ```
2. Build and launch:
   ```bash
   ./fbt launch APPSRC=applications_user/flipper_kb
   ```

## Usage

1. Open the **HID Remote** app on your Flipper.
2. Select **Start Remote**. Wait for the confirmation vibration.
3. Open the [Web Dashboard](https://flipper-hid-remote.netlify.app/) in a compatible browser:
    - **Android/PC**: Chrome, Edge, or any Chromium-based browser.
    - **iOS**: Use the **Bluefy** app.
4. Click **Connect**. Your device should appear as **HID_[YourName]**.
5. Control your computer!

## Privacy & Security

- **Zero-Install**: No app store downloads required.
- **No Data Collection**: All communication happens locally between your device, the Flipper, and the target computer.
- **Secure Context**: Requires HTTPS for Web Bluetooth (automatically provided by the Netlify link).

---
Built with ❤️ for the Flipper Zero Community.
