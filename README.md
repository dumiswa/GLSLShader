# 🎮 OpenGL Checkerboard Shader – Assignment 01 (3D Rendering)

This project is part of a university assignment for the *3D Rendering* course. The goal was to explore modern OpenGL and GLSL by procedurally generating animated quads with shader-based visual effects, controlled via uniforms from C++.

## ✨ Features

- ✅ Two animated quads rendered with modern OpenGL.
- ✅ Procedural **checkerboard** and **radial checkerboard** patterns.
- ✅ **Fake lighting** effect that follows the mouse cursor per-quad.
- ✅ **Pattern animation** via shader (rotation and scaling).
- ✅ Independent **circular motion** for both quads.
- ✅ Speed control via keyboard input (`W`/`S`).
- ✅ All animation and lighting controlled by uniforms.

---

## 📸 Demo 
![2025-05-06 19-40-59 (1)](https://github.com/user-attachments/assets/a8d7398b-6ce5-4d39-a427-441200698f42)

---

## 🗂️ Project Structure
- ✅ main.cpp # Main application logic and OpenGL setup
- ✅ vertexshader.vs # Vertex shader: quad movement and UV mapping
- ✅ fragmentshader.fs # Fragment shader: pattern generation + lighting
- ✅ ShaderUtil.h # Shader loading utility (header)
- ✅ ShaderUtil.cpp # Shader loading utility (implementation)
- ✅ CMakeLists.txt # Build configuration
- ✅ README.md # This documentation


---

## ⚙️ Build Instructions

1. Open the project in **CLion** or any **CMake-compatible** IDE.
2. Make sure **GLEW** and **SFML** are installed (vcpkg is recommended).
3. Build the project. If needed, copy these DLLs into the build folder:
   - `glew32.dll`
   - `sfml-system-2.dll`
   - `sfml-window-2.dll`
   - `sfml-graphics-2.dll`
4. Run the program.

---

## 🎮 Controls

| Key       | Action                              |
|-----------|--------------------------------------|
| `W`       | Increase animation speed             |
| `S`       | Decrease animation speed             |
| `Mouse`   | Move light source                    |
| `ESC`     | Exit the program                     |

---

## 🎨 Shader Uniforms

This project controls more than two parameters through uniforms:

- `u_time` – Time-based animation driver  
- `u_speed` – Controls animation speed (scaling + rotation)  
- `u_mouse` – Mouse position (for lighting)  
- `u_columns`, `u_rows` – Checkerboard density  
- `u_patternType` – 0 for checkerboard, 1 for radial  
- `u_offset` – Quad screen movement  
- `u_quadCenter` – For lighting calculations relative to each quad  

---

## 🧠 Technical Notes

- **Vertex Shader** applies `u_offset` to position the quad and calculates `TexCoord` (0–1).
- **Fragment Shader**:
  - Generates either checkerboard or radial pattern procedurally.
  - Applies scaling/rotation using `u_time` and `u_speed`.
  - Calculates lighting by comparing `u_mouse` to `TexCoord`, adjusted to quad space using `u_quadCenter`.
  - Uses `mix()` to blend light intensity smoothly, even for dark squares.

---



