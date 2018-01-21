#ifndef B23PROJET_SPRITE_H
#define B23PROJET_SPRITE_H

#include "../../../includes.h"

void initTextures();

void renderSprite(GameObject sprite, SDL_Rect *target);

int directionToAngle(DIRECTION d);

SDL_Texture *getSpriteTexture();


#endif
