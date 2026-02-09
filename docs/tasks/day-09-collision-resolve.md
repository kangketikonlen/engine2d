# Day 9 — Collision Resolution

## Goal
Prevent overlap.

## Learn
- Axis separation
- Minimal push-out logic

## Trial, Error and Troubleshoot Note — Day 9 (Collision Resolution)
- Collision system is split into two distinct phases:
  - **Detection**: checks whether two objects overlap
  - **Resolution**: corrects position to remove overlap
  - These two concerns must not be mixed

- Collision shape used:
  - Axis-Aligned Bounding Boxes (AABB)
  - Rectangles aligned to world axes
  - Collision is equivalent to checking overlap on X and Y axes separately

- Axis-separated movement:
  - Movement is applied one axis at a time
    - Move on X → resolve collisions
    - Move on Y → resolve collisions
  - This avoids ambiguity about which axis caused the collision
  - Enables sliding behavior naturally

- Push-out (snap) resolution:
  - When overlap occurs, player is snapped flush against the obstacle
  - Resolution depends on movement direction:
    - Moving right → snap to left side of obstacle
    - Moving left → snap to right side
    - Same logic applies for Y axis
  - Ensures zero overlap after resolution (critical invariant)

- Why snapping is used instead of undoing movement:
  - Undoing movement is imprecise due to floating-point error
  - Snapping guarantees deterministic and stable positioning

- Collision logic operates strictly in **world space**
  - Camera offset is never involved in collision checks
  - Rendering converts world space → screen space afterward

- Emergent behavior:
  - Sliding along walls happens automatically
  - No special “sliding” logic is required

- Known limitations (intentional):
  - Fast movement can cause tunneling
  - Only one obstacle handled cleanly
  - No penetration depth calculation
  - No physics forces or responses

- Key takeaway:
  - Collision resolution is about restoring invariants
  - Invariant enforced: *the player must never overlap obstacles*
  - Simple, deterministic rules beat complex physics early on

## Deliverable
- Player stops or slides against walls
