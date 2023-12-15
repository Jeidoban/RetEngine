#include "SDL2/SDL.h"

extern Uint64 deltaTime;
extern bool running;
extern int screenWidth;
extern int screenHeight;
extern unsigned int shaders[2];
#define SHADER_DEFAULT 0
#define SHADER_LIGHTING 1