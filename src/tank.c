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
	SDL_FPoint pos;
	SDL_Point size;
	SDL_Point canon_size;
	float v;
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

	tank->canon_surface = SDL_LoadBMP(canon_filename);
	if (!tank->canon_surface) {
		fprintf(stderr, "Error during load of canon surface : %s\n", SDL_GetError());
	}
	tank->canon = SDL_CreateTextureFromSurface(renderer, tank->canon_surface);
	if (!tank->canon) {
		fprintf(stderr, "Error during load of canon surface :  %s", SDL_GetError());
	}

	tank->size = getsize(tank->corps);
	tank->canon_size = getsize(tank->canon);
	tank->pos.x = 0;
	tank->pos.y = 0;
	tank->angle = 0;
	tank->canon_angle = 0;
	tank->v = 0.1;
	tank->state = STOP;

	printf("Tank initialized : pos = %f;%f  size = %d;%d\n", tank->pos.x, tank->pos.y, tank->size.x, tank->size.y);
	return tank;
}

void drawTank(Tank* tank, SDL_Renderer* renderer)
{
	SDL_Rect dest = { tank->pos.x, tank->pos.y, tank->size.x, tank->size.y };
	SDL_RenderCopyEx(renderer, tank->corps, NULL, &dest, tank->angle, NULL, SDL_FLIP_NONE);
	SDL_Rect dest_canon = { tank->pos.x + tank->size.x/2, tank->pos.y + tank->size.y/2, tank->canon_size.x, tank->canon_size.y };
	SDL_RenderCopyEx(renderer, tank->canon, NULL, &dest_canon, tank->canon_angle, NULL, SDL_FLIP_NONE);
}



void freeTank(Tank* tank)
{
	SDL_FreeSurface(tank->corps_surface);
	SDL_DestroyTexture(tank->corps);
	SDL_FreeSurface(tank->canon_surface);
	SDL_DestroyTexture(tank->canon);
	free(tank);
}

void setSizeTank(Tank* tank, SDL_Point size)
{
	tank->size.x = size.x;
	tank->size.y = size.y;
}

void setPosTank(Tank* tank, SDL_FPoint pos)
{
	tank->pos.x = pos.x;
	tank->pos.y = pos.y;
}

void moveTank(Tank* tank, float m)
{
	float angle_rad = tank->angle * M_PI / 180;
	float x = (float)m * SDL_cosf(angle_rad);
	float y = (float)m * SDL_sinf(angle_rad);
	tank->pos.x += x;
	tank->pos.y += y;

	//on recalcule l'orientation du canon
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	targetPoint(tank, (SDL_FPoint) { (float)mx, (float)my });
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

void setVitesseTank(Tank* tank, float vitesse)
{
	tank->v = vitesse;
}

void targetPoint(Tank* tank, SDL_FPoint point)
{
	float angle_rad = SDL_atan2f(point.y - tank->pos.y, point.x - tank->pos.x);
	tank->canon_angle = angle_rad * 180/ M_PI - 90;
	//3.14 <-> 180
}

void moveLeft(Tank* tank)
{
	tank->state = MOVE_LEFT;
}

void moveLeftStop(Tank* tank)
{
	tank->state = tank->state & ~MOVE_LEFT;
}

void moveRight(Tank* tank)
{
	tank->state = MOVE_RIGHT;
}

void moveRightStop(Tank* tank)
{
	tank->state = tank->state & ~MOVE_RIGHT;
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
		tank->state = tank->state & ~SHOOT;
	}

	printf("Tank : pos = (%f;%f) angle = %f canon_angle = %f\r", tank->pos.x, tank->pos.y, tank->angle,tank->canon_angle);
}

