# engine2d — Development Log

This log records development progress, milestones, and notable discoveries.
It is chronological and descriptive, not instructional.

---

## Day 0 — Environment Setup
- Installed C++ toolchain and SDL2 development libraries
- Set up build and run scripts (`cbuild.sh`, `crun.sh`)
- Avoided IDE build shortcuts in favor of explicit commands
- Confirmed minimal SDL program runs on Fedora

---

## Day 1 — Window & Main Loop
- Created SDL window and main loop
- Verified clean initialization and shutdown
- Confirmed event polling works correctly

---

## Day 2 — Timing & Delta Time
- Implemented delta time calculation
- Added frame limiting (~60 FPS)
- Verified frame-rate–independent loop behavior

---

## Day 3 — Input System
- Implemented event polling and keyboard state checks
- Distinguished between key press and key held
- Added WASD movement affecting game state

---

## Day 4 — Rendering Primitives
- Introduced SDL_Renderer
- Implemented clear / draw / present loop
- Rendered moving rectangle for visual feedback

---

## Day 5 — Basic Math (2D Vectors)
- Introduced `Vec2` for position and velocity
- Switched to velocity-based movement
- Established frame-independent motion model

---

## Day 6 — Sprite Rendering
- Integrated SDL2_image
- Loaded textures from disk
- Replaced primitives with sprite rendering
- Handled texture load failures correctly

---

## Day 7 — Camera System
- Separated world space from screen space
- Implemented camera offset
- Camera follows player position

---

## Day 8 — Collision Detection
- Implemented AABB collision checks
- Added bounding boxes in world space
- Verified overlap detection visually

---

## Day 9 — Collision Resolution
- Added axis-separated movement
- Implemented push-out collision resolution
- Enabled sliding behavior against walls

---

## Day 10 — Entity Management
- Introduced `Entity` as a data structure
- Managed entities via `std::vector`
- Centralized update and render loops

---

## Day 11 — Asset Management
- Implemented texture caching via TextureManager
- Ensured textures are loaded once and reused
- Clarified ownership using RAII

---

## Day 12 — Scene Reset
- Added scene reset functionality
- Cleared runtime state safely
- Reinitialized entities without restarting SDL
- Chose Escape key for reset during development

---

## Day 13 — Debug Tools
- Added toggleable debug rendering (F1)
- Visualized entity bounding boxes
- Improved confidence in collision and camera systems

---

## Day 14 — Mini Demo
- Built a small playable test level
- Added walls and collision
- Validated camera, input, debug tools, and reset
- Fixed spawn-inside-collider bug by moving player start position
- Confirmed engine foundation is stable

---

## Status

As of Day 14:
- Core engine systems are implemented
- Architecture is data-driven and minimal
- No major technical debt identified
- Ready to expand into world systems and gameplay