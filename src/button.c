#include "../header/button.h"
list all_buttons = NULL;

struct Button
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


Button* initButton(SDL_Renderer* renderer, char* text, int x, int y, int w, int h, void(*pressed)(void))
{
	Button* button = malloc(sizeof(Button));
	if (!button) {
		fprintf(stderr, "Error during memory allocation : %s", SDL_GetError());
	}

	button->renderer = renderer;
	button->text = text;
	button->x = x;
	button->y = y;
	button->w = w;
	button->h = h;
	button->pressed = pressed;
    button->color = (SDL_Color){ 255, 255, 255, 255 };
	button->hover_color = (SDL_Color){ 255, 0, 0, 255 };
	button->current_color = button->color;

	if (!all_buttons)
		all_buttons = list_create(Button*);
	list_add(all_buttons, button, -1);

	return button;
}

/*
* Affiche un Button
* @param Button* Button : le Button à afficher
* @return void
* @note : Affiche un Button à l'écran
* l'utilisation de SDL_RendererPresent est nécessaire pour afficher le Button
*/
void draw_Button(Button* Button)
{
	SDL_Renderer* renderer = Button->renderer;
	SDL_Rect rect = { Button->x, Button->y, Button->w, Button->h };
	//dessiner le Button
	SDL_SetRenderDrawColor(renderer, Button->current_color.r, Button->current_color.g, Button->current_color.b, Button->current_color.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
	//écrire le texte du Button
	SDL_Color color = { 0, 0, 0, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(global_font, Button->text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect text_rect = { Button->x + 10, Button->y + 10, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, NULL, &text_rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

}

void check_Button(Button* Button, SDL_Event* event)
{
	if (event->type == SDL_MOUSEBUTTONUP)
	{
		int x = event->button.x;
		int y = event->button.y;
		if (x >= Button->x && x <= Button->x + Button->w && y >= Button->y && y <= Button->y + Button->h)
		{
			printf("Button %s is pressed !\n", Button->text);
			if (Button->pressed)
			{
				
				Button->pressed();
			}
		}
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		//Si la souris passe au dessus du Button on en change la couleur
		int x = event->motion.x;
		int y = event->motion.y;
		if (x >= Button->x && x <= Button->x + Button->w && y >= Button->y && y <= Button->y + Button->h)
		{
			Button->current_color = Button->hover_color;
		}
		else
		{
			Button->current_color = Button->color;
		}
	}
}

void free_Button(Button* Button)
{
	list_remove(all_buttons, Button);
	free(Button);
}

void freeAllButton(void)
{
	if (!all_buttons)
		return;
	for (uint i = 0; i < list_length(all_buttons); i++)
	{
		Button* button = list_get(all_buttons, i);
		free_Button(button);
	}
	list_free(all_buttons);
}

void check_all_buttons(SDL_Event* event)
{
	if (!all_buttons)
		return;
	for (uint i = 0; i < list_length(all_buttons); i++)
	{
		Button* Button = list_get(all_buttons, i);
		check_Button(Button, event);
	}
}

void draw_all_buttons(void)
{
	if (!all_buttons)
		return;
	for (uint i = 0; i < list_length(all_buttons); i++)
	{
		Button* Button = list_get(all_buttons, i);
		draw_Button(Button);
	}
}

list takeAllButtons(void)
{
	list temp = all_buttons;
	all_buttons = NULL;
	return temp;
}

void pushAllButtons(list buttons)
{
	if (!all_buttons)
		all_buttons = buttons;
	else
	{
		fprintf(stderr, "Error : all_buttons is not empty\n");
	}
}
