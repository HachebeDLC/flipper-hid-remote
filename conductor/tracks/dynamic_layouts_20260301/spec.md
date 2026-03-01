# Spec: Dynamic Keyboard Layout Support

## Goal
Integrate Flipper Zero's BadUSB `.kl` layout files into the HID Bridge to support any keyboard language dynamically.

## Requirements
1. **Layout Table:** Implement a 128-entry (16-bit) mapping table in `hid_injector.c`.
2. **File Loader:** Create a function to load `.kl` files from `/ext/badusb/assets/layouts/`.
3. **UI Integration:** Add a "Layout" menu item to the GUI to browse and select `.kl` files.
4. **Fallback:** Use a hardcoded US-English layout if no file is loaded.
5. **Persistence:** Save the selected layout path so it persists across app restarts (optional but recommended).

## Technical Details
- Each entry in `.kl`: `uint16_t` (Low byte: Scancode, High byte: Modifiers).
- Modifier flags:
    - Bit 0: LCtrl
    - Bit 1: LShift
    - Bit 2: LAlt
    - Bit 3: LGUI
    - Bit 4: RCtrl
    - Bit 5: RShift
    - Bit 6: RAlt (AltGr)
    - Bit 7: RGUI
- Conversion to FuriHal modifiers: Shift layout modifiers left by 8 bits or map manually to `KEY_MOD_...`.

## Verification
1. Load `ES.kl` (Spanish).
2. Type `?` on the phone.
3. Computer should receive `?` correctly.
4. Switch to `FR.kl` (French).
5. Type `a` on the phone.
6. Computer should receive `q` (AZERTY mapping).
