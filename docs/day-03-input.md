# Day 3 — Input System

## Goal
Correct keyboard handling.

## Learn
- Event polling
- Key pressed vs key held

## Trial, Error and Troubleshoot Note
- Input is handled inside the main loop
- Use **event polling** (`SDL_PollEvent`) for:
  - Window close
  - One-shot actions (key pressed / released)
  
- Use **keyboard state** (`SDL_GetKeyboardState`) for:
  - Continuous input (WASD movement)
  - Key held detection

- Do **not** use `SDL_KEYDOWN` for movement
  - Key repeat is OS-dependent
  - Leads to inconsistent movement

- Apply **delta time** to movement
  - `position += speed * deltaTime`
  - Makes movement frame-rate independent

- Keep input logic simple
  - No input abstraction yet
  - No action mapping yet

- Output state to console for validation
  - Confirms input and timing work together

## Deliverable
- WASD input affects state or movement
