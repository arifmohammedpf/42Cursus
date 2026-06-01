# cub3D — Parsing & Map Validation

This document explains how the engine parses the `.cub` configuration file and validates that the map structure is enclosed, clean, and safe to execute. These functions are located in `src/parsing/` and its subfolder `validation/`.

---

## 1. High-Level Parsing Orchestration (`src/parsing/parse_cub.c`)

### [parse_cub_file](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_cub.c#L36-L59)
* **What it is for:** The entry point for the parsing pipeline.
* **Why it is needed:** Converts the text map file into valid structures, aborting immediately on syntax or formatting errors.
* **How it works:**
  1. Calls `validate_n_open` to verify the extension and open the file descriptor.
  2. Reads the file line-by-line using `get_next_line`.
  3. Sends each line to `parse_line`. If `parse_line` returns `0` (failure), frees the current line, calls GNL buffer cleanup, closes the file, and returns `0` (abort).
  4. Once all lines are processed, closes the file descriptor and returns the result of `validate_map_data`.

### [validate_n_open](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_cub.c#L15-L34)
* **What it is for:** Validates the file extension and opens the file.
* **Why it is needed:** Ensures that the game only runs `.cub` config files and handles file access errors gracefully.
* **How it works:** Reads the length of the string, verifies that the final four characters are `.cub`, and runs standard system `open(..., O_RDONLY)`. If either check fails, prints an error message and returns `-1`.

---

## 2. Line Routing & Parsing (`src/parsing/identifier_lines.c`)

### [parse_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/identifier_lines.c#L84-L94)
* **What it is for:** Trims and routes each raw file line.
* **Why it is needed:** Standardizes whitespace handling and directs lines to their appropriate parsing sub-systems.
* **How it works:**
  1. Trims leading/trailing whitespace (spaces, tabs, newlines) using `ft_strtrim`.
  2. If the trimmed line is empty, it runs `handle_empty_line`.
  3. Otherwise, it calls `process_non_empty_line`.

### [handle_empty_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/identifier_lines.c#L15-L24)
* **What it is for:** Checks if an empty line is valid.
* **Why it is needed:** According to 42 subject rules, empty lines are allowed before the map but not within the map layout.
* **How it works:** Frees the trimmed line string. Checks the state flag `data->map_started`. If the map has already started, prints an error and returns `0` (fail). Otherwise, returns `1` (success).

### [process_non_empty_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/identifier_lines.c#L37-L57)
* **What it is for:** Routes non-empty lines to either the map grid builder or the header element parsers.
* **Why it is needed:** Correctly separates textures/colors parsing from map grid layout construction.
* **How it works:**
  1. If `map_started` is active, it directly forwards the line to `handle_map_line`.
  2. Otherwise, it checks if the line matches the syntax of a map grid line using `is_map_line`. If so, sets `map_started = 1` and runs `handle_map_line`.
  3. If not a map line, it routes to `parse_identifier_line` to search for textures or color paths. If it doesn't match those either, returns `0` (syntax error).

### [parse_identifier_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/identifier_lines.c#L26-L35)
* **What it is for:** Forwards lines to texture or color parsers.
* **Why it is needed:** Acts as a helper router.
* **How it works:** Checks if `parse_texture_line` succeeds; if not, checks if `parse_color_line` succeeds. If both fail, prints an invalid format error and returns `0`.

---

## 3. Extracting Config Data (`src/parsing/parse_data.c` & `parse_color.c`)

### [parse_texture_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_data.c#L22-L49)
* **What it is for:** Identifies and registers texture file paths.
* **Why it is needed:** Extracts XPM paths for North (`NO`), South (`SO`), West (`WE`), and East (`EA`) walls.
* **How it works:**
  1. Checks for duplicates using `check_texture_duplicates`.
  2. Uses `ft_strncmp` to look for prefixes (e.g. `"NO "`, `"SO "`).
  3. If matched, calls `assign_texture_path` and sets the boolean definition flag to `1`.

