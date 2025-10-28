# Code Convention

# 🧭 C Code Convention – PascalCase Only

## 📘 Naming Overview

| Code Element | Convention | Example |
|:-------------:|:-----------:|:--------|
| **Interface (API / System / Manager)** | `PascalCase` | `RenderSystem`, `AudioManager`, `EntityServer` |
| **Type (struct / union / enum / typedef)** | `PascalCase` | `Texture`, `ShaderProgram`, `LevelData` |
| **Function** | `PascalCase` | `LoadTexture()`, `UpdateCamera()`, `CreateEntity()` |
| **Variable (local / global / static)** | `PascalCase` | `FrameCount`, `TempBuffer`, `EntityList` |
| **Constant (const)** | `PascalCase` or `kPascalCase` | `Gravity`, `kEpsilon` |
| **Macro / Config Flag** | `ALL_CAPS` | `ENABLE_LOGGING`, `ARRAY_COUNT(x)` |
| **Enum Name** | `PascalCase` | `RenderMode`, `AppState` |
| **Enum Member** | `ALL_CAPS` | `RENDER_MODE_2D`, `APP_STATE_RUNNING` |
| **File Name** | `PascalCase` (optional `_` between words) | `RenderSystem.c`, `AudioMixer.h` |
| **Include Guard** | `ALL_CAPS_WITH_UNDERSCORE` | `#ifndef AUDIO_MANAGER_H` |

---

## 🔄 Resource Lifecycle Convention

Each resource that performs allocation or initialization **must have a clear symmetric pair**.

| Purpose | Function Pair | Example |
|:--------:|:---------------:|:--------|
| **Heap / GPU Allocation** | `Create*()` / `Delete*()` | `CreateEntity()`, `DeleteEntity()` |
| **External Data (File / Asset)** | `Load*()` / `Unload*()` | `LoadTexture()`, `UnloadTexture()` |
| **Subsystem / Context Initialization** | `Init*()` / `Uninit*()` | `InitAudioSystem()`, `UninitAudioSystem()` |
| **Session / Handle Resource** | `Open*()` / `Close*()` | `OpenFileStream()`, `CloseFileStream()` |

> ✅ **Symmetry Rule:**  
> Every `Create` must have `Delete`.  
> Every `Load` must have `Unload`.  
> Every `Init` must have `Uninit`.  
> Every `Open` must have `Close`.

---

## 🧩 Type Definition Guidelines

| Type | Prefix / Suffix | Example |
|------|------------------|---------|
| `struct` | none | `struct Texture` |
| `typedef struct` | optional `_t` | `typedef struct Texture Texture_t;` |
| `enum` | none | `enum RenderMode { RENDER_MODE_2D, RENDER_MODE_3D };` |
| `function pointer` | `_Fn` suffix | `typedef void (*UpdateFn)(Entity*);` |

---

## ⚙️ Example Implementation Pattern

```c
// Texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct Texture {
    U32 Id;
    I32 Width;
    I32 Height;
} Texture;

B32 LoadTexture(Texture *Tex, const char *Path);
Void UnloadTexture(Texture *Tex);

#endif // TEXTURE_H
