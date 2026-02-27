# Tech Stack: Flipper HID Remote

## Flipper Application
- **Language**: **C** utilizing the **Furi API**. This is the native language for Flipper Zero apps, providing direct access to hardware (USB, BLE, Display, Haptics).
- **Build System**: **ufbt (Standalone Flipper Build Tool)**. We develop the application as a standalone project outside of the firmware tree for faster iteration and easier dependency management.
- **Target Firmware**: **Community Firmware (Unleashed/RogueMaster)**. The application will be optimized for the expanded features and API access provided by popular community distributions, while maintaining a baseline of compatibility.

## Phone Interface
- **Language**: **TypeScript/JavaScript**.
- **Technology**: **Web Bluetooth API**. This allows for a zero-install mobile experience where any smartphone with a modern browser can connect to the Flipper without needing a dedicated App Store download.

## Communication & Protocol
- **Transport**: **Bluetooth Low Energy (BLE)** using the Flipper's built-in Serial-over-BLE service.
- **Data Format**: **Custom Binary Protocol**. We use a lightweight custom binary format (e.g., [Type][Payload]) to minimize parsing overhead and latency between the Web Bluetooth dashboard and the Flipper app.

## USB Emulation
- **HID Profile**: **USB Composite Device**. The Flipper will present itself to the host as a standard USB Keyboard and a USB Mouse (and optionally a consumer control device for media keys).
- **Library**: **FuriHal USB**. We will use the Flipper's hardware abstraction layer for low-level USB descriptor management and report injection.
