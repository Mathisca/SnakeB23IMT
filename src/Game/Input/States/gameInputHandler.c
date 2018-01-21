#include "gameInputHandler.h"

void processGameInput(SDL_Keycode code) {
    switch (code) {
        case SDLK_z:
            changeDirection(NORTH);
            break;
        case SDLK_s:
            changeDirection(SOUTH);
            break;
        case SDLK_q:
            changeDirection(WEST);
            break;
        case SDLK_d:
            changeDirection(EAST);
            break;
        default:
            break;
    }
}