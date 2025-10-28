# Code Convention

## 📘 Naming Overview

| Code Element | Convention | Example |
|:-------------:|:-----------:|:--------|
| **Interface (API / System / Manager)** | `PascalCase` | `RenderSystem`, `AudioManager`, `EntityServer` |
| **Type (struct / union / enum / typedef)** | `PascalCase` | `Texture`, `ShaderProgram`, `LevelData` |
| **Function** | `PascalCase` *(use clear lifecycle pairs)* | `LoadTexture() / UnloadTexture()`, `CreateEntity() / DeleteEntity()` |
| **Variable (local / member)** | `snake_case` | `vertex_count`, `temp_buffer` |
| **Global Variable** | `g_snake_case` | `g_frame_time` |
| **Static Variable (file scope)** | `s_snake_case` | `s_free_list` |
| **Macro / Config Flag** | `ALL_CAPS` | `ENABLE_LOGGING`, `ARRAY_COUNT(x)` |
| **Constant (const)** | `kPascalCase` | `const f32 kGravity = 9.8f;` |
| **File Name** | `snake_case` | `render_system.c`, `audio_mixer.h` |
| **Include Guard** | `ALL_CAPS_WITH_UNDERSCORE` | `#ifndef AUDIO_MANAGER_H` |

---

## 🔄 Resource Lifecycle Convention

Always define **symmetric pairs** of functions for resources that require allocation and deallocation.

| Lifecycle Purpose | Function Pair | Example |
|:------------------:|:--------------:|:--------|
| **Memory-allocated resource** | `Create*()` / `Delete*()` | `CreateEntity()`, `DeleteEntity()` |
| **External data (file / asset)** | `Load*()` / `Unload*()` | `LoadTexture()`, `UnloadTexture()` |
| **Subsystem / runtime context** | `Init*()` / `Uninit*()` | `InitAudioSystem()`, `UninitAudioSystem()` |
| **Session or handle-based resource** | `Open*()` / `Close*()` | `OpenFileStream()`, `CloseFileStream()` |

> ✅ **Rule of symmetry:**  
> Every `LoadSomething()` must have a matching `UnloadSomething()`.  
> Every `CreateSomething()` must have a matching `DeleteSomething()`.

---

## 🧩 Type Definition Guidelines

| Type | Prefix / Suffix | Example |
|------|------------------|---------|
| `struct` | none | `struct Texture` |
| `typedef struct` | optional `_t` suffix | `typedef struct Texture Texture_t;` |
| `enum` | none | `enum RenderMode { RENDERMODE_2D, RENDERMODE_3D };` |
| `function pointer` | `_Fn` suffix | `typedef void (*UpdateFn)(Entity*);` |

---

## ⚙️ Example Implementation Pattern

```c
// Texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct Texture {
    u32 id;
    i32 width, height;
} Texture;

b32 LoadTexture(Texture *tex, const char *path);
void UnloadTexture(Texture *tex);

#endif // TEXTURE_H
