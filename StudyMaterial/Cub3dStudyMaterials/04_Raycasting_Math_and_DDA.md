# cub3D — Raycasting Math & DDA Engine

This document explains the mathematical foundations and code implementation of the **Digital Differential Analysis (DDA)** raycasting engine. These functions reside in [src/engine/ray_casting.c](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_casting.c), [ray_horz.c](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_horz.c), [ray_vert.c](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_vert.c), and [ray_utils.c](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_utils.c).

---

## 1. What is Digital Differential Analysis (DDA)?

To draw the walls in 3D, we need to know exactly where the player's view lines intersect a wall tile on the map.
A naive approach would step along the ray in tiny fractions (e.g. `0.01` tiles at a time) and check if that point is inside a wall. This is **extremely slow** and can skip corners or clip through wall edges.

**DDA** is a fast, highly accurate grid-traversal algorithm. Instead of stepping by constant small distances, we project the ray onto the grid and hop from one grid line to the next.
Since walls are aligned on grid boundaries, a ray can only hit a wall at a grid intersection.
- **Horizontal intersections:** Checking where the ray crosses horizontal grid lines ($y = 0, 1, 2, ...$).
- **Vertical intersections:** Checking where the ray crosses vertical grid lines ($x = 0, 1, 2, ...$).

The algorithm calculates both paths separately, steps through them until a wall is hit, and then chooses the closer intersection point.

```
Horizontal Stepping (ray_horz.c)             Vertical Stepping (ray_vert.c)
      ┌───┬───┬───┬───┐                            ┌───┬───┬───┬───┐
      │   │   │   │   │                            │   │   │   │   │
      ├───┼───┼───┼───┤                            ├───┼───┼───┼───┤
      │   │   │   │ * │ (Hit!)                     │   │   │ * │   │ (Hit!)
      ├───┼───┼─*─┼───┤                            ├───┼─*─┼───┼───┤
      │   │ * │   │   │                            │ * │   │   │   │
      ├──*┼───┼───┼───┤                            ├─*─┼───┼───┼───┤
      │ P │   │   │   │                            │ P │   │   │   │
      └───┴───┴───┴───┘                            └───┴───┴───┴───┘
      (steps along horizontal lines)               (steps along vertical lines)
```

---

## 2. Core Raycasting Orchestrator (`src/engine/ray_casting.c`)

### [cast_all_rays](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_casting.c#L15-L35)
* **What it is for:** Casts 1200 individual rays across the player's $60^\circ$ Field of View.
* **Why it is needed:** Populates the ray array with the distance and hit metadata needed to render the screen.
* **How it works:**
  1. Computes `angle_diff` = `fov_angle / 1200` (about $0.05^\circ$ per ray).
  2. Sets the starting `ray_angle` to `player->viewangle - (fov_angle / 2)` (the leftmost edge of the screen).
  3. Iterates from column `0` to `1199`:
     - Normalizes the `ray_angle` to stay between $0$ and $2\pi$.
     - Calls `get_ray_direction` to set the movement flags.
     - Calls `find_horz_intersection` to get the distance to the closest horizontal wall collision.
     - Calls `find_vert_intersection` to get the distance to the closest vertical wall collision.
     - Calls `get_small_wall_hit` to compare the two distances and save the details.
     - Increments `ray_angle` by `angle_diff` to move to the next screen column.

---

## 3. Horizontal Grid Traversal (`src/engine/ray_horz.c`)

This file handles checking intersections with horizontal grid lines ($y$-lines).
Note: To maintain precision, all math inside this file is multiplied by `TILE_SIZE` (1024).

### [find_horz_intercept](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_horz.c#L15-L24)
* **What it is for:** Calculates the first horizontal line intersection point.
* **Why it is needed:** Establishes the starting point for the DDA loop.
* **How it works:**
  * **Y-Intercept:** If the ray is facing down, the intercept is the floor of the player's Y coordinate plus one tile. If facing up, it is the floor of the player's Y coordinate.
    $$\text{intercept.y} = \lfloor\text{player.y}\rfloor \times 1024 + (\text{facing\_down} ? 1024 : 0)$$
  * **X-Intercept:** Uses trigonometry to project the X coordinate relative to the Y change:
    $$\text{intercept.x} = \text{player.x} \times 1024 + \frac{\text{intercept.y} - \text{player.y} \times 1024}{\tan(\text{ray\_angle})}$$

### [find_horz_step](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_horz.c#L26-L39)
* **What it is for:** Calculates the step size ($dx, dy$) between horizontal lines.
* **Why it is needed:** Provides the offsets to hop to the next line.
* **How it works:**
  * **Step Y:** The step is exactly `TILE_SIZE` (1024), negative if the ray faces up, positive if it faces down.
  * **Step X:** Calculated using trigonometry:
    $$\text{step.x} = \frac{1024}{\tan(\text{ray\_angle})}$$
  * Ensures that if the ray points left, `step.x` is negative, and if it points right, `step.x` is positive.

### [find_horz_intersection](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_horz.c#L58-L79)
* **What it is for:** Steps through horizontal intersections until a wall is hit.
* **Why it is needed:** Finds the horizontal boundary collision distance.
* **How it works:**
  1. Computes the starting intercept and steps.
  2. Runs a loop that checks `is_within_horz_bounds`.
  3. Inside the loop, calls `check_horz_wall_hit`.
     - *Important Detail:* If the ray faces up, we check Y coordinate `ray->horzwallhit.y - 1` because the wall is in the grid row *above* the intersection line.
  4. If a wall is hit, sets `gethorhit = 1` and breaks the loop.
  5. Otherwise, adds `step.x` and `step.y` to the coordinates and continues.
  6. Returns the distance using `get_dis`.

