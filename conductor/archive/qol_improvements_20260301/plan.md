# Plan: Quality of Life Improvements

## Phase 1: Settings Persistence [checkpoint: 78b3da2]
- [x] Task: Implement Config File Support [78b3da2]
    - [x] Define a simple config struct (layout path, vibro enabled).
    - [x] Implement `save_config` and `load_config` using Flipper Storage API.
- [x] Task: Auto-load on Startup [78b3da2]
    - [x] Ensure `GuiManagerAlloc` loads and applies the saved layout.

## Phase 2: Flipper UI and Haptics [checkpoint: 78b3da2]
- [x] Task: Haptics Toggle [78b3da2]
    - [x] Add "Vibration" ON/OFF item to settings.
    - [x] Respect this setting in `GuiManagerHandleBleData`.
- [x] Task: Visual Modifiers [78b3da2]
    - [x] Update the status screen to show icons/text for active Ctrl/Alt/Shift.

## Phase 3: Web Dashboard Enhancements [checkpoint: 78b3da2]
- [x] Task: Sensitivity Slider [78b3da2]
    - [x] Add UI slider to `index.html`.
    - [x] Apply multiplier to `pendingDX/DY` in `app.js`.
- [x] Task: LocalStorage Persistence [78b3da2]
    - [x] Save Target OS and Sensitivity in the browser.

## Phase 4: Verification and Checkpoint [checkpoint: 78b3da2]
- [x] Task: Conductor - User Manual Verification 'QoL Improvements' [78b3da2]
- [x] Task: Conductor - Checkpoint 'QoL Improvements' [78b3da2]
