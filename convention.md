# Code Convention

### Naming

__Code Element__ | __Convention__ | __Example__
:---| :---: | :---
**Macros** | `ALL_CAPS` | `#define MIN(a,b) (((a)<(b))?(a):(b))`
**Defines / Config Flags** | `ALL_CAPS` | `#define PLATFORM_DESKTOP`
**Struct** | `PascalCase` | `struct Texture2D`
**Struct Members** | `camelCase` | `texture.texId`
**Enum** | `PascalCase` | `TextureFormat`
**Enum Members** | `ALL_CAPS` | `PIXELFORMAT_UNCOMPRESSED_R8G8B8`
**Functions** | `PascalCase` | `InitWindow()`
**Constants** | `camelCase` | `const int maxValue = 8;`
**Variables** | `camelCase` | `screenWidth`
**Local Variables** | `camelCase` | `playerPosition`
**Global Variables** | `camelCase` | `fullScreen`
**Pointers** | `Type *pointer`  | `Texture2D *array;`
**Float Values** | Always include `.0f` | `float value = 10.0f;`
**File Names** | `snake_case` | `render_system.c`, `audio_mixer.h`
**Header Guards** | `ALL_CAPS_WITH_UNDERSCORE` | `#ifndef TEXTURE_H`
**Boolean Prefixes** | Optional `Is`, `Has`, `Can` | `IsVisible`, `HasShadow`, `CanMove`
**Resource Lifecycle Functions** | Symmetric Pair | `Create/Delete`, `Load/Unload`, `Init/Uninit`, `Open/Close`
**Function Pointer Typedefs** | PascalCase + `Fn` suffix | `typedef void (*UpdateFn)(Entity *E);`

---

### 📏 Notes

1. **No snake_case** (except for external API compatibility).  
2. **PascalCase** is used for *types*, *interfaces*, and *public functions*.  
3. **camelCase** is used for *variables* and *members*.  
4. **Macro names**,**Preprocesor**, and **enum members** are always **ALL_CAPS**.  
5. **Float literals** always use `f` suffix (`10.0f`) for clarity and type safety.  
6. **Symmetry rule**: any alloc/init/load/open function must have its cleanup pair.
7. **Indentation** alway use 2 space instead of tabs

---

### 💡 Example

```c
#define ENABLE_LOGGING 1
#define PLATFORM_DESKTOP

typedef struct Texture2D {
    u32 id;
    i32 width;
    i32 height;
} Texture2D;

typedef enum TextureFormat {
    PIXELFORMAT_UNCOMPRESSED_R8G8B8,
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
} TextureFormat;

i32 LoadTexture(Texture2D *tex, const char *path);
void UnloadTexture(Texture2D *Tex);

static i32 screenWidth = 1280;
static i32 screenHeight = 720;
static f32 frameTime = 0.0f;

void InitWindow(I32 width, I32 height, const Char *title);
void CloseWindow(void);
//alway use curly bracket for : if,else if,else,for,while
if(...){
    ...
}else if(...){
   ...
}else{
   ...
}

for(...){
    ...
}
while(...){
    ...
}

```
