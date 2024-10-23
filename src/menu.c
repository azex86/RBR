#include "../header/menu.h"
/*
    Affichage du Menu
*/
void menu(GameSettings settings)
{
    printf("Chargement et affichage du menu ...\n");
    SDL_Renderer* renderer = settings.renderer;
    SDL_Window* window = settings.window;
    init_font();
    SDL_SetWindowTitle(window, "Menu");

    // Boucle principale
    int quit = 0;
    int iterations = 0;

	Bouton* settings_bouton = init_bouton(renderer, "Settings", 100, 100, 100, 50, NULL);

    if(0!=SDL_RenderClear(renderer)){
        fprintf(stderr,"Error : %s",SDL_GetError());
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
        
        //On efface tout
        // Couleur du fond : noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //On affiche le menu
        draw_all_buttons();

        // Affichage du rendu à l'écran
        SDL_RenderPresent(renderer);        
    }
}
