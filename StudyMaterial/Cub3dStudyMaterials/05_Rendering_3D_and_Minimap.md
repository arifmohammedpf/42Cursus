# cub3D — Rendering Engine (3D Projection & Minimap)

This document details the rendering subsystems that draw the environment: floor/ceiling backgrounds, textured 3D wall projections, and the 2D minimap HUD overlay. These functions are located in `src/rendering/`.

---

## 1. Background Rendering (`src/rendering/bg_render.c`)

The background is rendered first, serving as the canvas on which the 3D walls are painted.

### [render_ceiling_and_floor](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/bg_render.c#L51-L68)
* **What it is for:** Draws the ceiling color on the top half of the screen and the floor color on the bottom half.
* **Why it is needed:** Fills empty pixels where walls are not present.
* **How it works:**
  1. Converts floor and ceiling RGB colors to integers using `create_rgb`.
  2. Casts the framebuffer address pointer to an integer pointer (`int *img_data`).
  3. Divides `line_size` by 4 to get the row width in integers.
  4. Calls `render_ceiling` (writing color values for rows `0` to `349`) and `render_floor` (writing color values for rows `350` to `699`).

---

## 2. Load & Read Textures (`src/rendering/load_texture.c` & `pixel_manip.c`)

Textures are stored as `.xpm` images. We load them at startup and read from their raw address buffers.

### [load_all_textures](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/load_texture.c#L30-L50)
* **What it is for:** Loads the 4 wall textures.
* **Why it is needed:** Prepares image buffers before rendering begins.
* **How it works:** Loops through indices `0` to `3` (North, South, West, East) and calls `load_single_texture` with the parsed path. If any load fails, cleans up loaded resources and aborts.

### [load_single_texture](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/load_texture.c#L15-L28)
* **What it is for:** Loads one texture file.
* **Why it is needed:** Accesses the texture's raw data.
* **How it works:** Calls MLX's `mlx_xpm_file_to_image`, which populates the image pointer, width, and height. Then calls `mlx_get_data_addr` to obtain the raw pixel address.

### [my_mlx_pixel_put](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/pixel_manip.c#L15-L23)
* **What it is for:** Writes a pixel value directly to the framebuffer.
* **Why it is needed:** Faster replacement for `mlx_pixel_put`.
* **How it works:** Checks bounds. If within screen limits, calculates the target memory offset:
  $$\text{offset} = y \times \text{line\_size} + x \times \left(\frac{\text{bits\_per\_pixel}}{8}\right)$$
  Writes the color value directly to that address.

### [get_texture_pixel](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/pixel_manip.c#L25-L35)
* **What it is for:** Reads a pixel value from a texture.
* **Why it is needed:** Samples colors from wall textures.
* **How it works:** Checks bounds. If within bounds, calculates row offset and returns the 32-bit color code from the texture's address array:
  $$\text{color} = \text{data}[y \times (\text{line\_size} / 4) + x]$$

---

## 3. Projection Calculations (`src/rendering/wall_calculate.c`)

### [calculate_wall_height](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_calculate.c#L15-L34)
* **What it is for:** Computes the projected height and screen boundaries of a wall slice.
* **Why it is needed:** Scales the wall based on distance, creating perspective.
* **How it works:**
  1. Clamps distance to a minimum of `1.0` tile to prevent division-by-zero.
  2. Calculates the distance to the projection plane:
     $$\text{dist\_to\_plane} = \frac{\text{SCREENWIDTH} / 2}{\tan(30^\circ)} = \frac{600}{\tan(\pi/6)}$$
  3. Calculates the projected wall height:
     $$\text{wall\_height} = \left(\frac{\text{TILE\_SIZE}}{\text{distance}}\right) \times \text{dist\_to\_plane}$$
  4. Clamps `wall_height` to prevent buffer overflows.
  5. Sets the top and bottom screen limits:
     $$\text{wall\_top} = \frac{\text{SCREENHEIGHT}}{2} - \frac{\text{wall\_height}}{2}$$
     $$\text{wall\_bottom} = \frac{\text{SCREENHEIGHT}}{2} + \frac{\text{wall\_height}}{2}$$
  6. Clamps `wall_top` to `0` and `wall_bottom` to `SCREENHEIGHT - 1`.

### [calculate_texture_coords](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_calculate.c#L36-L63)
* **What it is for:** Finds the horizontal index (`texture_x`) of the texture column to draw.
* **Why it is needed:** Decides which vertical slice of the texture matches the wall hit point.
* **How it works:**
  * **Vertical Wall Hit:** The hit point Y is used to sample the texture. `texture_x = (int)(vertwallhit.y) % texture_width`. If the ray faces left, flips `texture_x` so textures do not appear mirrored. Sets texture index to `3` (East) or `2` (West).
  * **Horizontal Wall Hit:** The hit point X is used to sample the texture. `texture_x = (int)(horzwallhit.x) % texture_width`. If the ray faces up, flips `texture_x`. Sets texture index to `1` (South) or `0` (North).

---

## 4. Wall Rendering Loops (`src/rendering/wall_render.c` & `wall_texture.c`)

### [render_3d_view](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_render.c#L61-L76)
* **What it is for:** Draws the complete 3D scene.
* **Why it is needed:** The primary rendering pipeline called each frame.
* **How it works:** Paints the ceiling and floor background, then loops through all 1200 rays to render wall strips.

