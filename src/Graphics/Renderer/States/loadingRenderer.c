#include "loadingRenderer.h"

static int widthPosition = -1;
static int screenWidth = -1;
static int sw, sh;
static TTF_Font *textFont;

void renderLoading() {
    getWindowWidth(&sw, &sh);
    int widthChanged = sw != screenWidth;

    if (widthChanged) {
        textFont = getRetroFont(sw);
        screenWidth = sw;

        if (textFont == NULL)
            return;
    }

    SDL_Renderer *renderer = getRenderer();

    SDL_SetRenderDrawColor(renderer, 10, 74, 200, 0xFF);
    SDL_RenderClear(renderer);

    SDL_Color color = {255, 255, 0};

    SDL_Surface *text = TTF_RenderText_Solid(textFont, getUpdateText(), color);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, text);

    SDL_Rect test = {0, 0, text->w, text->h};

    if (widthChanged) {
        /* La 'taille' du texte sera toujours égale à
         * la taille quand il n'y a qu'un seul point.
         * Permet d'éviter que le texte ne bouge en permanence.
         */
        widthPosition = text->w;
    }
    SDL_Rect win = {sw / 2 - widthPosition / 2,
                    sh / 2 - text->h / 2, text->w, text->h};
    SDL_RenderCopyEx(renderer, textTexture, &test, &win, 0, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(text);
}