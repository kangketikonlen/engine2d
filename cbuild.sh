#!/usr/bin/env bash
set -e

mkdir -p build

g++ src/main.cpp -o build/engine2d $(pkg-config --cflags --libs sdl2 SDL2_image)