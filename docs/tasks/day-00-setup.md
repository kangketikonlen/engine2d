# Day 0 — Environment Setup

## Goal
Confirm the toolchain works.

## Tasks
- Install C++ compiler (gcc or clang)
- Install SDL2 development libraries
- Install VS Code C++ extensions
- Create project structure:

```bash
engine2d/
├── build/
│ └── engine2d
├── include/
├── src/
│ └── main.cpp
├── cbuild.sh
├── crun.sh
└── README.md
```

## Trial, Error and Troubleshoot Note
- Install C++ toolchain:
  - `sudo dnf install -y gcc gcc-c++ make cmake`

- Install SDL2 development libraries:
  - `sudo dnf install -y SDL2 SDL2-devel`

- VS Code extensions:
  - **C/C++** (Microsoft)
  - **CMake Tools** (optional, for later)

- Build approach:
  - Avoid VS Code “Run / Build active file”
  - Use explicit build and run scripts instead

## Deliverable
- A `main.cpp` that compiles and runs

## Done When
- The program runs without errors
