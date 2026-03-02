# Changelog

All notable changes to this project will be documented in this file.

## [1.0.1] - 2026-03-02
### Added
- **Momentum Firmware Support**: Integrated build process for custom firmwares.
- **Custom Identity**: Device now identifies as `HID_[Name]` for professional branding.
- **Dedicated Pairing**: Added isolated key storage (`.bt_hid.keys`) for stable, interference-free connections.
- **Modifier Sync**: Dashboard now correctly clears Ctrl/Shift/Alt on key release.

### Fixed
- **Stability**: Fixed a critical crash on application exit.
- **Handshake**: Implemented self-healing Bluetooth connection to handle bonding drops.
- **Preload Fix**: Resolved "Invalid file" error by ensuring 100% compliant icon encoding.

## [1.0.0] - 2026-03-02
### Added
- Initial Release.
- Full Keyboard/Mouse USB HID Bridge.
- PWA Web Dashboard.
