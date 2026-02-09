# Day 14 — Mini Demo

## Goal
Small playable test.

## Tasks
- Build tiny level
- Player movement
- Walls and collision

## Trial, Error and Troubleshoot Note — Day 14 (Mini Demo)

- Initial issue encountered:
  - Player spawned at `(0, 0)`
  - Inner wall also occupied the origin
  - Player started **inside a collider**

- Symptoms observed:
  - Immediate collision resolution at frame 0
  - Unstable behavior on startup
  - Wayland input log message:
    - `imDefLkup.c,430: The application disposed a key event...`
  - Log was not fatal, but indicated invalid early state

- Root cause:
  - Scene initialization produced an **invalid world state**
  - Collision resolution assumes the previous frame is valid
  - Spawning inside colliders breaks this assumption

- Fix applied:
  - Moved player spawn point to a safe location:
    - `Vec2(0, 60)`
  - Ensures no overlap with any wall at start

- Why this fix is correct:
  - Spawn position is **scene data**, not system logic
  - No collision code was modified
  - Reset behavior remains consistent
  - Engine assumptions remain intact

- Engine design lesson:
  - Scene initialization must always produce a valid state
  - Collision systems are corrective, not curative
  - Invalid initial states lead to undefined or platform-specific behavior

- Best practices established:
  - Never spawn entities inside colliders
  - Validate spawn points during scene setup
  - Treat early-frame warnings as signals, not noise

- Result:
  - Mini demo is stable and playable
  - Player movement and collision behave correctly
  - Debug tools remain useful and accurate
  - Day 14 demo fulfills its goal as a proof of engine foundation

## Deliverable
- Playable demo using engine2d
