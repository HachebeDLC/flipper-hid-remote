# Plan: Quality of Life Improvements v2

## Phase 1: Hardware Integration and Persistence
- [~] Task: Battery Level Reporting
    - [ ] Write tests for BLE battery service reporting.
    - [ ] Implement Battery Service in `ble_listener.c`.
    - [ ] Verify battery level appears on host device.
- [ ] Task: Config Storage Refinement
    - [ ] Write tests for saving/loading expanded config (BT name, accel enabled).
    - [ ] Update `settings.c/h` with new fields.
    - [ ] Implement dynamic Bluetooth Name selection from predefined list.
- [ ] Task: Conductor - User Manual Verification 'Hardware Integration and Persistence' (Protocol in workflow.md)

## Phase 2: Input Refinement and Settings UI
- [ ] Task: Mouse Acceleration Logic
    - [ ] Write tests for non-linear movement scaling.
    - [ ] Implement acceleration toggle and math in `hid_injector.c`.
- [ ] Task: Settings Menu Reorganization
    - [ ] Write tests for sub-menu navigation events.
    - [ ] Refactor `GuiManager` to support "Connectivity", "Input", and "Feedback" sub-menus.
- [ ] Task: Conductor - User Manual Verification 'Input Refinement and Settings UI' (Protocol in workflow.md)

## Phase 3: Web Dashboard Polish
- [ ] Task: Dashboard Settings Persistence
    - [ ] Write JS tests for localStorage save/load.
    - [ ] Implement `localStorage` for "Target OS" and "Sensitivity".
- [ ] Task: Web Themes and UI Polish
    - [ ] Implement Dark/Light mode toggle in `index.html`.
    - [ ] Add the Sensitivity slider and link to `app.js`.
- [ ] Task: Conductor - User Manual Verification 'Web Dashboard Polish' (Protocol in workflow.md)
