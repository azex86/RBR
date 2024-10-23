#pragma once
#ifndef  BUTTON_HEADER
#define BUTTON_HEADER
#include <SDL2/SDL.h>
#include "list.h"
#include "tool.h"
struct Button;
typedef struct Button Button;


Button* initButton(SDL_Renderer* renderer, char* text, int x, int y, int w, int h, void(*pressed)(void));
void draw_Button(Button* Button);
void check_Button(Button* Button, SDL_Event* event);
void free_Button(Button* Button);
void freeAllButton(void);
void check_all_buttons(SDL_Event* event);
void draw_all_buttons(void);

/*
* Récupère tous les boutons actifs
* Et les désactive
*/
list takeAllButtons(void);

/*
* Active tous les boutons de la liste passée en paramètre
* précondition : aucun bouton n'est actif
*/
void pushAllButtons(list buttons);

#endif // ! BUTTON_HEADER
