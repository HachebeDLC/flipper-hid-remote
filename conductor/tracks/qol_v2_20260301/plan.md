# Plan: Quality of Life Improvements v2

## Phase 1: Hardware Integration and Persistence [checkpoint: 49ca972]
- [x] Task: Battery Level Reporting [49ca972]
    - [x] Write tests for BLE battery service reporting.
    - [x] Implement Battery Service in `ble_listener.c`.
    - [x] Verify battery level appears on host device.
- [x] Task: Config Storage Refinement [49ca972]
    - [x] Write tests for saving/loading expanded config.
    - [x] Update `settings.c/h` with new fields.
    - [x] Implement dynamic Layout selection from main menu.
- [x] Task: Conductor - User Manual Verification 'Hardware Integration and Persistence' (Protocol in workflow.md) [49ca972]

## Phase 2: Input Refinement and Settings UI [checkpoint: 49ca972]
- [x] Task: Mouse Acceleration Logic [49ca972]
    - [x] Write tests for non-linear movement scaling.
    - [x] Implement acceleration toggle and math in `hid_injector.c`.
- [x] Task: Settings Menu Reorganization [49ca972]
    - [x] Write tests for sub-menu navigation events.
    - [x] Refactor `GuiManager` to a flat, stable settings list.
    - [x] Added Visual Modifier icons to status header.
- [x] Task: Conductor - User Manual Verification 'Input Refinement and Settings UI' (Protocol in workflow.md) [49ca972]

## Phase 3: Web Dashboard Polish [checkpoint: 49ca972]
- [x] Task: Dashboard Settings Persistence [49ca972]
    - [x] Write JS tests for localStorage save/load.
    - [x] Implement `localStorage` for "Target OS" and "Sensitivity".
- [x] Task: Web Themes and UI Polish [49ca972]
    - [x] Implement Dark/Light mode toggle in `index.html`.
    - [x] Add the Sensitivity slider and link to `app.js`.
- [x] Task: Conductor - User Manual Verification 'Web Dashboard Polish' (Protocol in workflow.md) [49ca972]

## Phase: Review Fixes
- [x] Task: Apply review suggestions [c5f064f]
