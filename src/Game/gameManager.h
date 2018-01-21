#ifndef B23PROJET_GAMEMANAGER_H
#define B23PROJET_GAMEMANAGER_H

#include "../includes.h"

enum ENGINE_STATE {
    UNINITIALIZED,
    INIT,
    PLAYING,
    STOP_REQUESTED,
    STOPPED,
    ERROR_OCCURED
};
typedef enum ENGINE_STATE ENGINE_STATE;

enum GAME_STATE {
    LOADING,
    MAIN_MENU,
    PAUSE,
    INGAME
};

typedef enum GAME_STATE GAME_STATE;

void startGame();

void setEngineState(ENGINE_STATE);

void setGameState(GAME_STATE);

GAME_STATE getGameState();

void stopGame();

ENGINE_STATE getEngineState();

#endif