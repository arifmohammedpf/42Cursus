# cub3D — Initialization, Core Loop & Memory Management

This document details the functions responsible for booting the game, running the per-frame loop, handling user input hooks, and managing system resources (cleanup and exit). These functions reside in [main.c](file:///c:/42AD/staff-evaluation/cub3d/src/main.c) and the `src/core/` folder.

---

## 1. Entry Point: `main.c`

### [main](file:///c:/42AD/staff-evaluation/cub3d/src/main.c#L15-L36)
* **What it is for:** The entry point of the executable.
* **Why it is needed:** Controls the high-level program flow: parsing setup, starting MLX, entering the loop, and releasing resources on exit.
* **How it works:**
  1. Validates that the command-line argument count is exactly 2 (the program name and the `.cub` map path).
  2. Calls `display_info` to print the controls console banner.
  3. Calls `init_game` to set up all structures and graphics frameworks. If parsing or graphic boot fails, exits with code `1`.
  4. Registers `game_loop` as the frame callback via `mlx_loop_hook`.
  5. Hands control over to the blocking `mlx_loop`. The program hangs here.
  6. If the event loop finishes (clean exit), it destroys the window, calls memory cleanup functions, and exits.

---

## 2. Core Game Orchestration (`src/core/game.c`)

### [init_game](file:///c:/42AD/staff-evaluation/cub3d/src/core/game.c#L46-L68)
* **What it is for:** Initializes the complete game state.
* **Why it is needed:** Centralizes calls to parsing, window creation, texture loading, memory allocations, and hook bindings.
* **How it works:**
  1. Zero-fills the root `t_game` struct using `ft_memset`.
  2. Records the start timeval to compute rendering delays.
  3. Initializes map data pointers and color sentinel variables (setting paths to `NULL` and color fields to `-1`).
  4. Calls `parse_cub_file`. If it fails, calls `mlx_error_and_cleanup` at stage 2 (freeing parsed configuration).
  5. Initialises MLX via `init_mlx` (opens window, allocates image buffer). If it fails, calls `mlx_error_and_cleanup` at stage 2.
  6. Loads wall textures from file. If loading fails, calls cleanup at stage 3 (destroying MLX window and buffers).
  7. Places the player (coordinates and angle) by scanning the parsed grid.
  8. Configures and scales the minimap HUD.
  9. Allocates the 1200-element raycasting arrays.
  10. Registers keyboard and window close hooks.

### [game_loop](file:///c:/42AD/staff-evaluation/cub3d/src/core/game.c#L25-L44)
* **What it is for:** Executed every frame by MiniLibX.
* **Why it is needed:** Drives the gameplay: reading input, calculating physics, raycasting walls, rendering graphics, and updating the monitor.
* **How it works:**
  1. Computes the elapsed time (`delta_time`) between the current frame and the previous frame using `gettimeofday`.
  2. Updates `last_frame_time` to the current timestamp.
  3. Calls `update_player` to handle movement and rotation.
  4. Calls `cast_all_rays` to find the distance to walls for all 1200 screen columns.
  5. Calls `render_3d_view` to draw the floor, ceiling, and textured walls into the framebuffer.
  6. Calls `render_minimap` to overlay the 2D minimap in the top-left corner.
  7. Calls `mlx_put_image_to_window` to push the completed pixel buffer onto the screen.

### [update_player](file:///c:/42AD/staff-evaluation/cub3d/src/core/game.c#L15-L23)
* **What it is for:** Triggers physics calculations.
* **Why it is needed:** Keeps player movement logic modular.
* **How it works:** Reads the state of keyboard flags (direction switches) and applies turning, forwards/backwards movement, and strafe updates.

---

## 3. Game State Initialization (`src/core/_init.c` & `src/core/_init_mlx.c`)

### [init_map_data](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init.c#L25-L35)
* **What it is for:** Clears parsed configuration variables.
* **Why it is needed:** Ensures texture path pointers are initially null, and colors are set to invalid sentinels.
* **How it works:** Sets all `path` variables to `NULL`, resets definitions check-flags to `0`, and calls `init_map_data_colors` to set Floor/Ceiling red, green, and blue components to `-1`.

### [init_map](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init.c#L37-L43)
* **What it is for:** Initializes the map boundary metadata.
* **Why it is needed:** Establishes dimensions before parsing map grids.
* **How it works:** Sets map grid width, height, and grid character double-pointer to `NULL` / `0`.

### [init_player](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init.c#L45-L54)
* **What it is for:** Sets the player's initial variables.
* **Why it is needed:** Defines speeds and sets movement switches to inactive.
* **How it works:** Assigns speed constraints (`PLAYER_MOVE_SPEED` and `PLAYER_ROTATION_SPEED`), clears movement flags, and triggers `find_player_position` to scan the grid.

### [init_mlx](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init_mlx.c#L15-L41)
* **What it is for:** Connects to the graphics driver and creates the window.
* **Why it is needed:** Bootstraps the screen rendering interface.
* **How it works:**
  1. Calls `mlx_init` to create a connection pointer.
  2. Calls `mlx_new_window` to open the visual window.
  3. Mallocs a `t_img_data` struct for the main frame buffer.
  4. Calls `mlx_new_image` to establish a pixel buffer of dimensions 1200 x 700.
  5. Obtains the raw memory pointer to this buffer via `mlx_get_data_addr`.

### [init_raycast](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init_mlx.c#L43-L51)
* **What it is for:** Allocates memory for rays.
* **Why it is needed:** Sets up a dedicated heap space where the DDA system can record hit details.
* **How it works:** Sets the field of view to $60^\circ$ (`M_PI / 3`), configures `num_rays` to match window width, and mallocs an array of 1200 `t_ray` structs.

---

## 4. Player Positioning Utilities (`src/core/_init_utils.c`)

### [find_player_position](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init_utils.c#L27-L50)
* **What it is for:** Scans the 2D grid to locate the player.
* **Why it is needed:** Determines where the player starts and which direction they face.
* **How it works:** Loops through the map array. If it encounters `N`, `S`, `E`, or `W`, it converts the indices `(j, i)` to floating-point tile coordinates `(j + 0.5, i + 0.5)` (centering the player in the tile) and calls `set_player_direction` to set the angle.

### [set_player_direction](file:///c:/42AD/staff-evaluation/cub3d/src/core/_init_utils.c#L15-L25)
* **What it is for:** Maps starting character letters to radian angles.
* **Why it is needed:** Translates compass letters into mathematical vectors.
* **How it works:**
  * `'N'` $\rightarrow$ $270^\circ$ (`3 * M_PI / 2`)
  * `'S'` $\rightarrow$ $90^\circ$ (`M_PI / 2`)
  * `'E'` $\rightarrow$ $0^\circ$ (`0`)
  * `'W'` $\rightarrow$ $180^\circ$ (`M_PI`)

---

## 5. Input Hooks & Callbacks (`src/core/hooks.c`)

### [setup_hooks](file:///c:/42AD/staff-evaluation/cub3d/src/core/hooks.c#L55-L60)
* **What it is for:** Registers callbacks for hardware and window actions.
* **Why it is needed:** Links window system inputs to our C logic.
* **How it works:** Calls MLX bindings:
  * `KEY_PRESS` $\rightarrow$ `key_hook`
  * `KEY_RELEASE` $\rightarrow$ `key_release_hook`
  * `DESTROY_NOTIFY` (clicking the window 'X') $\rightarrow$ `esc_hook`

### [key_hook](file:///c:/42AD/staff-evaluation/cub3d/src/core/hooks.c#L15-L36)
* **What it is for:** Processes key presses.
* **Why it is needed:** Activates movement switches when keys are held.
* **How it works:**
  * If `keycode == KEY_ESC`, prints "game over!!!", cleans up resources, and terminates.
  * If `W`/`S` are pressed, sets `walkdirection` to `1` / `-1`.
  * If `A`/`D` are pressed, sets `movesleft_or_right` to `-1` / `1` (strafing).
  * If `Left`/`Right` arrow keys are pressed, sets `turndirection` to `-1` / `1`.

### [key_release_hook](file:///c:/42AD/staff-evaluation/cub3d/src/core/hooks.c#L38-L47)
* **What it is for:** Processes key releases.
* **Why it is needed:** Stops movement when keys are released.
* **How it works:** Resets movement state flags (`walkdirection`, `movesleft_or_right`, `turndirection`) back to `0` when their respective keys are released.

### [esc_hook](file:///c:/42AD/staff-evaluation/cub3d/src/core/hooks.c#L49-L53)
* **What it is for:** Handles window closure.
* **Why it is needed:** Ensures resources are freed when clicking the 'X' button.
* **How it works:** Calls `cleanup_and_exit` and terminates with exit code `0`.

---

## 6. Exit and Memory Cleanup (`src/core/exit.c` & `src/core/free.c`)

The codebase features a staged exit mechanism. When errors occur during startup, only resources allocated up to that point are cleaned up, avoiding segfaults from freeing unallocated memory pointers.

### Staged Exit Logic: [mlx_error_and_cleanup](file:///c:/42AD/staff-evaluation/cub3d/src/core/exit.c#L15-L28)
* **What it is for:** Safely handles startup failures.
* **Why it is needed:** Prevents memory leaks if initialization fails midway.
* **How it works:** Prints the error message to console and checks the `stage` variable:
  * **`stage >= 4`**: Calls `cleanup_raycast_data` and `cleanup_textures` (destroys MLX images and frees raycasting buffers).
  * **`stage >= 3`**: Destroys the MLX window.
  * **`stage >= 2`**: Frees the parsed configuration using `free_config`.
  * Returns `1` so the calling function can exit.

### [cleanup_and_exit](file:///c:/42AD/staff-evaluation/cub3d/src/core/exit.c#L66-L82)
* **What it is for:** Performs full cleanup on program shutdown.
* **Why it is needed:** Releases all heap space and window hooks back to the operating system.
* **How it works:**
  1. Frees the raycasting buffer.
  2. Loops through the four wall textures, destroying their MLX image handles.
  3. Destroys the main frame buffer image and frees the container struct.
  4. Destroys the window handle.
  5. Frees the MLX library context pointer.
  6. Frees the map configuration (paths and grid array).

### [free_config](file:///c:/42AD/staff-evaluation/cub3d/src/core/free.c#L56-L61)
* **What it is for:** Frees variables parsed from the `.cub` file.
* **Why it is needed:** Releases configuration data.
* **How it works:**
  * Calls `free_texture_paths` to free the strings for North, South, West, and East texture paths.
  * Calls `free_map_array` to loop through the 2D grid rows and free each string, before freeing the outer double-pointer.
  * Cleans the structure memory using `ft_memset` to clear remaining variables.

### [free_split](file:///c:/42AD/staff-evaluation/cub3d/src/core/free.c#L15-L26)
* **What it is for:** Utility to free split string arrays.
* **Why it is needed:** Standard cleanup for string manipulation outputs.
* **How it works:** Loops through a NULL-terminated string array, freeing each string index, then frees the outer double-pointer.

---

## Next Steps

Now that you understand the core setup, let's explore **how the map config is parsed and validated**.

👉 Proceed to [03_Parsing_and_Map_Validation.md](./03_Parsing_and_Map_Validation.md)
