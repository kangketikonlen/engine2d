#!/usr/bin/env bash
set -e

# Force X11 on Fedora/Wayland
export SDL_VIDEODRIVER=x11

./build/engine2d