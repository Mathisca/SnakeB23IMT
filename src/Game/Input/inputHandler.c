#include "inputHandler.h"

void processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                setEngineState(STOP_REQUESTED);
                break;
            case SDL_KEYDOWN:
                processKeyDown(event.key.keysym);
                break;
            case SDL_MOUSEMOTION:
                processMouseMotion(event.motion);
                break;
            case SDL_MOUSEBUTTONUP:
                processMousePress(event.button);
            default:
                break;
        }
    }
}

static void processMousePress(SDL_MouseButtonEvent key) {
    switch (getGameState()) {
        case MAIN_MENU:
            processMainMenuButtonEvent(key);
            break;
        case PAUSE:
            break;
        default:
            break;
    }
}


static void processMouseMotion(SDL_MouseMotionEvent key) {
    switch (getGameState()) {
        case MAIN_MENU:
            processMainMenuMouseEvent(key);
            break;
        case PAUSE:
            break;
        default:
            break;
    }
}


static void processKeyDown(SDL_Keysym key) {
    SDL_Keycode code = key.sym;
    switch (getGameState()) {
        case MAIN_MENU:
            processMainMenuInput();
            break;
        case INGAME:
            processGameInput(code);
            break;
        case PAUSE:
            break;
        default:
            printf("Illegal state : %i\n", getGameState());
            break;
    }
}