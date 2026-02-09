# engine2d — Architectural Decisions

This document records key architectural decisions made during development,
including the reasoning behind them.

Its purpose is to preserve intent and prevent unnecessary redesigns later.

---

## Entities Are Data

**Decision**
- Entities are plain data structures
- No behavior, no inheritance, no virtual methods

**Reasoning**
- Behavior is applied by systems, not stored in entities
- Prevents inheritance explosions
- Enables flexible role changes (enemy ↔ NPC ↔ player)

**Implication**
- Meaning is contextual, not intrinsic
- Systems define identity through interaction

---

## No ECS (Yet)

**Decision**
- Do not introduce an Entity Component System prematurely

**Reasoning**
- Current scale does not justify ECS complexity
- ECS adds indirection, tooling needs, and debugging cost
- Data-oriented thinking is already achieved without ECS

**Revisit When**
- Systems require independent iteration
- Performance profiling demands it
- Tooling/editor support exists

---

## Data-Driven First

**Decision**
- Prefer data over hardcoded logic
- Scene initialization defines world state

**Reasoning**
- Reset, reload, and iteration become trivial
- Bugs often originate from invalid initial state
- Enables future level loading without refactors

---

## World Space vs Screen Space Separation

**Decision**
- All simulation occurs in world space
- Screen space exists only during rendering

**Reasoning**
- Camera should never affect physics
- Simplifies collision, AI, and logic
- Enables camera effects without breaking gameplay

---

## Axis-Separated Collision Resolution

**Decision**
- Move and resolve collisions per axis (X then Y)

**Reasoning**
- Eliminates ambiguity in collision response
- Enables sliding behavior naturally
- Simple and deterministic

**Trade-off**
- Does not handle tunneling or complex physics
- Accepted for current scope

---

## Collision Detection vs Resolution Separation

**Decision**
- Detection and resolution are separate steps

**Reasoning**
- Detection answers “are we overlapping?”
- Resolution answers “what do we do about it?”
- Mixing them causes fragile logic

---

## Asset Ownership via Managers (RAII)

**Decision**
- Assets are owned by managers
- Entities only reference assets

**Reasoning**
- Prevents duplicate loads
- Prevents memory leaks
- Centralizes lifetime management

**Implication**
- Asset reuse becomes trivial
- Entities remain lightweight

---

## Explicit Build and Run Scripts

**Decision**
- Use `cbuild.sh` and `crun.sh`
- Avoid IDE-managed build magic

**Reasoning**
- Build steps are explicit and debuggable
- Prevents toolchain confusion
- Works consistently across environments

---

## Debug Tools Are First-Class

**Decision**
- Debug rendering is built into the engine
- Toggleable at runtime

**Reasoning**
- Invisible systems are hard to trust
- Visual debugging shortens iteration loops
- Debug code should observe, not participate

---

## Input Design Is Part of Engine Design

**Decision**
- Destructive actions use distant keys (Escape, F-keys)

**Reasoning**
- Accidental resets destroy player trust
- Input layout affects usability, not just control

---

## Scene Reset Is Data Reset

**Decision**
- Reset clears runtime state only
- SDL subsystems and assets remain alive

**Reasoning**
- Faster iteration
- Avoids reinitialization bugs
- Matches real engine behavior

---

## No Premature Optimization

**Decision**
- Favor clarity over micro-optimization

**Reasoning**
- Correctness precedes performance
- Most early bottlenecks are architectural, not computational

---

## Guiding Principle

> Build systems that make invalid states hard to represent.

If a bug appears:
- Question initial state
- Question ownership
- Question space separation

Only then question the algorithm.