### [assign_texture_path](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_data.c#L15-L20)
* **What it is for:** Allocates and saves trimmed paths.
* **Why it is needed:** Cleans path declarations of extra spacing.
* **How it works:** Frees existing content at the target double-pointer, runs `ft_strtrim(trimmed + offset, " \t")` to isolate the path, and stores the pointer.

### [parse_color_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_data.c#L51-L78)
* **What it is for:** Extracts Floor and Ceiling colors.
* **Why it is needed:** Populates Floor (`F`) and Ceiling (`C`) RGB parameters.
* **How it works:** Checks if colors have already been defined. If not, forwards the comma-separated string to `parse_color` and registers definition flags.

### [parse_color](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_color.c#L103-L125)
* **What it is for:** Parses and validates `"R,G,B"` strings.
* **Why it is needed:** Converts string inputs into numeric RGB values.
* **How it works:**
  1. Checks formatting (must have exactly two commas).
  2. Splits the string by commas using `ft_split`.
  3. Verifies that the split yields exactly three elements.
  4. Calls `parse_and_validate_rgb` to convert them into integers.

### [parse_rgb_component](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_color.c#L15-L41)
* **What it is for:** Validates and converts an individual color channel.
* **Why it is needed:** Ensures that each channel string contains only digits.
* **How it works:** Trims spaces, verifies digit integrity using `is_valid_number`, converts to integer using `ft_atoi`, and registers it to the corresponding channel (`r`, `g`, or `b`).

---

## 4. Grid parsing and processing (`src/parsing/parse_map_line.c` & `expand_char.c`)

