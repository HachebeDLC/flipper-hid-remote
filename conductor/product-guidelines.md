# Product Guidelines: Flipper HID Remote

## UX Principles
- **Feedback Oriented**: Every command received from the phone must have a corresponding (though potentially brief) visual indicator on the Flipper screen to ensure the user is aware of the device's activity.
- **Resilient Link**: The application must prioritize maintaining the Bluetooth connection. If the link is lost, the app should attempt background reconnection silently and recover state without requiring a full application restart.
- **Seamless Trust**: To provide a fluid "remote control" experience, the app will rely on the underlying Bluetooth pairing security. Once paired and connected, commands from the phone are executed immediately without secondary on-device confirmations.

## Visual Style
- **Native Flipper UI**: All on-screen elements, including fonts, icons, and menu layouts, must adhere to the standard Flipper Zero UI library (FuriGui). This ensures the application feels like a built-in part of the firmware.
- **Connectivity Status**: Use standard system icons for Bluetooth (connected/disconnected) and USB (plugged/unplugged) in the status bar or header.

## Haptics & Sound
- **Events Only**: To balance battery life and user awareness, use haptic feedback (vibration) and audible tones exclusively for major lifecycle events:
    - Successful Bluetooth connection.
    - Loss of Bluetooth connection.
    - USB device initialization by the host.

## Development Standards
- **Low Latency**: Code paths for HID packet transmission must be highly optimized to minimize the delay between phone-input and host-execution.
- **Battery Efficiency**: Avoid frequent screen refreshes for static data; only update UI elements when a state change occurs.
