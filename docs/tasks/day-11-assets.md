# Day 11 — Asset Management

## Goal
Avoid duplicate resource loads.

## Learn
- Resource caching
- Ownership and cleanup (RAII)

## Trial, Error and Troubleshoot Note — Day 11 (Asset Management)
- Problem identified:
  - Loading textures per entity causes:
    - Duplicate disk I/O
    - Duplicate GPU textures
    - Higher memory usage
    - Complicated cleanup logic

- Core fix introduced:
  - Centralized **TextureManager**
  - Textures are loaded once and cached by file path
  - Subsequent requests reuse the same `SDL_Texture*`

- Key rule established:
  - **Entities do not own assets**
  - Entities only *reference* textures
  - Asset lifetime is managed elsewhere

- Practical example:
  - 10 enemies using the same sprite:
    - Before: 10 texture loads
    - After: 1 texture load, 10 references
  - Same logic applies to NPCs, props, UI, etc.

- Ownership model:
  - TextureManager:
    - Owns all textures
    - Responsible for loading and destruction
    - Uses RAII to clean up automatically
  - Entity:
    - Holds a non-owning `SDL_Texture*`
    - Never destroys textures

- Why this is safe:
  - `SDL_Texture` is read-only during rendering
  - Multiple entities can share the same texture without conflict
  - Destruction happens once, at shutdown

- Conceptual takeaway:
  - Visual identity is separate from behavior
  - Many entities can look the same but behave differently
  - Meaning is defined by systems, not by data ownership

- Result:
  - No duplicate texture loads
  - Clear ownership and cleanup
  - Asset usage scales cleanly with entity count

## Deliverable
- Textures loaded once and reused
