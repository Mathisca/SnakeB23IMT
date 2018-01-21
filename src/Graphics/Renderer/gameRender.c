#include "gameRender.h"

// Affiche la frame correspondante à l'état du jeu
void render(double offset) {
    switch (getGameState()) {
        case LOADING:
            renderLoading();
            break;
        case MAIN_MENU:
            renderMainMenu();
            break;
        case INGAME:
            renderGame(offset);
            break;
        case PAUSE:
            renderGame(offset);
        default:
            break;
    }
}