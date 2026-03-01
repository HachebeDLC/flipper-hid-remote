# Plan: Quality of Life Improvements

## Phase 1: Settings Persistence
- [ ] Task: Implement Config File Support
    - Define a simple config struct (layout path, vibro enabled).
    - Implement `save_config` and `load_config` using Flipper Storage API.
- [ ] Task: Auto-load on Startup
    - Ensure `GuiManagerAlloc` loads and applies the saved layout.

## Phase 2: Flipper UI and Haptics
- [ ] Task: Haptics Toggle
    - Add "Vibration" ON/OFF item to settings.
    - Respect this setting in `GuiManagerHandleBleData`.
- [ ] Task: Visual Modifiers
    - Update the status screen to show icons/text for active Ctrl/Alt/Shift.

## Phase 3: Web Dashboard Enhancements
- [ ] Task: Sensitivity Slider
    - Add UI slider to `index.html`.
    - Apply multiplier to `pendingDX/DY` in `app.js`.
- [ ] Task: LocalStorage Persistence
    - Save Target OS and Sensitivity in the browser.

## Phase 4: Verification and Checkpoint
- [ ] Task: Conductor - User Manual Verification 'QoL Improvements'
- [ ] Task: Conductor - Checkpoint 'QoL Improvements'
