#ifndef B23PROJET_INPUTHANDLER_H
#define B23PROJET_INPUTHANDLER_H

#include <SDL2/SDL_events.h>
#include "../gameManager.h"

void processEvents();

static void processKeyDown(SDL_Keysym);

static void processMouseMotion(SDL_MouseMotionEvent key);

static void processMousePress(SDL_MouseButtonEvent key);

#endif