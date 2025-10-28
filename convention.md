# Code Convention

__Code Element__ | __Convention__ | __Example__
:---| :---: | :---
**Macros** | `ALL_CAPS` | `#define MIN(a,b) (((a)<(b))?(a):(b))`
**Defines / Config Flags** | `ALL_CAPS` | `#define PLATFORM_DESKTOP`
**Constants** | `camelCase` | `const int maxValue = 8;`
**Struct** | `PascalCase` | `struct Texture2D`
**Struct Members** | `camelCase` | `texture.texId`
**Enum** | `PascalCase` | `TextureFormat`
**Enum Members** | `ALL_CAPS` | `PIXELFORMAT_UNCOMPRESSED_R8G8B8`
**Functions** | `PascalCase` | `InitWindow()`
**Variables** | `camelCase` | `screenWidth`
**Local Variables** | `camelCase` | `playerPosition`
**Global Variables** | `camelCase` | `fullScreen`
**Pointers** | `MyType *pointer`  | `Texture2D *array;`
**Float Values** | Always include `.0f` | `float value = 10.0f;`
**File Names** | `PascalCase` | `RenderSystem.c`, `Audio_Mixer.h`
**Header Guards** | `ALL_CAPS_WITH_UNDERSCORE` | `#ifndef TEXTURE_H`
**Boolean Prefixes** | Optional `Is`, `Has`, `Can` | `IsVisible`, `HasShadow`, `CanMove`
**Resource Lifecycle Functions** | Symmetric Pair | `Create/Delete`, `Load/Unload`, `Init/Uninit`, `Open/Close`
**Function Pointer Typedefs** | PascalCase + `Fn` suffix | `typedef void (*UpdateFn)(Entity *E);`

---

### 📏 Notes

1. **No snake_case** (except for external API compatibility).  
2. **PascalCase** is used for *types*, *interfaces*, and *public functions*.  
3. **camelCase** is used for *variables* and *members*.  
4. **Macro names** and **enum constants** are always **ALL_CAPS**.  
5. **Float literals** always use `f` suffix (`10.0f`) for clarity and type safety.  
6. **Pointers** always place `*` next to the variable, not the type (`Type *ptr`, not `Type* ptr`).  
7. **Symmetry rule**: any alloc/init/load/open function must have its cleanup pair.
8. **Indentation** alway use 2 space instead of tabs

---

### 💡 Example

```c
#define ENABLE_LOGGING 1
#define PLATFORM_DESKTOP

typedef struct Texture2D {
    U32 Id;
    I32 Width;
    I32 Height;
} Texture2D;

typedef enum TextureFormat {
    PIXELFORMAT_UNCOMPRESSED_R8G8B8,
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
} TextureFormat;

B32 LoadTexture(Texture2D *Tex, const char *Path);
Void UnloadTexture(Texture2D *Tex);

static I32 screenWidth = 1280;
static I32 screenHeight = 720;
static F32 frameTime = 0.0f;

Void InitWindow(I32 Width, I32 Height, const Char *Title);
Void CloseWindow(Void);
