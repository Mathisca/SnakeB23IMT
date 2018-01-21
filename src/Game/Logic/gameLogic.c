#include "gameLogic.h"

void updateGame() {
    switch (getGameState()) {
        case LOADING:
            updateLoadingLogic();
            break;
        case MAIN_MENU:
            updateMainMenuLogic();
            break;
        case INGAME:
            updateInGameLogic();
            break;
        case PAUSE:
            break;
        default:
            printf("Illegal state : %i\n", getGameState());
            break;
    }
}