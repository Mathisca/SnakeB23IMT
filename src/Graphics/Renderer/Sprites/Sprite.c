#include "Sprite.h"

SDL_Surface *textureSurface;
SDL_Texture *spritesTexture;
SDL_Rect spriteClips[100]; // TODO définit un max

SDL_Texture *getSpriteTexture() {
    if (spritesTexture == NULL)
        initTextures();

    return spritesTexture;
}

/**
 * Chargement et initialisation des sprites
 */
void initTextures() {
    textureSurface = IMG_Load("assets/img/sprite.png");
    if (textureSurface == NULL)
        printf("ERR %s\n\n", SDL_GetError());
    else {
        spriteClips[EMPTY].x = 0;
        spriteClips[EMPTY].y = 0;
        spriteClips[EMPTY].w = CASE_SIZE;
        spriteClips[EMPTY].h = CASE_SIZE;

        spriteClips[SNAKE_HEAD].x = 128;
        spriteClips[SNAKE_HEAD].y = 0;
        spriteClips[SNAKE_HEAD].w = CASE_SIZE;
        spriteClips[SNAKE_HEAD].h = CASE_SIZE;

        spriteClips[SNAKE_CORPSE].x = 64;
        spriteClips[SNAKE_CORPSE].y = 0;
        spriteClips[SNAKE_CORPSE].w = CASE_SIZE;
        spriteClips[SNAKE_CORPSE].h = CASE_SIZE;

        spriteClips[BANANA].x = 0;
        spriteClips[BANANA].y = 64;
        spriteClips[BANANA].w = CASE_SIZE;
        spriteClips[BANANA].h = CASE_SIZE;

        spriteClips[FRUIT].x = 0;
        spriteClips[FRUIT].y = 128;
        spriteClips[FRUIT].w = CASE_SIZE;
        spriteClips[FRUIT].h = CASE_SIZE;

        spriteClips[ROCK_0].x = 64;
        spriteClips[ROCK_0].y = 128;
        spriteClips[ROCK_0].w = CASE_SIZE;
        spriteClips[ROCK_0].h = CASE_SIZE;

        spriteClips[ROCK_1].x = 128;
        spriteClips[ROCK_1].y = 128;
        spriteClips[ROCK_1].w = CASE_SIZE;
        spriteClips[ROCK_1].h = CASE_SIZE;

        spriteClips[ROCK_2].x = 192;
        spriteClips[ROCK_2].y = 128;
        spriteClips[ROCK_2].w = CASE_SIZE;
        spriteClips[ROCK_2].h = CASE_SIZE;

        spriteClips[ROCK_3].x = 256;
        spriteClips[ROCK_3].y = 128;
        spriteClips[ROCK_3].w = CASE_SIZE;
        spriteClips[ROCK_3].h = CASE_SIZE;

        spriteClips[ROCK_FLIP].x = 256;
        spriteClips[ROCK_FLIP].y = 0;
        spriteClips[ROCK_FLIP].w = CASE_SIZE;
        spriteClips[ROCK_FLIP].h = CASE_SIZE;

        spriteClips[STATIC_ROCK_0].x = 192;
        spriteClips[STATIC_ROCK_0].y = 0;
        spriteClips[STATIC_ROCK_0].w = CASE_SIZE;
        spriteClips[STATIC_ROCK_0].h = CASE_SIZE;

        spriteClips[STATIC_ROCK_1].x = 192;
        spriteClips[STATIC_ROCK_1].y = 64;
        spriteClips[STATIC_ROCK_1].w = CASE_SIZE;
        spriteClips[STATIC_ROCK_1].h = CASE_SIZE;

        spriteClips[STATIC_ROCK_2].x = 256;
        spriteClips[STATIC_ROCK_2].y = 64;
        spriteClips[STATIC_ROCK_2].w = CASE_SIZE;
        spriteClips[STATIC_ROCK_2].h = CASE_SIZE;

        spriteClips[LOGO_MENU].x = 0;
        spriteClips[LOGO_MENU].y = 512;
        spriteClips[LOGO_MENU].w = 512;
        spriteClips[LOGO_MENU].h = 265;
    }
}

void renderSprite(GameObject sprite, SDL_Rect *target) {
    if (spritesTexture == NULL)
        spritesTexture = SDL_CreateTextureFromSurface(getRenderer(), textureSurface);

    SDL_Rect base = spriteClips[sprite.type];

    if (sprite.y != -1) {
        int angle = directionToAngle(sprite.directionTo);

        if (sprite.type >= ROCK_0 && sprite.type <= ROCK_3) {
            if (sprite.x == 0 && sprite.y == 0) { // 0/0
                base = spriteClips[ROCK_FLIP];
            } else if (sprite.x == 0 && sprite.y == GAME_HEIGHT - 1) { // 0/MAX
                base = spriteClips[ROCK_FLIP];
                angle = -90;
            } else if (sprite.x == GAME_WIDTH - 1 && sprite.y == GAME_HEIGHT - 1) {
                base = spriteClips[ROCK_FLIP];
                angle = 180;
            } else if (sprite.x == GAME_WIDTH - 1 && sprite.y == 0) {
                base = spriteClips[ROCK_FLIP];
                angle = 90;
            } else {
                if (sprite.y == GAME_HEIGHT - 1)
                    angle = 180;
                else if (sprite.x == 0) {
                    angle = 270;
                } else if (sprite.x == GAME_WIDTH - 1) {
                    angle = 90;
                }
            }

            SDL_RenderCopyEx(getRenderer(), getSpriteTexture(), &base, target,
                             angle, NULL, SDL_FLIP_NONE);

        } else {
            SDL_RenderCopyEx(getRenderer(), getSpriteTexture(), &base, target,
                             angle, NULL, SDL_FLIP_NONE);
        }
    } else {
        SDL_RenderCopyEx(getRenderer(), getSpriteTexture(), &base, target,
                         0, NULL, SDL_FLIP_NONE);
    }



}

int directionToAngle(DIRECTION d) {
    switch (d) {
        case NORTH:
            return 90;
        case SOUTH:
            return 270;
        case EAST:
            return 180;
        case WEST:
            return 0;
        default:
            return 0;
    }
}