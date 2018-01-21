#include "mainMenuRenderer.h"

BACKGROUND_TYPE currentBack = MAINMENU_0;

void renderMainMenu() {
    SDL_Renderer *renderer = getRenderer();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    int w, h;
    getWindowWidth(&w, &h);

    double scalew = w / TARGET_WIDTH;   // IMPORTANT : permet d'adapter à toutes les résolutions
    double scaleh = h / TARGET_HEIGHT;  // IMPORTANT : permet d'adapter à toutes les résolutions


    GameObject logo = {LOGO_MENU, NODIRECTION, 0, -1};
    SDL_Rect pos = {(int) ((TARGET_WIDTH / 2 - 512 / 2) * scalew), (int) (50 * scaleh), (int) (512 * scalew),
                    (int) (256 * scaleh)};

    renderBackground(currentBack); // Affichage du fond d'écran correspondant
    renderSprite(logo, &pos);

    SDL_RenderPresent(renderer);
}

int getCurrentBackground() {
    return currentBack;
}

void setCurrentBackground(int back) {
    currentBack = (BACKGROUND_TYPE) back;
}