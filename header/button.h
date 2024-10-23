#pragma once
#ifndef  BUTTON_HEADER
#define BUTTON_HEADER
#include <SDL2/SDL.h>
#include "list.h"
#include "tool.h"
struct Bouton;
typedef struct Bouton Bouton;

extern list all_boutons;


Bouton* init_bouton(SDL_Renderer* renderer, char* text, int x, int y, int w, int h, void(*pressed)(void));
void draw_bouton(Bouton* bouton);
void check_bouton(Bouton* bouton, SDL_Event* event);
void free_bouton(Bouton* bouton);

void check_all_buttons(SDL_Event* event);
void draw_all_buttons(void);
#endif // ! BUTTON_HEADER
