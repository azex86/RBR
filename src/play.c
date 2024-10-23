#include "../header/play.h"
#include "../header/button.h"

void drawBackground(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 113, 230, 249, 255);//cyan
	SDL_RenderClear(renderer);
}



void play(GameSettings settings)
{

	printf("Chargement et affichage du jeu ...\n");
	SDL_Renderer* renderer = settings.renderer;
	SDL_Window* window = settings.window;
	init_font();
	SDL_SetWindowTitle(window, "Jeu");

	// Boucle principale
	int quit = 0;
	int iterations = 0;

	if (0 != SDL_RenderClear(renderer)) {
		fprintf(stderr, "Error : %s", SDL_GetError());
	}

	Tank* mytank = initTank("res/tank.bmp", "res/canon.bmp", renderer);
	KeyboardSettings mysettings = {SDLK_RIGHT,SDLK_LEFT,SDLK_SPACE};
	//Gestion des événements
	SDL_Event event;
	while (!quit) {
		iterations++;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
			else if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;
				default:
					break;
				}
			}
			check_all_buttons(&event);
			keyboardPlayerCheck(mytank, mysettings, &event);
		}

		updateTank(mytank);
		drawBackground(renderer);
		
		draw_all_buttons();
		drawTank(mytank, renderer);

		SDL_RenderPresent(renderer);
	}
	freeAllButton();
	printf("Fin du jeu\n");
}
