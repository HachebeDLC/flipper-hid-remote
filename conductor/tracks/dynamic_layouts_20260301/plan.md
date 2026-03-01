# Plan: Dynamic Keyboard Layout Support

## Phase 1: Layout Engine implementation
- [ ] Task: Implement Layout Data Structure
    - Define `LayoutTable` (128 x uint16_t).
    - Implement `FlipperHidLayoutLoadDefault` (hardcoded US).
- [ ] Task: Update `FlipperHidInjectKey`
    - Replace `TranslateToSpanish` with a generic layout lookup.
    - Convert `.kl` modifiers (8-bit) to `FuriHal` modifiers (shifted).

## Phase 2: File Loading logic
- [ ] Task: Implement `.kl` File Parser
    - Use `Storage` API to read 256 bytes from a file into the active layout table.
- [ ] Task: Layout Selection UI
    - Add "Settings -> Keyboard Layout" to `GuiManager`.
    - Implement a file browser starting in `/ext/badusb/assets/layouts/`.

## Phase 3: Integration and Verification
- [ ] Task: Integration Test
    - Load a `.kl` file and verify character injection on a non-US host.
- [ ] Task: Final Polish
    - Show the active layout name on the Status screen.
    - Ensure layout persists if possible.

## Phase 4: Verification and Checkpoint
- [ ] Task: Conductor - User Manual Verification 'Dynamic Keyboard Layout Support'
- [ ] Task: Conductor - Checkpoint 'Dynamic Keyboard Layout Support'
