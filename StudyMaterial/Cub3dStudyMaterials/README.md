# cub3D Codebase Study Materials

This directory contains comprehensive study materials for the **cub3D** codebase. These resources are designed to help you understand the architecture, mathematics, configurations, rendering systems, and physics engine of the project, enabling you to confidently explain it to others.

---

## 📖 Chapter Index

| Chapter | File | Description | Key Concepts Covered |
|:---:|---|---|---|
| **0** | [00_Introduction_and_Architecture.md](./00_Introduction_and_Architecture.md) | Overall project brief and architecture overview. | Raycasting principles, coordinate systems, angles, program phases, and directory maps. |
| **1** | [01_Header_Files_and_Data_Structures.md](./01_Header_Files_and_Data_Structures.md) | Detailed walkthrough of header structures and configurations. | `t_game`, `t_ray`, `t_mlx`, `t_player`, `t_img_data`, and key constants. |
| **2** | [02_Initialization_and_Core_Loop.md](./02_Initialization_and_Core_Loop.md) | Code execution boot pipeline and loop orchestration. | MLX context setups, time delta calculations, key hooks, window callbacks, and staged memory cleanups. |
| **3** | [03_Parsing_and_Map_Validation.md](./03_Parsing_and_Map_Validation.md) | Configuration file reading and structural checks. | Color/texture lines extraction, tab expansion, duplicate prevention, and map boundary enclosure searches. |
| **4** | [04_Raycasting_Math_and_DDA.md](./04_Raycasting_Math_and_DDA.md) | The mathematical heart of the engine. | Digital Differential Analysis (DDA), trigonometric grid steps, distance calculations, and fisheye correction. |
| **5** | [05_Rendering_3D_and_Minimap.md](./05_Rendering_3D_and_Minimap.md) | Buffer writing, scaling, texturing, and HUD rendering. | Ceiling/floor rendering, wall textures calculations, scaling parameters, and 2D minimap HUD drawing. |
| **6** | [06_Player_Movement_and_Hooks.md](./06_Player_Movement_and_Hooks.md) | Movement mechanics and collision boundaries. | Independent axis validation (wall sliding), safety margins, rotation stepping, and input synchronization. |

---

## 🛠️ How to Use These Materials

1. **Read in Order:** If you are new to the codebase, start with **Chapter 0** to get a high-level view before diving into individual files or algorithms.
2. **Follow the Code Links:** Clickable file links are embedded inside the chapters (e.g. `[cub3d.h]`) to let you jump straight to the source files on your system.
3. **Trace the Math:** Use **Chapter 4** to understand the trigonometry behind the ray calculations, which is the most common topic of discussion during project defenses.
