#include "../header/button.h"
list all_boutons = NULL;

struct Bouton
{
	SDL_Renderer* renderer;
	char* text;
	int x;
	int y;
	int w;
	int h;
	SDL_Color color;
	SDL_Color hover_color;
	SDL_Color current_color;
	void(*pressed)(void);
};


Bouton* init_bouton(SDL_Renderer* renderer, char* text, int x, int y, int w, int h, void(*pressed)(void))
{
	Bouton* bouton = malloc(sizeof(Bouton));
	if (!bouton) {
		fprintf(stderr, "Error during memory allocation : %s", SDL_GetError());
	}

	bouton->renderer = renderer;
	bouton->text = text;
	bouton->x = x;
	bouton->y = y;
	bouton->w = w;
	bouton->h = h;
	bouton->pressed = pressed;
    bouton->color = (SDL_Color){ 255, 255, 255, 255 };
	bouton->hover_color = (SDL_Color){ 255, 0, 0, 255 };
	bouton->current_color = bouton->color;

	if (!all_boutons)
		all_boutons = list_create(Bouton*);
	list_add(all_boutons, bouton, -1);

	return bouton;
}

/*
* Affiche un bouton
* @param Bouton* bouton : le bouton à afficher
* @return void
* @note : Affiche un bouton à l'écran
* l'utilisation de SDL_RendererPresent est nécessaire pour afficher le bouton
*/
void draw_bouton(Bouton* bouton)
{
	SDL_Renderer* renderer = bouton->renderer;
	SDL_Rect rect = { bouton->x, bouton->y, bouton->w, bouton->h };
	//dessiner le bouton
	SDL_SetRenderDrawColor(renderer, bouton->current_color.r, bouton->current_color.g, bouton->current_color.b, bouton->current_color.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
	//écrire le texte du bouton
	SDL_Color color = { 0, 0, 0, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(global_font, bouton->text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect text_rect = { bouton->x + 10, bouton->y + 10, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &text_rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

}

void check_bouton(Bouton* bouton, SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONUP)
	{
		int x = event->button.x;
		int y = event->button.y;
		if (x >= bouton->x && x <= bouton->x + bouton->w && y >= bouton->y && y <= bouton->y + bouton->h)
		{
			printf("Button %s is pressed !\n", bouton->text);
			if (bouton->pressed)
			{
				
				bouton->pressed();
			}
		}
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		//Si la souris passe au dessus du bouton on en change la couleur
		int x = event->motion.x;
		int y = event->motion.y;
		if (x >= bouton->x && x <= bouton->x + bouton->w && y >= bouton->y && y <= bouton->y + bouton->h)
		{
			bouton->current_color = bouton->hover_color;
		}
		else
		{
			bouton->current_color = bouton->color;
		}
	}
}

void free_bouton(Bouton* bouton)
{
	list_remove(all_boutons, bouton);
	free(bouton);
}

void check_all_buttons(SDL_Event* event)
{
	for (uint i = 0; i < list_length(all_boutons); i++)
	{
		Bouton* bouton = list_get(all_boutons, i);
		check_bouton(bouton, event);
	}
}

void draw_all_buttons(void)
{
	for (uint i = 0; i < list_length(all_boutons); i++)
	{
		Bouton* bouton = list_get(all_boutons, i);
		draw_bouton(bouton);
	}
}
