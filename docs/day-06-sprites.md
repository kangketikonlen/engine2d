# Day 6 — Sprite Rendering

## Goal
Render textures.

## Learn
- Loading textures
- Handling load failures
- Texture lifetime

## Trial, Error and Troubleshoot Note — Day 6 (Sprite Rendering)
- Need to install SDL2_image and SDL2_image-devel in Fedora.
- Issue encountered:
  - Linker errors: `undefined reference to IMG_*`
  - Errors occurred even though headers compiled correctly

- Root cause:
  - `SDL2_image` was **included** but not **linked**
  - `#include <SDL2/SDL_image.h>` is not sufficient by itself

- Fix applied:
  - Update build script to link SDL2_image explicitly:
    - `pkg-config --cflags --libs sdl2 SDL2_image`
  - Ensure `SDL2_image` and `SDL2_image-devel` are installed on Fedora

- Key takeaway:
  - Compile-time success ≠ link-time success
  - `undefined reference` errors almost always mean:
    - Missing library in the linker step

- Texture lifecycle learned:
  - `IMG_Init` → must be paired with `IMG_Quit`
  - `IMG_LoadTexture` → must be paired with `SDL_DestroyTexture`
  - Destruction order matters:
    1. Destroy textures
    2. Destroy renderer
    3. Destroy window
    4. Quit SDL_image
    5. Quit SDL

- Result:
  - Sprite loads successfully
  - Sprite renders correctly
  - WASD movement works with textures
  - Program exits cleanly

## Deliverable
- Player sprite rendered
