# Day 1 — Window & Main Loop

## Goal
Open a window and keep it alive.

## Learn
- `main()`
- SDL initialization and shutdown
- Basic game loop

## Trial, Error and Troubleshoot Note
- Fedora (Wayland) note:
  - SDL2 windows may be created but not visible
  - Force X11 for development:
    - `export SDL_VIDEODRIVER=x11`
  - Applied in `crun.sh` to ensure window visibility

## Deliverable
- 800×600 window
- Clean exit on window close

## Notes
Do not add abstractions yet.
