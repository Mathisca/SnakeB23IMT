#include "fontManager.h"

static TTF_Font *textFont;
int lastSw = 0;

/*
 * Retourne le TTF_Font de la police de jeu
 */
TTF_Font *getRetroFont(int sw) {
    if (textFont != NULL && lastSw != sw)
        TTF_CloseFont(textFont);

    lastSw = sw;
    textFont = TTF_OpenFont(FONTPATH, sw / 20);

    if (textFont == NULL) {
        printf(KRED "Impossible de charger la police %s !"KRESET, FONTPATH);
        setEngineState(ERROR_OCCURED);
    }

    return textFont;
}