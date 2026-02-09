# Day 2 — Timing & Delta Time

## Goal
Make the loop time-aware.

## Learn
- `SDL_GetTicks` or performance counters
- Delta time calculation
- Simple frame limiting

## Trial, Error and Troubleshoot Note
- Introduce `SDL_Renderer` to handle drawing
- Renderer is created from the window (`SDL_CreateRenderer`)
- Clear the screen every frame to make rendering visible
- Use a solid clear color to confirm the frame loop is running
- Rendering happens inside the main loop
- Call order per frame:
  1. Handle events
  2. Clear renderer
  3. Present renderer (`SDL_RenderPresent`)
- No abstractions yet
- Focus on making each frame visually obvious

## Deliverable
- FPS printed to console
