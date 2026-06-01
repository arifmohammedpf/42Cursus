# cub3D — Header Files & Data Structures

Understanding data structures is the most important prerequisite to understanding the code. In C, data structures form the skeleton of the application. In this document, we explain every major constant, enum, and struct defined in [cub3d.h](file:///c:/42AD/staff-evaluation/cub3d/includes/cub3d.h) and [structures.h](file:///c:/42AD/staff-evaluation/cub3d/includes/structures.h).

---

## 1. Key Constants (in `cub3d.h`)

| Constant | Value | What It Is For | Why & How It Is Used |
|---|---|---|---|
| `SCREENWIDTH` | `1200` | Width of the game window in pixels. | Determines the number of vertical wall strips to render and the number of rays to cast (1 ray per vertical pixel column). |
| `SCREENHEIGHT` | `700` | Height of the game window in pixels. | Determines the vertical screen bounds. Used to compute wall heights, clip wall rendering bounds, and draw floor/ceiling boundaries. |
| `PLAYER_MOVE_SPEED` | `3.0` | Player speed in map tiles per second. | Controls how fast the player moves forwards, backwards, or sideways. Multiplied by `delta_time` to keep movement speed consistent regardless of framerate. |
| `PLAYER_ROTATION_SPEED` | `1.0` | Player rotation speed in radians per second. | Controls how fast the player turns left or right. Multiplied by `delta_time` to ensure smooth turning. |
| `TILE_SIZE` | `1024` | Scale factor for internal raycasting math. | Converts coordinate math from floating-point tiles to high-precision integers (sub-tiles). This avoids floating-point round-off errors during DDA wall intersection checks. |
| `WALL_DIST` | `0.4` | Collision padding margin around the player. | Prevents the player from clipping directly into walls. When checking movement validity, it ensures the player stays at least `0.4` tiles away from any wall face. |

---

## 2. Enums: Keyboard Input Mapping (`t_keys`)

To support cross-platform builds, the key codes are conditionally compiled using preprocessor directives (`#if __APPLE__` / `#elif __linux__`):

```c
typedef enum e_keys
{
    KEY_A = 97,           // Strafe Left
    KEY_S = 115,          // Move Backwards
    KEY_D = 100,          // Strafe Right
    KEY_W = 119,          // Move Forwards
    KEY_ESC = 65307,      // Exit Game
    KEY_LEFT_ARROW = 65361,  // Rotate Left
    KEY_RIGHT_ARROW = 65363  // Rotate Right
} t_keys;
```

* **What it is for:** Maps keyboard inputs to specific action IDs.
* **Why it is needed:** Different operating systems (macOS vs. Linux) issue different key code values for the same physical keys. Conditional compilation maps them correctly.
* **How it works:** When a key event occurs, MLX passes the raw key code to our hook handlers, which compare it against these enum constants.

---

## 3. Core Structures (in `structures.h`)

### `t_cordinates` — A 2D Point
```c
typedef struct s_cordinates
{
    double          x;
    double          y;
}                   t_cordinates;
```
* **What it is for:** Represents an arbitrary 2D location or vector on the map.
* **Why it is needed:** Used to represent positions (like player coordinates or ray-to-wall intersection points).
* **How it works:** Holds floating-point fields `x` and `y`. (Note: spelled `s_cordinates` with one "o" in the code).

---

### `t_ray` — A Single Ray cast
```c
typedef struct s_ray
{
    double          ray_angle;          // Angle in radians (0 to 2π)
    double          wall_hit_x;         // Map X coordinate where wall was hit
    double          wall_hit_y;         // Map Y coordinate where wall was hit
    double          player_angle;       // Player angle at the moment of casting
    double          distance;           // Corrected perpendicular distance
    int             was_hit_vertical;   // 1 if East/West wall, 0 if North/South wall
    int             is_ray_facing_up;   // Movement direction flags (boolean)
    int             is_ray_facing_down;
    int             is_ray_facing_left;
    int             is_ray_facing_right;
    int             wall_content;       // Reserved for future extensions
    t_cordinates    horzwallhit;        // Intersection coordinates on horizontal grid line
    t_cordinates    vertwallhit;        // Intersection coordinates on vertical grid line
    double          distancetowall;     // Raw diagonal distance to wall
    int             wallhitisvert;      // Alias for was_hit_vertical
}                   t_ray;
```
* **What it is for:** Encapsulates the results of casting a single ray into the map.
* **Why it is needed:** The raycaster computes 1200 of these per frame. The rendering engine reads them to draw each vertical slice of wall.
* **How it works:** 
  * The raycaster determines the ray direction and sets the `is_ray_facing_*` flags.
  * It performs the DDA algorithm to find the closest horizontal grid intersection (`horzwallhit`) and vertical grid intersection (`vertwallhit`).
  * It compares the distances, picks the shorter one, sets `was_hit_vertical`, computes the fisheye-corrected `distance`, and stores the final coordinates in `wall_hit_x` and `wall_hit_y`.

---

### `t_ray_cast` — The Ray Array Container
```c
typedef struct s_ray_cast
{
    double          fov_angle;          // Field of view in radians (60° = π/3)
    int             num_rays;           // Total rays = SCREENWIDTH (1200)
    t_ray           *rays;              // Dynamically allocated array of t_ray
}                   t_ray_cast;
```
* **What it is for:** Holds the entire collection of rays cast across the player's field of view.
* **Why it is needed:** Groups all raycasting settings and outputs together in a clean container.
* **How it works:** During game initialization, `rays` is allocated as an array of `num_rays` (1200) elements. Every frame, `cast_all_rays` loops through and populates each ray in this array.

---

### `t_img_data` — An Image Buffer
```c
typedef struct s_img_data
{
    void            *img;               // Opaque pointer to the MLX image object
    char            *addr;              // Raw byte array of pixel data
    int             *int_addr;          // Raw integer array of pixel data (unused alias)
    int             bits_per_pixel;     // Bits per pixel (usually 32)
    int             line_size;          // Number of bytes in a single screen row
    int             endian;             // Color byte ordering
    int             width;              // Width of the image in pixels
    int             height;             // Height of the image in pixels
}                   t_img_data;
```
* **What it is for:** Represents any graphical buffer (both the main screen frame buffer and the loaded wall textures).
* **Why it is needed:** Writing pixels to the screen using MLX's built-in `mlx_pixel_put` is extremely slow because it makes a round-trip system call per pixel. Instead, we write directly into a raw memory block (`addr`) and push the entire image to the window at once.
* **How it works:**
  * `img` is created using `mlx_new_image` (for screen buffer) or `mlx_xpm_file_to_image` (for textures).
  * `addr` is a pointer returned by `mlx_get_data_addr`.
  * To write a color at coordinates `(x, y)`, we calculate the byte index: `y * line_size + x * (bits_per_pixel / 8)` and write the color code (usually 32-bit RGB) directly to that address.

---

### `t_mlx` — MLX System Handles
```c
typedef struct s_mlx
{
    void            *mlx;               // Connection pointer returned by mlx_init()
    void            *mlx_win;           // Window handle returned by mlx_new_window()
    t_img_data      *img;               // The main screen framebuffer image
}                   t_mlx;
```
* **What it is for:** Wraps the graphics library context.
* **Why it is needed:** Houses the connections to the window manager and the active display window.
* **How it works:** Initialized at startup. When rendering a frame, the renderer writes to `img` and then copies `img` onto `mlx_win` using `mlx_put_image_to_window`.

---

### `t_player` — The Player State
```c
typedef struct s_player
{
    t_cordinates    position;           // Float coordinate (x, y) on the grid
    double          movespeed;          // Speed multiplier (tiles per second)
    double          viewangle;          // Viewing angle in radians (0 to 2π)
    double          rotationspeed;      // Turning speed in radians per second
    int             movesleft_or_right; // Strafe input flag (-1 = left, 1 = right, 0 = none)
    int             turndirection;      // Turning input flag (-1 = left, 1 = right, 0 = none)
    int             walkdirection;      // Straight input flag (-1 = back, 1 = forward, 0 = none)
}                   t_player;
```
* **What it is for:** Tracks the player's position, viewing angle, and active movement states.
* **Why it is needed:** Separate tracking of movement input flags allows the physics engine to update player coordinates correctly inside the game loop based on keys currently held down.
* **How it works:**
  * When a movement key is pressed, key hooks set `walkdirection`, `movesleft_or_right`, or `turndirection` to `1` or `-1`. When released, they are reset to `0`.
  * Every frame, the physics engine updates `position.x`, `position.y`, and `viewangle` using these flags scaled by speed and `delta_time`.

---

### `t_rgb` — A Color Representation
```c
typedef struct s_rgb
{
    int             r;                  // Red component (0 to 255)
    int             g;                  // Green component (0 to 255)
    int             b;                  // Blue component (0 to 255)
}                   t_rgb;
```
* **What it is for:** Stores Floor and Ceiling colors before rendering.
* **Why it is needed:** Holds parsed RGB fields separately for range validation.
* **How it works:** Parsed from the config (e.g. `F 220,100,0`). It is initialized with `-1` sentinels so the validator can verify that color fields were defined.

---

### `t_map` & `t_map_data` — The Parsed Configuration File
```c
typedef struct s_map
{
    char            **data;             // Unused map data pointer
    int             width;              // Maximum width of the map grid in tiles
    int             height;             // Height of the map grid (number of rows)
}                   t_map;

typedef struct s_map_data
{
    char            *no_path;           // North texture filepath
    char            *so_path;           // South texture filepath
    char            *we_path;           // West texture filepath
    char            *ea_path;           // East texture filepath
    int             has_c;              // Boolean: Ceiling color defined
    int             has_f;              // Boolean: Floor color defined
    int             has_no;             // Boolean: North texture path defined
    int             has_so;             // Boolean: South texture path defined
    int             has_we;             // Boolean: West texture path defined
    int             has_ea;             // Boolean: East texture path defined
    t_rgb           floor;              // Floor color RGB struct
    t_rgb           roof;               // Ceiling color RGB struct
    char            **map;              // 2D grid array representing the maze
    t_map           map_info;           // Map dimensions (width and height)
    int             map_started;        // Parser state flag (checking if map rows started)
}                   t_map_data;
```
* **What it is for:** Serves as the complete registry for all parameters parsed from the `.cub` file.
* **Why it is needed:** Keeps configuration separate from active runtime subsystems. The renderer and raycaster read texture paths, colors, and map tiles from here.
* **How it works:**
  * Texture paths and colors are stored as strings/structs during parsing.
  * The map grid `map` is dynamically allocated as an array of strings, where `map[y][x]` corresponds to a tile character (`'1'` for wall, `'0'` for floor, `' '` for void, etc.).
  * `map_info` holds the bounding dimensions.

---

### `t_wall_data` — Wall Projection Slice
```c
typedef struct s_wall_data
{
    int             wall_height;        // Height of the projected wall slice in pixels
    int             wall_top;           // Y-pixel coordinate where wall begins
    int             wall_bottom;        // Y-pixel coordinate where wall ends
    double          texture_x;          // X-pixel column to sample from the texture image
    int             texture_num;        // Index of the texture to use (0=N, 1=S, 2=W, 3=E)
}                   t_wall_data;
```
* **What it is for:** Temporary structure containing rendering details for one vertical screen column.
* **Why it is needed:** Bridges raycast outputs and the pixel texturing engine.
* **How it works:**
  * Created inside the wall render pipeline for a specific ray.
  * Calculated using the ray's perpendicular distance, ray angle, and hit flags.
  * Tells the renderer: "draw a wall of height `wall_height` from pixel `wall_top` to `wall_bottom`, sampling column `texture_x` of texture index `texture_num`".

---

### `t_pixel_data` — Pixel Loop Iterator Data
```c
typedef struct s_pixel_data
{
    int             strip_id;           // Screen X coordinate (0 to SCREENWIDTH - 1)
    int             y;                  // Screen Y coordinate (0 to SCREENHEIGHT - 1)
    double          texture_pos;        // Running fractional Y position on the texture image
}                   t_pixel_data;
```
* **What it is for:** Holds coordinates inside the vertical wall slice rendering loops.
* **Why it is needed:** Avoids passing multiple separate counter variables to `render_wall_pixel`.
* **How it works:** Holds the destination screen coordinates (`strip_id`, `y`) and the corresponding vertical texture source pointer (`texture_pos`).

---

### `t_minimap` & `t_minimap_square` — Minimap Configuration
```c
typedef struct s_minimap_square
{
    int             start_x;            // Top-left screen X coordinate in pixels
    int             start_y;            // Top-left screen Y coordinate in pixels
    int             size;               // Box side length in pixels
    int             color;              // Box hex color value
}                   t_minimap_square;

typedef struct s_minimap
{
    int             size;               // Outer bounding dimension (200x200 pixels)
    int             scale;              // Calculated scale factor (pixels per map tile)
    int             offset_x;           // Bounding screen offset X (10 pixels)
    int             offset_y;           // Bounding screen offset Y (10 pixels)
    int             player_size;        // Player avatar size (6 pixels)
    int             wall_color;         // Wall fill color (0x404040 - dark gray)
    int             floor_color;        // Floor fill color (0xFFFFFF - white)
    int             player_color;       // Player dot color (0xFF0000 - red)
    int             border_color;       // Border color (0x000000 - black)
}                   t_minimap;
```
* **What it is for:** Configuration and primitive drawing structures for the minimap HUD.
* **Why it is needed:** Controls HUD layout settings, colors, and dimensions.
* **How it works:**
  * `t_minimap` is filled with static parameters at boot.
  * The scale is dynamically computed during initialization based on map dimensions to fit the map within the 200px limit.
  * `t_minimap_square` is used as a parameter container to draw grid squares.

---

### `t_game` — The Root State
```c
typedef struct s_game
{
    t_mlx           mlx;                // Graphics window and framebuffer structure
    t_player        player;             // Player position, speed, and inputs
    t_map_data      map_data;           // Parsed config details
    t_ray_cast      raycast;            // Active ray array
    t_img_data      textures[4];        // Loaded texture images (N, S, W, E)
    t_minimap       minimap;            // Minimap HUD configuration
    double          delta_time;         // Time taken to render the previous frame
    struct timeval  last_frame_time;    // Timestamp of the last frame render
}                   t_game;
```
* **What it is for:** The root struct containing the complete state of the entire running game.
* **Why it is needed:** Avoids the use of global variables. Instead, `game` is allocated on the stack in `main.c`, and pointers to it (`t_game *game`) are passed to every system.
* **How it works:** Orchestrates all sub-structures and tracks the frame-rate timer using `last_frame_time` and `delta_time`.

---

## Next Steps

Now that you know the structures, let's explore **how the game boots up** and the **main execution loop**.

👉 Proceed to [02_Initialization_and_Core_Loop.md](./02_Initialization_and_Core_Loop.md)
