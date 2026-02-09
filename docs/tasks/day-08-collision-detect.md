# Day 8 — Collision Detection

## Goal
Detect overlaps.

## Learn
- AABB collision checks
- Bounding boxes

## Trial, Error and Troubleshoot Note — Day 8 (Collision Detection)
- Collision detection introduced using **AABB (Axis-Aligned Bounding Boxes)**
- Each object is represented by:
  - Position `(x, y)`
  - Size `(width, height)`

- Core AABB overlap rule:
  - Two rectangles collide if their projections overlap on both axes
  - Conditions used:
    - `a.x < b.x + b.w`
    - `a.x + a.w > b.x`
    - `a.y < b.y + b.h`
    - `a.y + a.h > b.y`

- Collision is checked in **world space**
  - Camera offset is *not* involved in collision logic
  - Rendering converts world space → screen space afterward

- Visual feedback used for validation:
  - Obstacle changes color when collision occurs
  - Confirms detection without needing physics response

- Important distinction:
  - **Detection ≠ Resolution**
  - Day 8 only answers: *“Are these objects overlapping?”*

- Known limitations (intentional):
  - No collision response (no blocking or sliding)
  - No continuous collision detection
  - No rotated shapes

- Key takeaway:
  - Always detect collisions before trying to resolve them
  - Keep collision logic independent from rendering logic

- Result:
  - Overlap detection works reliably
  - Foundation laid for collision response in later days

## Deliverable
- Collision detection between objects
