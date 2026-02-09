# engine2d — Troubleshooting & Lessons Learned

This document records bugs, mistakes, edge cases, and design lessons
encountered during development, along with their causes and fixes.

Its purpose is long-term memory and pattern recognition.

---

## Day 2 — Frame Timing Confusion
**Issue**
- FPS output exceeded expected limits (~120 FPS)

**Cause**
- Frame limiting was not applied correctly

**Fix**
- Added explicit frame delay based on target frame time

**Lesson**
- Delta time and frame limiting solve different problems
- FPS must be measured after timing stabilization

---

## Day 6 — SDL2_image Linker Errors
**Issue**
- Linker errors: `undefined reference to IMG_*`

**Cause**
- SDL2_image headers included but library not linked

**Fix**
- Updated build command to include:
  - `pkg-config --cflags --libs sdl2 SDL2_image`

**Lesson**
- Compile-time success does not imply link-time success
- `undefined reference` almost always means a missing library

---

## Day 7 — Camera Appears to Do Nothing
**Issue**
- Camera logic worked conceptually but had no visible effect

**Cause**
- Only one object rendered
- Player always centered
- No visual reference for world movement

**Fix**
- Accepted as expected behavior
- Later reinforced with debug visualization

**Lesson**
- Camera systems require reference points to be visually verified
- Lack of feedback is not always a bug

---

## Day 8 — Collision Detection vs Resolution
**Issue**
- Objects overlapped but passed through each other

**Cause**
- Only detection implemented, no resolution

**Fix**
- Added explicit collision resolution in Day 9

**Lesson**
- Detection answers *if*
- Resolution answers *what to do about it*
- Never mix the two

---

## Day 9 — Unstable Collision Behavior
**Issue**
- Early jitter and snapping during movement

**Cause**
- Movement applied on both axes at once
- Ambiguous collision direction

**Fix**
- Implemented axis-separated movement
- Resolved collisions per axis

**Lesson**
- Axis separation simplifies resolution
- Sliding behavior emerges naturally

---

## Day 10 — Entity Identity Confusion
**Issue**
- Discomfort with entities being “just data”

**Cause**
- Expectation that identity and behavior live inside entities

**Resolution**
- Clarified that meaning is applied by systems, not data
- Accepted data-driven design

**Lesson**
- Entities are containers
- Systems define behavior and meaning

---

## Day 11 — Duplicate Texture Loads
**Issue**
- Same texture loaded multiple times for different entities

**Cause**
- Each entity owned its own texture

**Fix**
- Introduced TextureManager with caching
- Centralized ownership using RAII

**Lesson**
- Assets should be owned once and referenced many times
- Entities must not manage resource lifetime

---

## Day 12 — Accidental Reset Input
**Issue**
- Reset bound to keys near WASD (Q/R)
- High chance of accidental reset

**Cause**
- Destructive action mapped to high-frequency input area

**Fix**
- Rebound reset to Escape

**Lesson**
- Destructive actions must be physically distant from movement keys
- Input design is part of engine design

---

## Day 14 — Spawn Inside Collider
**Issue**
- Player spawned inside inner wall
- Immediate collision correction at frame 0
- Wayland input log appeared:
  - `imDefLkup.c,430: The application disposed a key event...`

**Cause**
- Invalid initial world state
- Collision system assumes previous frame was valid

**Fix**
- Moved player spawn point to a safe location:
  - `Vec2(0, 60)`

**Lesson**
- Scene initialization must always produce a valid state
- Collision systems are corrective, not curative
- Early-frame warnings often signal invalid setup

---

## General Patterns Observed

- Most bugs originate from invalid initial state
- Clear ownership prevents entire classes of errors
- Visual debugging drastically reduces guesswork
- Separating data from behavior improves flexibility

---

## Guiding Rule

> If something behaves strangely at runtime,  
> first question the **initial state**, not the system.
