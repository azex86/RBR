#ifndef TOOL_HEADER
#define TOOL_HEADER
#include <SDL2/SDL.h>
struct Gamesettings
{
    float fps;
    SDL_Window* window;
    SDL_Renderer* renderer;
};
typedef struct Gamesettings GameSettings;

#endif