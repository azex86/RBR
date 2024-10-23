#include "../header/play.h"
#include "../header/button.h"

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
		}

		SDL_RenderClear(renderer);
		
		draw_all_buttons();


		SDL_RenderPresent(renderer);
	}
	freeAllButton();
	printf("Fin du jeu\n");
}
