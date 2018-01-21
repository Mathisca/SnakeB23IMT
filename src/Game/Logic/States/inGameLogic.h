#ifndef B23PROJET_INGAMELOGIC_H
#define B23PROJET_INGAMELOGIC_H

#include "../../../includes.h"

void updateInGameLogic();

enum GAMEPLAY_STATE {
    NOT_STARTED,
    GAME_STARTED,
    PLAYER_DIED,
    GAME_WON
};
typedef enum GAMEPLAY_STATE GAMEPLAY_STATE;

void startNewGame(int isbot, int isinfinite, int newspeed, int initscore);

GameObject getObjectOnPosition(int, int);

void setInGameState(GAMEPLAY_STATE newState);

double getOffset();

DIRECTION getInverted(DIRECTION d);

void initGame();

void changeDirection(DIRECTION newDirection);

void newFruit();

void setSpeed(double newSpeed);

GAMEPLAY_STATE getInGameState();

int getPlayTime();

int getScore();

#endif
