# Spec: Mouse and Trackpad Support

## Goal
Enable full mouse control via the Web Dashboard, including relative movement and button clicks.

## Requirements
1. **Movement:** Send relative (dx, dy) movement from a virtual trackpad in the browser.
2. **Buttons:** Implement Left and Right click support.
3. **Protocol Update:** 
    - `0x02`: Mouse Movement `[Type, dx, dy]` (already defined).
    - `0x06`: Mouse Buttons `[Type, mask]` (New).
4. **Smoothness:** Ensure mouse movement is responsive and doesn't lag the Bluetooth pipe.

## Technical Details
- **USB HID:** Use `furi_hal_hid_mouse_move(dx, dy)` for movement and `furi_hal_hid_mouse_press(btn)` / `furi_hal_hid_mouse_release(btn)` for clicks.
- **Web UI:** A large touch-sensitive area acting as a trackpad.
    - Touch Move -> Relative Movement.
    - Tap -> Left Click.
    - Two-finger tap (or dedicated button) -> Right Click.

## Verification
1. Connect to Flipper.
2. Swipe on the web trackpad.
3. Computer cursor should move smoothly.
4. Click Left/Right buttons.
5. Computer should register clicks.
