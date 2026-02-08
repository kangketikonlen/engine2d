# Day 4 — Rendering Primitives

## Goal
Draw something visible.

## Learn
- Renderer creation
- Clear / present
- Screen coordinates

## Trial, Error and Troubleshoot Note
- Create an `SDL_Renderer` from the window
  - Use `SDL_RENDERER_ACCELERATED`
  - Fail early if renderer creation fails

- Rendering loop structure (per frame):
  1. Handle events
  2. Update state (input + delta time)
  3. Clear screen (`SDL_RenderClear`)
  4. Draw primitives
  5. Present frame (`SDL_RenderPresent`)

- Screen coordinate system:
  - Origin `(0, 0)` is top-left
  - +X goes right
  - +Y goes down

- Use `SDL_SetRenderDrawColor` to control draw color
- Use `SDL_RenderFillRect` to draw a solid rectangle

- Convert float position to int when rendering
  - Simulation uses floats
  - Rendering uses pixel coordinates

- Keep rendering simple
  - No textures yet
  - No camera
  - No abstraction layer

## Deliverable
- Rectangle moves on screen
