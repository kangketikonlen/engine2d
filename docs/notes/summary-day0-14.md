# engine2d — Project Summary (Day 0–14)

This document summarizes the full foundation phase of **engine2d**, including
technical milestones, architectural decisions, and mental model shifts.

It represents a stable stopping point before Phase 2 (Day 15+).

---

## What Was Built

By Day 14, **engine2d** includes:

- SDL window creation and clean shutdown
- Deterministic main loop with delta time
- Frame-rate–independent movement
- Keyboard input (WASD)
- World space vs screen space separation
- Camera following the player
- AABB collision detection
- Axis-separated collision resolution (sliding)
- Entity management via `std::vector<Entity>`
- Asset management with texture caching (RAII)
- Scene reset without restarting SDL
- Toggleable debug rendering (collision boxes)
- A small playable mini demo with walls

This is a **real engine foundation**, not a toy loop.

---

## Key Architectural Decisions

- **Entities are data**
  - No behavior inside entities
  - Meaning is applied by systems

- **No ECS (yet)**
  - Current scale does not justify ECS complexity
  - Data-oriented thinking achieved without it

- **World logic is independent of rendering**
  - Simulation runs in world space
  - Rendering converts to screen space via camera

- **Collision detection ≠ collision resolution**
  - Detection answers “are we overlapping?”
  - Resolution restores invariants

- **Axis-separated movement**
  - Deterministic
  - Enables sliding naturally

- **Assets are owned by managers**
  - Loaded once
  - Reused across entities
  - Cleaned up via RAII

- **Scene reset is data reset**
  - Runtime state cleared
  - SDL and assets remain alive

- **Debug tools are first-class**
  - Invisible systems are visualized
  - Debug rendering is toggleable and non-intrusive

---

## Important Lessons Learned

- Most bugs originate from **invalid initial state**
- Collision systems assume the previous frame is valid
- Spawning inside colliders produces undefined behavior
- Compile success ≠ link success (SDL2_image case)
- Input design affects player trust
- Camera systems may appear “invisible” without reference points
- Modularization must isolate *stable logic*, not invent new abstractions

---

## Modularity Decision (Final)

Allowed and implemented:
