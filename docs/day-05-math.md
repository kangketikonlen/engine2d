# Day 5 — Basic Math (2D Vectors)

## Goal
Frame-independent movement.

## Learn
- `struct Vec2`
- Operator overloading
- Velocity-based motion

## Trial, Error and Troubleshoot Note
- Day 4 vs Day 5 distinction:
  - Day 4 focused on **visibility** (rendering a moving object)
  - Day 5 focused on **correct motion** (math and data model)

- Direct position updates (Day 4):
  - `position += speed * deltaTime`
  - Simple but tightly couples input and movement
  - Hard to extend with physics-like behavior

- Velocity-based movement (Day 5):
  - Input modifies **velocity**
  - Position is updated by:
    - `position += velocity * deltaTime`
  - This matches real-world motion and scales better

- Introduction of `Vec2`:
  - Groups related values (`x`, `y`)
  - Adds semantic meaning to data (position vs velocity)
  - Enables future operations (normalization, acceleration)

- Operator overloading:
  - Improves readability (`position += velocity * dt`)
  - Keeps math code concise without abstraction overhead

- Key takeaway:
  - Rendering shows *what* is happening
  - Math defines *why* and *how* it happens
  - Correct data flow: **Input → Velocity → Position**

- Known limitation (intentional):
  - Diagonal movement is faster
  - No normalization yet
  - This is acceptable for Day 5 and will be addressed later

## Deliverable
- Smooth movement independent of FPS
