# Day 13 — Debug Tools

## Goal
Make invisible systems visible.

## Learn
- Debug rendering
- Conditional drawing

## Trial, Error and Troubleshoot Note — Day 13 (Debug Tools)
- Debug tools introduced to visualize otherwise invisible systems
  - Collision bounds
  - Entity extents
  - Camera-related alignment

- Debug rendering principles:
  - Visual-only
  - Must not affect gameplay logic
  - Must be easy to toggle on/off

- Implementation details:
  - Added `debugDraw` boolean flag
  - Toggled using **F1** via event-based input
  - Prevents repeated toggling while key is held

- Debug rendering behavior:
  - Draws wireframe rectangles around entities
  - Uses world-to-screen transform (`position - camera`)
  - Rendered after normal sprites to ensure visibility

- Input choice rationale:
  - F1 is:
    - Physically distant from WASD
    - Non-destructive
    - Commonly used for debug/help

- Key insight:
  - If a system cannot be visualized, it is difficult to trust or debug
  - Debug rendering acts as a “truth layer” for engine state

- Design discipline:
  - Debug code is conditional and isolated
  - No gameplay logic depends on debug state

- Result:
  - Collision and spatial data can be inspected at runtime
  - Debugging becomes faster and more reliable


## Deliverable
- Toggle collision boxes or debug overlay
