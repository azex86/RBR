#ifndef TOOL_HEADER
#define TOOL_HEADER
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

typedef unsigned int uint;

struct Gamesettings
{
    float fps;
    SDL_Window* window;
    SDL_Renderer* renderer;
};
typedef struct Gamesettings GameSettings;

extern TTF_Font* global_font;
void init_font(void);


#endif