# cub3D — Player Movement & Collision Physics

This document explains the physics engine of cub3D, including player translation, rotation, and sliding wall collision. These functions are located in [src/engine/player_move.c](file:///c:/42AD/staff-evaluation/cub3d/src/engine/player_move.c).

---

## 1. Wall Collision Detection

To prevent the player from walking through walls or clipping into wall edges, the engine checks player coordinates before applying movement updates.

### [is_valid_position](file:///c:/42AD/staff-evaluation/cub3d/src/engine/player_move.c#L15-L27)
* **What it is for:** Checks if a coordinate is walkable.
* **Why it is needed:** Serves as the core collision check.
* **How it works:**
  1. Casts the coordinates to integer indices: `map_x = (int)x`, `map_y = (int)y`.
  2. Verifies that the indices are within map boundaries.
  3. Returns `1` if `map[map_y][map_x] != '1'` (meaning it is empty floor or a start position, not a wall).

### [is_valid_position_with_margin](file:///c:/42AD/staff-evaluation/cub3d/src/engine/player_move.c#L29-L40)
* **What it is for:** Checks collision with a safety padding margin (`WALL_DIST` = `0.4`).
* **Why it is needed:** If we only check the player's exact coordinate point, the player can get infinitely close to walls. Since the player has physical width, this would cause them to clip through wall faces.
* **How it works:** Checks four diagonal offsets around the target coordinate `(x, y)` using the margin:
  - Top-Left: `(x - margin, y - margin)`
  - Top-Right: `(x + margin, y - margin)`
  - Bottom-Left: `(x - margin, y + margin)`
  - Bottom-Right: `(x + margin, y + margin)`
  Returns `1` only if all four points are walkable.

```
       Collision Box Check Around Target Player Coordinates (P)
       
                        y - margin
                            │
            (x-margin, y-margin)  (x+margin, y-margin)
                    *─────────────*
                    │             │
        x - margin ─│      P      │─ x + margin
                    │             │
                    *─────────────*
            (x-margin, y+margin)  (x+margin, y+margin)
                            │
                        y + margin
```

---

## 2. Rotation Physics

### [handle_rotation](file:///c:/42AD/staff-evaluation/cub3d/src/engine/player_move.c#L62-L69)
* **What it is for:** Rotates the player's viewing angle.
* **Why it is needed:** Allows looking around.
* **How it works:**
  1. Calculates the angle rotation step:
     $$\text{step} = \text{PLAYER\_ROTATION\_SPEED} \times \text{delta\_time} \times \text{turndirection}$$
  2. Increments `player->viewangle` by this step.
  3. Calls `normangle` to wrap the angle between $0$ and $2\pi$.

---

## 3. Translation Physics & Wall Sliding

Standard first-person games use **wall sliding**: if you walk forward into a wall at an angle, you slide along it instead of stopping completely.
The engine achieves this by updating and validating X and Y coordinates **independently**.

```
                Independent Axis Collision Check (Sliding)
                
                     Wall (Solid)
                ═════════════════════
                       ▲ 
                       │ (Y check fails: blocked)
                       │ 
                       P ───────► (X check succeeds: moves right)
```

### [handle_forward_movement](file:///c:/42AD/staff-evaluation/cub3d/src/engine/player_move.c#L71-L89)
* **What it is for:** Moves the player forwards or backwards along their viewing angle.
* **Why it is needed:** Basic movement.
* **How it works:**
  1. Computes movement step: `move_step = PLAYER_MOVE_SPEED * delta_time`.
  2. If `walkdirection` is `0`, returns (no movement).
  3. Calculates potential new coordinates using trigonometry:
     $$\text{new\_x} = \text{position.x} + \cos(\text{viewangle}) \times \text{move\_step} \times \text{walkdirection}$$
     $$\text{new\_y} = \text{position.y} + \sin(\text{viewangle}) \times \text{move\_step} \times \text{walkdirection}$$
  4. Checks X-coordinate validity: `is_valid_position_with_margin(game, new_x, position.y)`. If valid, updates `position.x = new_x`.
  5. Checks Y-coordinate validity: `is_valid_position_with_margin(game, position.x, new_y)`. If valid, updates `position.y = new_y`.

### [handle_strafe_movement](file:///c:/42AD/staff-evaluation/cub3d/src/engine/player_move.c#L42-L60)
* **What it is for:** Moves the player sideways (strafing) perpendicular to their viewing angle.
* **Why it is needed:** Allows side-stepping.
* **How it works:**
  1. Sideways movement is perpendicular to the view angle. We rotate our direction vector by $90^\circ$ ($\pi/2$ radians).
  2. Calculates potential new coordinates:
     $$\text{new\_x} = \text{position.x} + \cos\left(\text{viewangle} + \frac{\pi}{2}\right) \times \text{move\_step} \times \text{movesleft\_or\_right}$$
     $$\text{new\_y} = \text{position.y} + \sin\left(\text{viewangle} + \frac{\pi}{2}\right) \times \text{move\_step} \times \text{movesleft\_or\_right}$$
  3. Validates and updates X and Y coordinates independently.

---

## 4. Key Binding and Game Loop Integration

Movement updates are processed every frame:

```
[Key Event] ──► hooks.c ──► Sets player input flags (e.g. walkdirection = 1)
                                │
[Each Frame] ──► game.c ──► Calls update_player()
                                │
                            player_move.c
                                ├─ handle_rotation()
                                ├─ handle_forward_movement() (Independent axis validation)
                                └─ handle_strafe_movement()  (Independent axis validation)
```

By separating keyboard interrupts from physics updates, player movement is extremely smooth and responsive, allowing simultaneous diagonal movement, strafing, and rotation.

---

## Summary of the Study Materials

Congratulations! You have completed the study materials for the **cub3D** project. 

* Proceed to [00_Introduction_and_Architecture.md](./00_Introduction_and_Architecture.md) for a high-level overview.
* Proceed to [01_Header_Files_and_Data_Structures.md](./01_Header_Files_and_Data_Structures.md) to inspect definitions.
* Proceed to [02_Initialization_and_Core_Loop.md](./02_Initialization_and_Core_Loop.md) to trace the game boot.
* Proceed to [03_Parsing_and_Map_Validation.md](./03_Parsing_and_Map_Validation.md) to understand configuration processing.
* Proceed to [04_Raycasting_Math_and_DDA.md](./04_Raycasting_Math_and_DDA.md) to study the math engine.
* Proceed to [05_Rendering_3D_and_Minimap.md](./05_Rendering_3D_and_Minimap.md) to see how visual elements are drawn.
