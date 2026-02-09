# engine2d

A minimal 2D game engine built step by step using **C++** and **SDL2**.

This repository is structured as a **learning-driven engine project**, where
each system is introduced intentionally and documented along the way.

---

## 📁 Project Structure
```bash
engine2d
├── assets
│   └── player.png
├── build
│   └── engine2d
├── docs
│   ├── notes
│   │   └── summary-day0-14.md
│   ├── tasks
│   │   ├── day-00-setup.md
│   │   ├── day-01-window-loop.md
│   │   ├── day-02-timing.md
│   │   ├── day-03-input.md
│   │   ├── day-04-rendering.md
│   │   ├── day-05-math.md
│   │   ├── day-06-sprites.md
│   │   ├── day-07-camera.md
│   │   ├── day-08-collision-detect.md
│   │   ├── day-09-collision-resolve.md
│   │   ├── day-10-entities.md
│   │   ├── day-11-assets.md
│   │   ├── day-12-scene-reset.md
│   │   ├── day-13-debug.md
│   │   ├── day-14-demo.md
│   │   ├── day-15-tile-map.md
│   │   ├── day-16-collision-layers.md
│   │   ├── day-17-triggers.md
│   │   ├── day-18-player-fsm.md
│   │   ├── day-19-animation.md
│   │   ├── day-20-game-states.md
│   │   └── day-21-polish.md
│   ├── curriculum.md
│   ├── decisions.md
│   ├── devlog.md
│   └── troubleshooting.md
├── include
├── src
│   └── main.cpp
├── README.md
└── run.sh
```

## 📌 Start Here

If you are new to this repository:

1. Read the **project roadmap**  
   → [`docs/curriculum.md`](docs/curriculum.md)

2. Follow development day by day  
   → [`docs/tasks/`](docs/tasks/)

3. Review architectural intent  
   → [`docs/decisions.md`](docs/decisions.md)

---

## 🗺️ Documentation Index

### Roadmap & Planning
- 📘 **Curriculum (Day 0–21)**  
  → [`docs/curriculum.md`](docs/curriculum.md)

- 🧩 **Daily Task Specs**  
  → [`docs/tasks/`](docs/tasks/)
  - Day 00 — Setup  
    → [`docs/tasks/day-00-setup.md`](docs/tasks/day-00-setup.md)
  - Day 01 — Window & Loop  
    → [`docs/tasks/day-01-window-loop.md`](docs/tasks/day-01-window-loop.md)
  - Day 02 — Timing  
    → [`docs/tasks/day-02-timing.md`](docs/tasks/day-02-timing.md)
  - Day 03 — Input  
    → [`docs/tasks/day-03-input.md`](docs/tasks/day-03-input.md)
  - Day 04 — Rendering  
    → [`docs/tasks/day-04-rendering.md`](docs/tasks/day-04-rendering.md)
  - Day 05 — Math  
    → [`docs/tasks/day-05-math.md`](docs/tasks/day-05-math.md)
  - Day 06 — Sprites  
    → [`docs/tasks/day-06-sprites.md`](docs/tasks/day-06-sprites.md)
  - Day 07 — Camera  
    → [`docs/tasks/day-07-camera.md`](docs/tasks/day-07-camera.md)
  - Day 08 — Collision Detection  
    → [`docs/tasks/day-08-collision-detect.md`](docs/tasks/day-08-collision-detect.md)
  - Day 09 — Collision Resolution  
    → [`docs/tasks/day-09-collision-resolve.md`](docs/tasks/day-09-collision-resolve.md)
  - Day 10 — Entities  
    → [`docs/tasks/day-10-entities.md`](docs/tasks/day-10-entities.md)
  - Day 11 — Assets  
    → [`docs/tasks/day-11-assets.md`](docs/tasks/day-11-assets.md)
  - Day 12 — Scene Reset  
    → [`docs/tasks/day-12-scene-reset.md`](docs/tasks/day-12-scene-reset.md)
  - Day 13 — Debug Tools  
    → [`docs/tasks/day-13-debug.md`](docs/tasks/day-13-debug.md)
  - Day 14 — Mini Demo  
    → [`docs/tasks/day-14-demo.md`](docs/tasks/day-14-demo.md)
  - Day 15 — Tile Map  
    → [`docs/tasks/day-15-tile-map.md`](docs/tasks/day-15-tile-map.md)
  - Day 16 — Collision Layers  
    → [`docs/tasks/day-16-collision-layers.md`](docs/tasks/day-16-collision-layers.md)
  - Day 17 — Triggers  
    → [`docs/tasks/day-17-triggers.md`](docs/tasks/day-17-triggers.md)
  - Day 18 — Player FSM  
    → [`docs/tasks/day-18-player-fsm.md`](docs/tasks/day-18-player-fsm.md)
  - Day 19 — Animation  
    → [`docs/tasks/day-19-animation.md`](docs/tasks/day-19-animation.md)
  - Day 20 — Game States  
    → [`docs/tasks/day-20-game-states.md`](docs/tasks/day-20-game-states.md)
  - Day 21 — Polish  
    → [`docs/tasks/day-21-polish.md`](docs/tasks/day-21-polish.md)

---

### Progress & History
- 🧾 **Development Log**  
  → [`docs/devlog.md`](docs/devlog.md)

- 🧪 **Troubleshooting & Lessons Learned**  
  → [`docs/troubleshooting.md`](docs/troubleshooting.md)

---

### Architecture & Design
- 🧠 **Architectural Decisions**  
  → [`docs/decisions.md`](docs/decisions.md)

---

## 🔧 Build & Run

### Dependencies (Fedora)
```bash
sudo dnf install -y gcc gcc-c++ make cmake SDL2 SDL2-devel SDL2_image SDL2_image-devel
```

---

### Build
```bash
./cbuild.sh
```

---

### Run
```bash
./run.sh
```
| On Fedora (Wayland), crun.sh forces SDL_VIDEODRIVER=x11

---

## 🧭 How to Use This Repository
- Use docs/tasks/ as your daily work guide
- Use devlog.md to record progress
- Use troubleshooting.md when something goes wrong
- Use decisions.md when questioning design choices

---

### Status
- Phase 1 (Day 0–14): ✅ Complete
- Phase 2 (Day 15–21): 🚧 In progress

---

### Philosophy
Build systems that make invalid states hard to represent. Clarity and correctness matter more than cleverness.