### [is_map_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_map_line.c#L32-L49)
* **What it is for:** Determines if a line is a map row.
* **Why it is needed:** Used to detect where the header ends and the map begins.
* **How it works:** Iterates through characters. If it finds illegal characters (anything other than `1`, `0`, `N`, `S`, `E`, `W`, space, tab, or newlines), returns `0`. Returns `1` if it finds at least one valid map character (enforcing that it's not just a blank line).

### [handle_map_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_map_line.c#L51-L72)
* **What it is for:** Adds a new line to the map data array.
* **Why it is needed:** Consolidates row checks before adding rows to the game state.
* **How it works:**
  1. Checks for empty lines within the map grid.
  2. Runs `validate_single_map_line` to verify character legality.
  3. Calls `add_map_line` to append the row.

### [add_map_line](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/parse_map_line.c#L100-L126)
* **What it is for:** Appends a map row to the game's grid array.
* **Why it is needed:** Dynamically grows the map buffer as lines are read.
* **How it works:**
  1. Trims ending newlines.
  2. Calls `expand_tabs_to_spaces` to standardize grid spacing.
  3. Reallocates the string array using `reallocate_map`.
  4. Stores the new row pointer at `map[height]`.
  5. Null-terminates the array at `map[height + 1]`.
  6. Increments the map height and updates `map_info.width` to track the longest row.

### [expand_tabs_to_spaces](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/expand_char.c#L74-L87)
* **What it is for:** Replaces tab characters (`\t`) with spaces.
* **Why it is needed:** Standardizes index lookup calculations. A tab would otherwise count as a single array character but render as multiple spaces, throwing off coordinate calculations.
* **How it works:** Counts tabs in the string, allocates a new buffer of length `strlen(line) + (tab_count * 3) + 1`, and copies characters one-by-one, replacing every tab with four spaces.

---

## 5. Map Validation Sub-System (`src/parsing/validation/`)

Once parsing is complete, the engine runs strict structural validations.

```
validate_map_data()
  │
  ├─ Check all 4 textures defined
  ├─ Check both colors defined
  ├─ Check map height > 0
  │
  └─ validate_map()
       ├─ validate_map_chars()     → counts players, checks characters
       ├─ validate_map_structure() → checks player_count == 1, checks enclosure
       │    └─ check_map_enclosure()
       │         └─ validate_walkable_position() for each floor/player tile
       │              ├─ check_border_positions()
       │              └─ check_walkable_enclosure()
       │                   └─ check_adjacent_boundary() for 4 neighbors
       ├─ validate_texture_files() → tries to open() all textures
       └─ validate_rgb_value()     → checks color ranges (0-255)
```

### [validate_map_data](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/config_validate.c#L15-L39)
* **What it is for:** High-level validation orchestrator.
* **Why it is needed:** Verifies that all configuration components are fully defined.
* **How it works:** Asserts that all four texture path variables are not `NULL`, ceiling and floor colors were successfully set (checking against `-1` sentinels), and height is non-zero. If so, calls `validate_map`.

### [validate_map](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/config_validate.c#L46-L69)
* **What it is for:** Validates the map grid, textures, and color values.
* **Why it is needed:** Prevents execution if map paths or parameters are invalid.
* **How it works:** Checks character legality, checks enclosure, verifies that texture files are openable, and asserts that floor RGB colors are within bounds.

### [validate_map_structure](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/map_validate.c#L15-L29)
* **What it is for:** Enforces single-player start and enclosure constraints.
* **Why it is needed:** Guarantees that there is exactly one player position and that the map has no open boundaries.
* **How it works:** Calls `validate_map_chars` to verify player count (must equal `1`), and returns the output of `check_map_enclosure`.

---

## 6. Boundary Enclosure Checks (`src/parsing/validation/boundary_utils.c` & `boundary_validate.c`)

The enclosure check verifies that all walkable positions (`0`, `N`, `S`, `E`, `W`) are completely sealed by walls (`1`).

### [check_map_enclosure](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/boundary_utils.c#L59-L82)
* **What it is for:** Loops through all walkable tiles.
* **Why it is needed:** Ensures that the player cannot fall out of bounds or walk into the void.
* **How it works:** Iterates through every tile in the map grid. If a tile is a walkable character (`'0'`, `'N'`, `'S'`, `'E'`, or `'W'`), it runs `validate_walkable_position` on it.

### [validate_walkable_position](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/boundary_utils.c#L50-L57)
* **What it is for:** Validates a walkable tile.
* **Why it is needed:** Aggregates border checks and neighbor checks.
* **How it works:**
  1. Calls `check_border_positions` to verify that the tile is not on the map borders.
  2. Calls `check_walkable_enclosure` to verify adjacent neighbors.

### [check_border_positions](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/boundary_validate.c#L65-L80)
* **What it is for:** Asserts that walkable tiles do not touch map boundaries.
* **Why it is needed:** Walkable tiles at the borders (top row, bottom row, left column, right column) are open to the outside, which is invalid.
* **How it works:**
  * Checks if row index is `0` or `height - 1`. If so, fails.
  * Checks if column index is `0` or the next character is the null terminator (`\0`). If so, fails.

### [check_walkable_enclosure](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/boundary_utils.c#L27-L48)
* **What it is for:** Iterates through the four adjacent neighbors.
* **Why it is needed:** Checks if the neighbors are valid tiles or open space.
* **How it works:** Uses coordinate offsets (`dx = [0, 0, -1, 1]`, `dy = [-1, 1, 0, 0]`) to get neighbor indices in the four cardinal directions (Up, Down, Left, Right). Calls `check_adjacent_boundary` on each.

### [check_adjacent_boundary](file:///c:/42AD/staff-evaluation/cub3d/src/parsing/validation/boundary_validate.c#L57-L63)
* **What it is for:** Evaluates neighbor tile validity.
* **Why it is needed:** Ensures that neighbors are within map bounds and are not spaces, tabs, or invalid characters.
* **How it works:** Calls `check_boundary_limits` to assert that the neighbor coordinates are inside the grid dimensions. Then calls `validate_adjacent_character` to verify that the target character is not a space or tab.

---

## Next Steps

Now that we have parsed the config and verified the map, let's explore the **raycasting math** that makes 3D rendering possible.

👉 Proceed to [04_Raycasting_Math_and_DDA.md](./04_Raycasting_Math_and_DDA.md)
