# Code Convention

| Code Element | Convention | Example |
|:-------------:|:-----------:|:--------|
| **Macro** | `ALL_CAPS` | `LOG_INFO(fmt, ...)` |
| **Constant / Enum Value** | `ALL_CAPS` | `STATE_RUNNING`, `MAX_ENTITY_COUNT` |
| **Struct / Union / Enum Type** | `PascalCase` | `BatchBuffer`, `RenderCommand`, `EntityState` |
| **Typedef Alias** | `PascalCase` + `_t` (opsional) | `Vector3_t`, `ShaderHandle` |
| **Function** | `snake_case` | `load_texture()`, `update_camera()` |
| **Global Variable** | `g_snake_case` | `g_frame_count`, `g_window` |
| **Static / File-scope Variable** | `s_snake_case` | `s_temp_buffer` |
| **Local Variable** | `snake_case` | `vertex_count`, `player_pos` |
| **Pointer Variable** | `p_snake_case` atau suffix `_ptr` | `p_entity`, `mesh_ptr` |
| **Enum Name** | `PascalCase` | `RenderMode`, `AppState` |
| **Enum Member** | `ALL_CAPS` | `RENDER_MODE_2D`, `APP_STATE_RUNNING` |
| **Function Parameter** | `snake_case` | `void draw_mesh(Mesh *mesh, ColorRGB color)` |
| **File Name** | `snake_case` | `render_system.c`, `math_linear.c` |
| **Header Include Guard** | `ALL_CAPS_WITH_UNDERSCORE` | `#ifndef RENDER_SYSTEM_H` |
| **Global Constant (const)** | `k
