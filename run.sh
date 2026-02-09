#!/usr/bin/env bash
set -e

# Force X11 on Fedora/Wayland
export SDL_VIDEODRIVER=x11

mkdir -p build

g++ src/main.cpp -o build/engine2d $(pkg-config --cflags --libs sdl2 SDL2_image)

./build/engine2d