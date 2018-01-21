#ifndef B23PROJET_GUIMANAGER_H
#define B23PROJET_GUIMANAGER_H

#include "../includes.h"

#if DEBUG
#define GAME_TITLE "SNAKE Par Mathis & Hugo (DEBUG)"
#else
#define GAME_TITLE "SNAKE Par Mathis & Hugo"
#endif

int initGraphics();

SDL_Renderer *getRenderer();

void *loadAssets();

static int createWindow();

static int initSDL();

static int createRenderer();

void setFps(double, double);

void getWindowWidth(int *w, int *h);

void freeGraphics();

void toggleFullScreen();

#endif
