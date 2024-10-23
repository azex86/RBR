#include "../header/tank.h"

enum TankState 
{
	STOP = 0b1,
	MOVE_RIGHT = 0b10,
	MOVE_LEFT = 0b100,
	SHOOT = 0b1000,
};

struct Tank
{
	SDL_Point pos;
	SDL_Point size;
	int v;
	float angle;
	float canon_angle;
	SDL_Surface* corps_surface;
	SDL_Texture* corps;
	SDL_Surface* canon_surface;
	SDL_Texture* canon;

	enum TankState state;
};

static SDL_Point getsize(SDL_Texture* texture) {
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

Tank* initTank(char* corps_filename, char* canon_filename, SDL_Renderer* renderer)
{
	Tank* tank = (Tank*)malloc(sizeof(Tank));
	if (!tank) {
		fprintf(stderr, "Error : malloc failed\n");
	}
	tank->corps_surface = SDL_LoadBMP(corps_filename);
	if (!tank->corps_surface) {
		fprintf(stderr, "Error during load of corps surface : %s\n", SDL_GetError());
	}
	tank->corps = SDL_CreateTextureFromSurface(renderer, tank->corps_surface);
	if (!tank->corps) {
		fprintf(stderr, "Error during load of corps texture :  %s", SDL_GetError());
	}

	tank->canon_surface = SDL_LoadBMP(corps_filename);
	if (!tank->corps_surface) {
		fprintf(stderr, "Error during load of canon surface : %s\n", SDL_GetError());
	}
	tank->canon = SDL_CreateTextureFromSurface(renderer, tank->corps_surface);
	if (!tank->corps) {
		fprintf(stderr, "Error during load of canon surface :  %s", SDL_GetError());
	}

	tank->size = getsize(tank->corps);

	tank->pos.x = 0;
	tank->pos.y = 0;
	tank->angle = 0;
	tank->canon_angle = 0;
	tank->v = 1;
	printf("Tank initialized : pos = %d;%d  size = %d;%d\n", tank->pos.x, tank->pos.y, tank->size.x, tank->size.y);
	return tank;
}

void drawTank(Tank* tank, SDL_Renderer* renderer)
{
	SDL_Rect dest = { tank->pos.x, tank->pos.y, tank->size.x, tank->size.y };
	SDL_RenderCopyEx(renderer, tank->corps, NULL, &dest, tank->angle, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(renderer, tank->canon, NULL, &dest, tank->canon_angle, NULL, SDL_FLIP_NONE);
}



void freeTank(Tank* tank)
{
	SDL_FreeSurface(tank->corps_surface);
	SDL_DestroyTexture(tank->corps);
	SDL_FreeSurface(tank->canon_surface);
	SDL_DestroyTexture(tank->canon);
	free(tank);
}

void setSizeTank(Tank* tank, int size_x, int size_y)
{
	tank->size.x = size_x;
	tank->size.y = size_y;
}

void setPosTank(Tank* tank, int x, int y)
{
	tank->pos.x = x;
	tank->pos.y = y;
}

void moveTank(Tank* tank, int m)
{
	float x = (float)m * cos(tank->angle);
	float y = (float)m * sin(tank->angle);
	tank->pos.x += x;
	tank->pos.y += y;
}

void setRotationTank(Tank* tank, float angle)
{
	tank->angle = angle;
}

void rotateTank(Tank* tank, float angle)
{
	tank->angle += angle;
}

void setRotationCanon(Tank* tank, float angle)
{
	tank->canon_angle = angle;
}

void rotateCanon(Tank* tank, float angle)
{
	tank->canon_angle += angle;
}

void setVitesseTank(Tank* tank, int vitesse)
{
	tank->v = vitesse;
}

void moveLeft(Tank* tank)
{
	tank->state = MOVE_LEFT;
}

void moveRight(Tank* tank)
{
	tank->state = MOVE_RIGHT;
}

void shoot(Tank* tank)
{
	tank->state = tank->state | SHOOT;
}

void updateTank(Tank* tank)
{
	if (tank->state & MOVE_LEFT)
	{
		moveTank(tank, -tank->v);
	}
	if (tank->state & MOVE_RIGHT)
	{
		moveTank(tank, tank->v);
	}
	if (tank->state & SHOOT)
	{
		printf("Pew pew\n");
	}
	tank->state = STOP;
}

