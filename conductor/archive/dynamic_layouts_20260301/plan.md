# Plan: Dynamic Keyboard Layout Support

## Phase 1: Layout Engine implementation [checkpoint: 809e25d]
- [x] Task: Implement Layout Data Structure [809e25d]
    - [x] Define `LayoutTable` (128 x uint16_t).
    - [x] Implement `FlipperHidLayoutLoadDefault` (hardcoded US).
- [x] Task: Update `FlipperHidInjectKey` [809e25d]
    - [x] Replace `TranslateToSpanish` with a generic layout lookup.
    - [x] Convert `.kl` modifiers (8-bit) to `FuriHal` modifiers (shifted).

## Phase 2: File Loading logic [checkpoint: 809e25d]
- [x] Task: Implement `.kl` File Parser [809e25d]
    - [x] Use `Storage` API to read 256 bytes from a file into the active layout table.
- [x] Task: Layout Selection UI [809e25d]
    - [x] Add "Settings -> Keyboard Layout" to `GuiManager`.
    - [x] Implement a file browser starting in `/ext/badusb/assets/layouts/`.

## Phase 3: Integration and Verification [checkpoint: 809e25d]
- [x] Task: Integration Test [809e25d]
    - [x] Load a `.kl` file and verify character injection on a non-US host.
- [x] Task: Final Polish [809e25d]
    - [x] Show the active layout name on the Status screen.
    - [x] Ensure layout persists if possible.

## Phase 4: Verification and Checkpoint [checkpoint: 809e25d]
- [x] Task: Conductor - User Manual Verification 'Dynamic Keyboard Layout Support' [809e25d]
- [x] Task: Conductor - Checkpoint 'Dynamic Keyboard Layout Support' [809e25d]
