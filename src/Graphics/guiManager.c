#include "guiManager.h"

/**
 * Fichier de gestion de la fenêtre SDL et des assets
 */

static SDL_Window *gWindow;
static SDL_Renderer *gRenderer = NULL;

/**
 * Initialise la SDL et les fenêtres
 * @return réussi
 */
int initGraphics() {
    if (!initSDL() || !createWindow() || !createRenderer())
        return 0;
    return 1;
}

/**
 * Initialise les libs SDL
 */
static int initSDL() {
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
        printf(KRED "Impossible de charger SDL : %s" KRESET, SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0) {
        printf(KRED "Impossible de charger l'extension TTF : %s" KRESET, TTF_GetError());
        return 0;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        printf(KRED "Impossible de charger l'extension IMG : %s" KRESET, IMG_GetError());
        return 0;
    }

    printf(KGRN "SDL Chargée : version de SDL : %d.%d.%d, TTF : %d.%d.%d, IMAGE : %d.%d.%d\n" KRESET,
           SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL,
           SDL_TTF_MAJOR_VERSION, SDL_TTF_MINOR_VERSION, SDL_TTF_PATCHLEVEL,
           SDL_IMAGE_MAJOR_VERSION, SDL_IMAGE_MINOR_VERSION, SDL_IMAGE_PATCHLEVEL);


    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf(KRED"/!\\ Les textures ne seront pas filtrées linéairement : %s\n"KRESET, SDL_GetError());
    }

    return 1;
}

/**
 * Création de la fenêtre SDL
 */
static int createWindow() {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    gWindow = SDL_CreateWindow(GAME_TITLE,
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               DM.w, DM.h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    if (gWindow == NULL) {
        printf(KRED "Impossible de créer la fenêtre : %s\n" KRESET, SDL_GetError());
        return 0;
    }

    SDL_SetWindowResizable(gWindow, SDL_TRUE);

    return 1;
}

/**
 * Création du renderer SDL
 */
static int createRenderer() {
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == NULL) {
        printf(KRED "Impossible de créer le renderer : %s\n" KRESET, SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return 1;
}

void getWindowWidth(int *w, int *h) {
    SDL_GetWindowSize(gWindow, w, h);
}

SDL_Renderer *getRenderer() {
    return gRenderer;
}

// Affiche les FPS dans le titre de la fenêtre
void setFps(double fps, double avgFps) {
    char title[100];
    snprintf(title, 100, "%s (~%lf FPS avg : %lf)", GAME_TITLE, fps, avgFps);
    SDL_SetWindowTitle(gWindow, title);
}

void freeGraphics() {
    if (gWindow != NULL) { // Les ressources seront libérées automatiquement
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
}

static SDL_bool fullscreen = SDL_FALSE;

/**
 * Met le jeu en plein écran
 */
void toggleFullScreen() {
    if (!fullscreen) {
        fullscreen = SDL_TRUE;
    } else
        fullscreen = SDL_FALSE;
    SDL_SetWindowFullscreen(gWindow, fullscreen);
    printf(KBLU "Mode Fullscreen : %i\n" KRESET, fullscreen);
}


void *loadAssets() {
    if (!DEBUG)
        sleep(3); // placebo

    initBackgrounds();
    initTextures();
    onLoadingEnd();
    pthread_exit(NULL);
}