#include "../header/tool.h"
TTF_Font* global_font;

void init_font(void)
{


	global_font = TTF_OpenFont("res/font/arial.ttf", 24);
	if (!global_font)
	{
		fprintf(stderr, "Error during font loading : %s", TTF_GetError());
		exit(1);
	}
}