---

## 4. Vertical Grid Traversal (`src/engine/ray_vert.c`)

This file handles checking intersections with vertical grid lines ($x$-lines).

### [find_vert_intercept](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_vert.c#L15-L24)
* **What it is for:** Calculates the first vertical line intersection point.
* **Why it is needed:** Establishes the starting point for the vertical DDA loop.
* **How it works:**
  * **X-Intercept:**
    $$\text{intercept.x} = \lfloor\text{player.x}\rfloor \times 1024 + (\text{facing\_right} ? 1024 : 0)$$
  * **Y-Intercept:**
    $$\text{intercept.y} = \text{player.y} \times 1024 + (\text{intercept.x} - \text{player.x} \times 1024) \times \tan(\text{ray\_angle})$$

### [find_vert_step](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_vert.c#L26-L39)
* **What it is for:** Calculates the step size ($dx, dy$) between vertical lines.
* **Why it is needed:** Provides the offsets to hop to the next line.
* **How it works:**
  * **Step X:** The step is exactly `TILE_SIZE` (1024), negative if the ray faces left, positive if it faces right.
  * **Step Y:** Calculated using trigonometry:
    $$\text{step.y} = 1024 \times \tan(\text{ray\_angle})$$
  * Adjusts the sign of `step.y` to match whether the ray points up or down.

### [find_vert_intersection](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_vert.c#L58-L80)
* **What it is for:** Steps through vertical intersections until a wall is hit.
* **Why it is needed:** Finds the vertical boundary collision distance.
* **How it works:**
  1. Computes the starting intercept and steps.
  2. Runs a loop that checks `is_within_vert_bounds`.
  3. Inside the loop, calls `check_vert_wall_hit`.
     - *Important Detail:* If the ray faces left, we check X coordinate `ray->vertwallhit.x - 1` because the wall is in the grid column *left* of the intersection line.
  4. If a wall is hit, sets `getverthit = 1` and breaks the loop.
  5. Otherwise, adds `step.x` and `step.y` to the coordinates and continues.
  6. Returns the distance using `get_dis`.

---

## 5. Raycasting Utilities (`src/engine/ray_utils.c`)

### [normangle](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_utils.c#L15-L21)
* **What it is for:** Normalizes any angle to stay between $0$ and $2\pi$ radians.
* **Why it is needed:** Angles wrap around as the player rotates. This function keeps them within standard bounds.
* **How it works:** Uses `fmod` to get the remainder of `angle` divided by `2π`. If the result is negative, adds `2π` to keep it positive.

### [get_ray_direction](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_utils.c#L23-L45)
* **What it is for:** Sets directional boolean flags.
* **Why it is needed:** Tells the DDA steps and checking offsets which direction the ray is traveling.
* **How it works:**
  * Checks if `ray_angle` is between $0$ and $\pi$ to determine if it is facing **down** (otherwise, it faces **up**).
  * Checks if `ray_angle` is less than $\pi/2$ or greater than $3\pi/2$ to determine if it is facing **right** (otherwise, it faces **left**).

### [has_wall_at](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_utils.c#L47-L62)
* **What it is for:** Checks if coordinates land inside a wall tile.
* **Why it is needed:** The primary collision lookup helper used by both raycasting and player movement collision detection.
* **How it works:**
  1. Checks if coordinates are outside map limits. If so, returns `1` (solid barrier).
  2. Converts coordinates to grid tile indices: `map_x = x / TILE_SIZE`, `map_y = y / TILE_SIZE`.
  3. Verifies that the indices are within array boundaries.
  4. Returns `1` if `map[map_y][map_x] == '1'`.

### [get_dis](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_utils.c#L64-L78)
* **What it is for:** Calculates the distance between two points.
* **Why it is needed:** Measures the distance from the player to a wall intersection.
* **How it works:** If `check` is false (meaning no wall was hit), returns `DBL_MAX` (infinity). Otherwise, calculates the Euclidean distance using the Pythagorean theorem:
  $$\text{distance} = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$$

### [get_small_wall_hit](file:///c:/42AD/staff-evaluation/cub3d/src/engine/ray_utils.c#L80-L102)
* **What it is for:** Compares horizontal and vertical hits, picks the closer one, and corrects for the fisheye distortion.
* **Why it is needed:** Resolves the final raycasting outputs for rendering.
* **How it works:**
  * **Horizontal is closer:** If `horzdistance <= vertdistance`:
    * Sets `was_hit_vertical = 0` (horizontal wall face hit).
    * Calculates the corrected perpendicular distance:
      $$\text{distance} = \text{horzdistance} \times \cos(\text{ray\_angle} - \text{player\_angle})$$
    * Saves intersection coordinates scaled back down to tile units.
  * **Vertical is closer:** If `horzdistance > vertdistance`:
    * Sets `was_hit_vertical = 1` (vertical wall face hit).
    * Calculates the corrected perpendicular distance:
      $$\text{distance} = \text{vertdistance} \times \cos(\text{ray\_angle} - \text{player\_angle})$$
    * Saves intersection coordinates scaled back down to tile units.

---

## Next Steps

Now that we have computed the distance to the walls, let's explore **how the engine renders the 3D wall projections**.

👉 Proceed to [05_Rendering_3D_and_Minimap.md](./05_Rendering_3D_and_Minimap.md)
