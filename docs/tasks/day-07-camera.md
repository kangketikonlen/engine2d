# Day 7 — Camera System

## Goal
Separate world space from screen space.

## Learn
- Camera offset
- World-to-screen transform

## Trial, Error and Troubleshoot Note — Day 7 (Camera System)
- Camera logic introduced without additional rendering aids
- World space and screen space are now separated conceptually

- Core camera idea:
  - Objects live in **world space**
  - Rendering converts world space → screen space
  - Formula used:
    - `screenPos = worldPos - cameraPos`

- Camera follows the player:
  - Camera position is derived from player position
  - Player remains centered on screen
  - World coordinates change, screen coordinates stay stable

- Common confusion encountered:
  - With only one object and a flat background, camera movement is not visually obvious
  - This is expected and not a bug
  - Camera systems require reference points (grid, background, other objects) to be visually verified

- Key takeaway:
  - Camera is a mathematical offset, not a physical object
  - Correct camera logic can exist even if visual feedback is minimal

- Known limitation (intentional):
  - No world grid or background
  - No camera bounds or smoothing
  - No zoom or parallax

- Result:
  - Camera logic implemented correctly
  - World-to-screen transform established
  - Ready for future visual debugging or enhancements

## Deliverable
- Camera follows player
