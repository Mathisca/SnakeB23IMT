#ifndef B23PROJET_LOOP_H
#define B23PROJET_LOOP_H

#include "../../includes.h"

#define GAME_LOGIC_PERIOD 25 // f = 1/25 Hz

void startGameLoop();

long long getCurrentTimestamp();

#endif