#include "../header/keyboard_player.h"

void keyboardPlayerCheck(Tank* tank, KeyboardSettings settings, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		SDL_KeyCode key = event->key.keysym.sym;
		
		if (key == settings.right)
			moveRight(tank);
		else if (key == settings.left)
			moveLeft(tank);
		else if (key == settings.shoot)
			shoot(tank);

		//debug
		switch (key)
		{
		case SDLK_a:
			rotateTank(tank, 0.1);
			break;
		case SDLK_e:
			rotateTank(tank, -0.1);
			break;
		default:
			break;
		}
	}
}
