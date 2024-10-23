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
			rotateTank(tank, 1);
			break;
		case SDLK_e:
			rotateTank(tank, -1);
			break;
		default:
			break;
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		SDL_KeyCode key = event->key.keysym.sym;

		if (key == settings.right)
			moveRightStop(tank);
		else if (key == settings.left)
			moveLeftStop(tank);
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		targetPoint(tank, (SDL_FPoint) { (float)event->motion.x, (float)event->motion.y });
	}
}
