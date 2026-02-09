# engine2d — Curriculum

This document defines the learning and development roadmap for **engine2d**.
Each day builds on previous systems without rewrites or premature abstraction.

---

## Phase 1 — Foundations (Day 0–14) ✅

### Day 0 — Environment Setup
- Toolchain installation
- SDL2 setup
- Build/run scripts

### Day 1 — Window & Main Loop
- SDL initialization
- Main loop
- Clean shutdown

### Day 2 — Timing & Delta Time
- Frame timing
- Delta time calculation
- FPS limiting

### Day 3 — Input System
- Event polling
- Key pressed vs key held
- WASD movement

### Day 4 — Rendering Primitives
- SDL_Renderer
- Clear / present
- Screen coordinates

### Day 5 — Basic Math (2D Vectors)
- Vec2 struct
- Velocity-based movement
- Frame-independent motion

### Day 6 — Sprite Rendering
- Texture loading
- SDL2_image
- Texture lifetime

### Day 7 — Camera System
- World space vs screen space
- Camera offset
- Camera follows player

### Day 8 — Collision Detection
- AABB collision checks
- Bounding boxes
- Overlap detection

### Day 9 — Collision Resolution
- Axis-separated movement
- Push-out resolution
- Sliding behavior

### Day 10 — Entity Management
- Entity as data
- std::vector<Entity>
- Centralized update/render loops

### Day 11 — Asset Management
- Texture caching
- Resource reuse
- RAII ownership

### Day 12 — Scene Reset
- Clearing runtime state
- Reinitializing entities
- Safe reset via input

### Day 13 — Debug Tools
- Debug rendering
- Collision box visualization
- Toggleable overlays

### Day 14 — Mini Demo
- Small playable level
- Player movement
- Walls and collision
- Debug + reset validation

---

## Phase 2 — World & Interaction (Day 15–21)

### Day 15 — Tile Maps
- Grid-based world data
- Tile → collider generation
- Data-driven levels

### Day 16 — Collision Layers
- Collision filtering
- Layer / mask rules
- Selective resolution

### Day 17 — Triggers & Interactions
- Trigger volumes
- Overlap events
- Non-blocking interactions

### Day 18 — Player State Machine
- Explicit player states
- Idle / moving separation
- State-driven logic

### Day 19 — Sprite Animation
- Sprite sheets
- Frame timing
- State → animation mapping

### Day 20 — Game States
- Menu vs gameplay
- High-level state control
- Input gating

### Day 21 — Polish & Validation
- Stress testing
- Debug verification
- Invariant cleanup
- Stability pass

---

## Scope Rules

- No ECS before systems demand it
- No editor before data stabilizes
- No rewrites unless a system breaks
- Prefer clarity over cleverness

---

## Goal

By the end of Phase 2, **engine2d** should be:
- Stable
- Data-driven
- Playable
- Extensible without architectural debt