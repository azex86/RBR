#include "../header/menu.h"
/*
    Affichage du Menu
*/
void menu(GameSettings settings)
{
    printf("Chargement et affichage du menu ...\n");
    SDL_Renderer* renderer = settings.renderer;
    SDL_Window* window = settings.window;
    // Boucle principale
    int quit = 0;
    int iterations = 0;

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

        }
        
        //On efface tout
        // Couleur du fond : noir
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //On affiche le menu


        // Affichage du rendu à l'écran
        SDL_RenderPresent(renderer);        
    }
}
