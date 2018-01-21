
#include "mainMenuInputHandler.h"

void processMainMenuInput() {
    toggleFullScreen();
}

void processMainMenuButtonEvent(SDL_MouseButtonEvent key) {
    switch (getCurrentBackground()) {
        case MAINMENU_1:
            startNewGame(0, 0, 5, 0);
            break;
        case MAINMENU_2:
            startNewGame(0, 1, 3, 0);
            break;
        case MAINMENU_3:
            startNewGame(1, 1, 6, 0);
            break;
        case MAINMENU_4:
            setEngineState(STOP_REQUESTED);
            break;
        default:
            break;
    }
}

void processMainMenuMouseEvent(SDL_MouseMotionEvent key) {
    int w, h;
    getWindowWidth(&w, &h);

    double scalew = w / TARGET_WIDTH;
    double scaleh = h / TARGET_HEIGHT;

    SDL_Point p = {key.x, key.y};
    SDL_Rect jouer = {(int) (450 * scalew), (int) (322 * scaleh),
                      (int) (1085 * scalew), (int) (133 * scaleh)
    };

    SDL_Rect infini = {(int) (450 * scalew), (int) (513 * scaleh),
                       (int) (1085 * scalew), (int) (133 * scaleh)
    };

    SDL_Rect automatique = {(int) (450 * scalew), (int) (704 * scaleh),
                            (int) (1085 * scalew), (int) (133 * scaleh)
    };

    SDL_Rect quitter = {(int) (450 * scalew), (int) (900 * scaleh),
                        (int) (1085 * scalew), (int) (133 * scaleh)
    };

    if (SDL_PointInRect(&p, &jouer) == SDL_TRUE) {
        setCurrentBackground(MAINMENU_1);
    } else if (SDL_PointInRect(&p, &infini) == SDL_TRUE) {
        setCurrentBackground(MAINMENU_2);
    } else if (SDL_PointInRect(&p, &automatique) == SDL_TRUE) {
        setCurrentBackground(MAINMENU_3);
    } else if (SDL_PointInRect(&p, &quitter) == SDL_TRUE) {
        setCurrentBackground(MAINMENU_4);
    } else {
        setCurrentBackground(MAINMENU_0);
    }
}

