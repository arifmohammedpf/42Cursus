# cub3D — Introduction & Architecture Overview

Welcome to the cub3D Study Materials! This guide is designed to help you understand every aspect of the cub3D project, from high-level architecture to low-level mathematics and implementation details.

---

## 1. What is cub3D?

**cub3D** is a graphics project at 42 where you build a pseudo-3D first-person game engine from scratch using C and the **MiniLibX (MLX)** library. The engine works similarly to retro 3D games like *Wolfenstein 3D* (1992).

### The Core Paradigm: Raycasting
Computers in the early 90s were too slow to render true 3D polygon meshes. Instead, they used **raycasting**:
- The game map is a flat 2D grid of walls (`1`) and empty spaces (`0`).
- The player is a 2D point moving on this grid with a viewing angle.
- For each vertical line on the screen, the engine shoots a "ray" (a mathematical line) from the player's position outward.
- When a ray hits a wall, the distance is calculated.
- The height of the wall slice drawn on the screen is inversely proportional to this distance (closer walls look taller; farther walls look smaller).

---

## 2. High-Level Architecture & Workflow

The execution of cub3D is divided into three distinct phases:

### Phase 1: Parse & Validate (The Gatekeeper)
- Checks if the input file has a `.cub` extension.
- Reads the file line-by-line using `get_next_line`.
- Extracts texture file paths (North, South, West, East) and RGB colors (Floor, Ceiling).
- Validates that the map is fully enclosed by walls (`1`) using a boundary search, has exactly one player start position (`N`, `S`, `E`, `W`), and contains only valid characters.

### Phase 2: Initialization (The Constructor)
- Starts the MLX library, creates a connection to the display server, and opens a `1200 x 700` pixel window.
- Loads the `.xpm` texture images into memory and extracts their raw pixel address buffers.
- Allocates the raycasting array (`1200` rays, one for each column of the screen).
- Sets up the hook functions to capture keyboard inputs and window close events.

### Phase 3: The Game Loop (The Engine)
- The program hands control to MLX via `mlx_loop()`.
- Every frame, MLX calls the `game_loop()` callback, which:
  - Measures time elapsed since the last frame (`delta_time`) to ensure smooth, frame-independent movement.
  - Updates player position based on key inputs, checking for wall collisions.
  - Performs raycasting to calculate distance to walls and which texture column to sample.
  - Renders floor/ceiling, projects the 3D walls, draws the minimap, and pushes the final image to the window.

---

## 3. Directory Map of the Codebase

Here is how the source code is organized, excluding external helper libraries:

* **`includes/`**
  * [cub3d.h](file:///c:/42AD/staff-evaluation/cub3d/includes/cub3d.h) — The main header containing library includes, key macros, enums, and all function prototypes.
  * [structures.h](file:///c:/42AD/staff-evaluation/cub3d/includes/structures.h) — Holds all the C structure definitions used to model the game state.
* **`src/`**
  * [main.c](file:///c:/42AD/staff-evaluation/cub3d/src/main.c) — The entry point of the executable.
  * **`src/core/`** — Core orchestration, initialization, hook setups, and exit routines.
  * **`src/engine/`** — Mathematical engines: DDA raycaster and player movement handlers.
  * **`src/parsing/`** — Config file reading, string trimming, tab expansion, and color parsing.
  * **`src/parsing/validation/`** — Integrity checks for textures, colors, map boundaries, and characters.
  * **`src/rendering/`** — Direct pixel manipulations, wall texture scaling, ceiling/floor coloring, and minimap rendering.

---

## 4. Key Concept Primers

Before diving into the code, keep these core concepts in mind:

### The Grid Coordinate System
* The 2D map uses standard grid coordinates where **`x` increases to the right** and **`y` increases downwards**.
* In C arrays, this is represented as `map[y][x]` (or `map[row][col]`).
* Player coordinates are floats (e.g. `x = 4.5`, `y = 5.5` means the player is in the center of tile `(4, 5)`).
* For sub-tile math inside the raycaster, coordinates are scaled by `TILE_SIZE` (1024) to allow high-precision fractional calculations without floating-point inaccuracies.

### Angles and Radians
* Angles are measured in radians from the positive X-axis (facing East):
  * **`0` or `2π`**: East (Right)
  * **`π/2`**: South (Down)
  * **`π`**: West (Left)
  * **`3π/2`**: North (Up)

### Field of View (FOV) and Rays
* The player has a Field of View (FOV) of **`60°`** (`π/3` radians).
* The screen is `1200` pixels wide, so the engine casts **`1200` individual rays**.
* The rays are distributed evenly across the `60°` arc: from `player_angle - 30°` to `player_angle + 30°`.

### Perpendicular Distance vs. Fisheye Distortion
* If we measure the raw diagonal distance from the player to the point where a ray hits a wall, the screen will look distorted (like a round fishbowl). This is because walls at the edges of our screen are mathematically farther away from the eye than walls in the center, even if we are looking straight at a flat wall.
* To fix this, we project the diagonal distance onto the player's viewing direction vector. We multiply the raw distance by the cosine of the difference between the ray's angle and the player's viewing angle:
  $$\text{distance} = \text{raw\_distance} \times \cos(\text{ray\_angle} - \text{player\_angle})$$
* This corrected **perpendicular distance** is what we use to calculate the height of wall slices, producing a flat, natural-looking 3D perspective.

---

## Next Steps

Now that you have a high-level view of the project and its core ideas, let's examine the **data structures** that hold the game's state.

👉 Proceed to [01_Header_Files_and_Data_Structures.md](./01_Header_Files_and_Data_Structures.md)
