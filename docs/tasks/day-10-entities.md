# Day 10 — Entity Management

## Goal
Manage multiple objects.

## Learn
- `std::vector<Entity>`
- Lifetime basics

## Trial, Error and Troubleshoot Note — Day 10 (Entity Management)
- Introduced the concept of **entities as data**
  - Each entity stores position, velocity, size, and texture
  - No behavior is embedded in the entity itself

- Used `std::vector<Entity>` to manage multiple objects
  - Allows dynamic growth (add/remove entities)
  - Provides clear ownership and lifetime
  - Good default container for games

- Shift in code structure:
  - From hard-coded single objects
  - To loops that update and render collections of entities

- Input handling:
  - Input affects only the first entity (player)
  - Other entities remain static or controlled by other logic later

- Camera logic:
  - Camera follows the player entity
  - Rendering uses world-to-screen conversion for all entities

- Key takeaway:
  - Scaling object count should not increase code complexity linearly
  - Centralized update/render loops are essential

- Important design insight:
  - Avoid adding inheritance or ECS too early
  - Data-first design keeps behavior flexible

- Known limitations (intentional):
  - No entity IDs or tagging
  - No removal during iteration
  - No collision handling between entities yet

- Result:
  - Multiple entities update and render correctly
  - Foundation laid for entity interaction and systems

## Deliverable
- Multiple entities updated and rendered
