#include "Background.h"

SDL_Texture *surfaceTexture[15];

void initBackgrounds() {
    SDL_Surface *tempSurface = IMG_Load("assets/img/floor_1.png");
    if (tempSurface == NULL)
        printf("LoadSurface error %s\n", SDL_GetError());

    surfaceTexture[GAME] = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);

    tempSurface = IMG_Load("assets/img/menu.png");
    if (tempSurface == NULL)
        printf("LoadSurface error %s\n", SDL_GetError());

    surfaceTexture[MAINMENU_0] = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);

    tempSurface = IMG_Load("assets/img/menu_jouer.png");
    if (tempSurface == NULL)
        printf("LoadSurface error %s\n", SDL_GetError());
    surfaceTexture[MAINMENU_1] = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);


    tempSurface = IMG_Load("assets/img/menu_infini.png");
    if (tempSurface == NULL)
        printf("LoadSurface error %s\n", SDL_GetError());

    surfaceTexture[MAINMENU_2] = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);

    tempSurface = IMG_Load("assets/img/menu_automatique.png");
    if (tempSurface == NULL)
        printf("LoadSurface error %s\n", SDL_GetError());

    surfaceTexture[MAINMENU_3] = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);

    tempSurface = IMG_Load("assets/img/menu_quitter.png");
    if (tempSurface == NULL)
        printf("LoadSurface error %s\n", SDL_GetError());

    surfaceTexture[MAINMENU_4] = SDL_CreateTextureFromSurface(getRenderer(), tempSurface);

    SDL_FreeSurface(tempSurface);
}

void renderBackground(BACKGROUND_TYPE background) {
    if (surfaceTexture == NULL) {
        printf("Err");
    }
    SDL_RenderCopy(getRenderer(), surfaceTexture[background], NULL, NULL);
}