#pragma once
#ifndef TANK_HEADER
#define TANK_HEADER
#include "tool.h"


struct Tank;
typedef struct Tank Tank;

Tank* initTank(char* corps_filename, char* canon_filename,SDL_Renderer* renderer);

// draw the tank
void drawTank(Tank* tank, SDL_Renderer* renderer);
// free the tank
void freeTank(Tank* tank);
// define the collision Box of the tank and the texture size too
void setSizeTank(Tank* tank, SDL_Point size);
void setPosTank(Tank* tank, SDL_FPoint pos);
void moveTank(Tank* tank, float m);
void setRotationTank(Tank* tank, float angle);
void rotateTank(Tank* tank, float angle);
void setRotationCanon(Tank* tank, float angle);
void rotateCanon(Tank* tank, float angle);
void setVitesseTank(Tank* tank, float vitesse);

void targetPoint(Tank* tank, SDL_FPoint point);

//set state to moveLeft at the next update
void moveLeft(Tank* tank);
void moveLeftStop(Tank* tank);
//set state to moveRight at the next update
void moveRight(Tank* tank);
void moveRightStop(Tank* tank);
//set state to shoot at the next update
void shoot(Tank* tank);
//update the tank position and state
void updateTank(Tank* tank);

#endif // !TANK_HEADER