### [render_wall_strip](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_render.c#L40-L59)
* **What it is for:** Processes and renders a single vertical column.
* **Why it is needed:** Bridges ray calculation and drawing functions.
* **How it works:** Fetches the ray for the column, determines the texture number, runs `calculate_wall_data`, and calls `render_textured_wall`.

### [render_textured_wall](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_render.c#L15-L38)
* **What it is for:** Loops through screen rows, drawing pixels.
* **Why it is needed:** Steps through texture coordinates to scale the image onto the wall slice.
* **How it works:** Calls `init_texture_params` to set step sizes. Iterates from `wall_top` to `wall_bottom`. Every pixel step, increments `texture_pos` by `texture_step` and calls `render_wall_pixel`.

### [init_texture_params](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_texture.c#L40-L48)
* **What it is for:** Calculates texture scaling factors.
* **Why it is needed:** Maps the texture height to the projected wall height.
* **How it works:** Calculates the vertical texture step size:
  $$\text{texture\_step} = \frac{\text{texture\_height}}{\text{wall\_height}}$$
  Calculates the starting position in texture coordinates:
  $$\text{texture\_pos} = \left(\text{wall\_top} - \frac{\text{SCREENHEIGHT}}{2} + \frac{\text{wall\_height}}{2}\right) \times \text{texture\_step}$$
  If the wall height is larger than the screen height, this offset shifts the starting Y index down, skipping parts of the texture that are clipped off the top of the screen.

### [render_wall_pixel](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/wall_texture.c#L24-L38)
* **What it is for:** Draws a single textured pixel.
* **Why it is needed:** Applies colors from the texture image to the screen framebuffer.
* **How it works:** Finds the integer vertical texture coordinate `texture_y` using modulo `texture_height` (with protection bounds). Calls `get_texture_pixel` using `wall->texture_x` and `texture_y`, and writes the color to the framebuffer.

---

## 5. Minimap Setup & HUD Rendering (`src/rendering/minimap_init.c` & `minimap_draw.c`)

The minimap provides a 2D top-down HUD overview in the top-left corner.

### [init_minimap](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_init.c#L15-L25)
* **What it is for:** Sets default minimap values.
* **Why it is needed:** Configures HUD sizes, offsets, and colors.
* **How it works:** Configures size (200x200 pixels), offsets (10px padding), player dot size (6px), and colors (walls = dark gray, floors = white, player = red, borders = black).

### [set_minimap_scale](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_init.c#L45-L64)
* **What it is for:** Calculates the scale factor (pixels per grid tile).
* **Why it is needed:** Fits the entire map inside the 200px boundary.
* **How it works:** Calculates potential scales for width and height:
  $$\text{scale\_x} = \frac{200}{\text{map\_width}}, \quad \text{scale\_y} = \frac{200}{\text{map\_height}}$$
  Chooses the smaller scale value. Clamps the result between `2` and `20` pixels per tile.

### [draw_minimap_square](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_draw.c#L27-L43)
* **What it is for:** Draws a solid color box on the minimap.
* **Why it is needed:** Draws individual map tiles and the player's avatar.
* **How it works:** Runs a nested loop from `start_y` to `start_y + size` and `start_x` to `start_x + size`, calling `draw_minimap_pixel` for each coordinate.

---

## 6. Minimap Rendering Pipeline (`src/rendering/minimap_render.c`)

### [render_minimap](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_render.c#L97-L102)
* **What it is for:** Orchestrates minimap rendering.
* **Why it is needed:** The primary HUD drawing call executed each frame.
* **How it works:** Calls `draw_minimap_border` to draw the bounding frame, `draw_minimap_tiles` to draw the map layout, and `draw_minimap_player` to overlay the player's position and direction vector.

### [draw_minimap_tiles](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_render.c#L30-L56)
* **What it is for:** Draws the 2D map grid on the HUD.
* **Why it is needed:** Renders wall blocks and open corridors on the overlay.
* **How it works:** Iterates through map grid cells. Calculates screen positions using scale offsets. Retrieves the cell's color (gray for walls, white for floors, black for void) and calls `draw_minimap_square`.

### [draw_minimap_player](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_render.c#L75-L95)
* **What it is for:** Draws the player on the minimap.
* **Why it is needed:** Shows player position and orientation.
* **How it works:**
  1. Calculates screen coordinates: `offset + position * scale`.
  2. If the position is valid, draws a red dot centered on those coordinates.
  3. Calls `draw_player_direction` to draw the orientation line.

### [draw_player_direction](file:///c:/42AD/staff-evaluation/cub3d/src/rendering/minimap_render.c#L58-L73)
* **What it is for:** Draws the player's view vector.
* **Why it is needed:** Shows which direction the player is looking on the HUD.
* **How it works:** Steps 15 pixels forward along the player's viewing angle vector using trigonometry:
  $$x_{\text{line}} = x_{\text{player}} + \cos(\text{viewangle}) \times i$$
  $$y_{\text{line}} = y_{\text{player}} + \sin(\text{viewangle}) \times i$$
  Paints red pixels along this path.

---

## Next Steps

Now that we have covered rendering, let's explore **how player movement and input hooks are handled**.

👉 Proceed to [06_Player_Movement_and_Hooks.md](./06_Player_Movement_and_Hooks.md)
