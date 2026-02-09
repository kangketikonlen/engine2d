# Day 12 — Scene Reset

## Goal
Reset game state safely.

## Learn
- Clearing state
- Reinitializing entities

## Trial, Error and Troubleshoot Note — Day 12 (Scene Reset & Input Choice)
- Scene reset implemented by:
  - Clearing runtime entity state
  - Reinitializing entities from a known configuration
  - Assets remain loaded and reused

- Reset trigger uses **event-based input**
  - `SDL_KEYDOWN` instead of held key state
  - Prevents repeated resets while a key is held

- Key binding decision:
  - Initially considered `R` / `Q`
  - Rejected due to proximity to **WASD**
    - Easy to press accidentally during movement
    - Feels punishing to players

- Final choice for now:
  - **Escape (`SDL_SCANCODE_ESCAPE`)**
  - Physically distant from movement keys
  - Requires deliberate action
  - Commonly treated as a “meta” key

- UX insight:
  - Destructive actions (reset, restart) should not be near high-frequency inputs
  - Accidental resets break player trust

- Design flexibility:
  - Key binding is easy to change later
  - Reset logic is decoupled from the specific key
  - Escape can later be reassigned to pause/menu

- Key takeaway:
  - Input design is part of system design
  - Technical correctness is not enough without usability

- Result:
  - Scene resets safely
  - Reset input feels intentional, not accidental

## Deliverable
- Press key to reset scene
