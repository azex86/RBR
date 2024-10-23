
/*
    compilation ligne de commande:
        Linux: 
            sudo apt-get install libsdl2-dev libsdl2-mixer-dev
            gcc -lSDL2 -lSDL2_mixer main.c 
        Windows:
            gcc main.c -o prog -I include -L lib -lmingw32 -lSDL2main -lSDL2

*/

/*
    Dans le main on va se contenter d'initialiser les modules de las SDL2
    Et de gérer les éventuels arguments en ligne de commande :

        --size [x:uint] [y:uint] : define the initial window size
        --fps [float] : define the limit of frame per second
        --screen [uint] : define in which screen the app start

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../header/menu.h"
#include "../header/tool.h"





#ifdef _WIN32
#define main main
#endif // _WIN

int main(int argc, char *argv[]) {

    //Gestion des arguments
    printf("Analyse des %d parametres la ligne de commande ...\n",argc);
    int screen_width_init = 640;
    int screen_height_init = 480;
    float fps = 24;
    int screen_id_init = 0;


    for(int i = 1;i<argc;i++)
    {
        char* arg =argv[i];
        if(!strcmp(arg,"--size")){
            if(argc<i+3){
                fprintf(stderr,"Erreur, --size flag wants two parameters !\n");
                return -1;
            }else{
                screen_width_init = atoi(argv[++i]);
                screen_height_init = atoi(argv[++i]);
            }
        }else if(!strcmp(arg,"--fps")){
            if(argc<i+2){
                fprintf(stderr,"Erreur, --fps flag wants one parameter !\n");
                return -1;
            }else{
                fps = atof(argv[++i]);
            }
        }else if(!strcmp(arg,"--screen")){
            if(argc<i+2){
                fprintf(stderr,"Erreur, --screen flag wants one parameter !\n");
                return -1;
            }else{
                screen_id_init = atoi(argv[++i]);
            }
        }
    }

    GameSettings settings;
    settings.fps = fps;

    settings.window = NULL;
    settings.renderer = NULL;

    // Initialisation de la SDL
    printf("Initialisation de la SDL ....\n");

    if (SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO) < 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    //Initialisation de la musique    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer : %s\n", Mix_GetError());
        return 1;
    }

	if (TTF_Init() == -1) {
		printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
		return 1;
	}

    // Création de la fenêtre
    settings.window = SDL_CreateWindow("RBR", SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen_id_init), SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen_id_init), screen_width_init, screen_height_init, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if (settings.window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return 1;
    }

    // Création du renderer
    settings.renderer = SDL_CreateRenderer(settings.window, -1, SDL_RENDERER_ACCELERATED);
    if (settings.renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return 1;
    }

    menu(settings);


    // Libération des ressources
    printf("Nettoyage des ressources avant cloture du programme ...\n");
    SDL_DestroyRenderer(settings.renderer);
    SDL_DestroyWindow(settings.window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}