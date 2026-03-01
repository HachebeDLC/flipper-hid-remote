# Spec: Quality of Life Improvements

## Goal
Enhance user experience through persistence, customization, and better visual feedback.

## Requirements
1. **Persistence:** Save selected keyboard layout and haptics settings to `/ext/apps/USB/flipper_kb.conf`.
2. **Haptics Control:** Toggle vibration on/off via the Flipper menu.
3. **Dashboard Polish:** 
    - Add a Mouse Sensitivity slider.
    - Improve the layout for different screen sizes.
4. **Visual Feedback:** Show active modifiers (Ctrl, Alt, Shift) on the Flipper screen.

## Technical Details
- **Storage:** Use `Flipper-Furi` storage API to read/write a simple binary or text config file.
- **UI:** Expand the `VariableItemList` in `GuiManager` for settings.
- **Web:** Use `localStorage` to save the "Target OS" and "Sensitivity" choices in the browser.

## Verification
1. Change layout to `ES.kl`.
2. Close and restart the app.
3. Layout should still be `ES.kl`.
4. Adjust sensitivity and move mouse; should be noticeably different.
