#pragma once
#ifndef KEYBOARD_PLAYER_HEADER
#define KEYBOARD_PLAYER_HEADER
#include "tool.h"
#include "tank.h"
struct KeyboardSettings
{
	SDL_KeyCode right;
	SDL_KeyCode left;
	SDL_KeyCode shoot;
};

typedef struct KeyboardSettings KeyboardSettings;

void keyboardPlayerCheck(Tank* tank, KeyboardSettings settings,SDL_Event* event);

#endif // !KEYBOARD_PLAYER_HEADER
