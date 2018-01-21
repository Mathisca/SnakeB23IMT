#include "inGameRenderer.h"

SDL_Texture *textTexture;
SDL_Texture *textTime;
SDL_Texture *fadeTexture;
TTF_Font *retroFont;
SDL_Surface *text;
SDL_Surface *textTimeSurface;

/**
 * Affiche le jeu
 * @param offset retard par rapport à l'update (pour l'interpolation)
 */
void renderGame(double offset) {
    // Libère les textures
    if (textTexture != NULL) {
        SDL_DestroyTexture(textTexture);
    }
    if (textTime != NULL) {
        SDL_DestroyTexture(textTime);
    }
    if (fadeTexture != NULL) {
        SDL_DestroyTexture(fadeTexture);
    }
    if (text != NULL) {
        SDL_FreeSurface(text);
    }
    if (textTimeSurface != NULL) {
        SDL_FreeSurface(textTimeSurface);
    }

    int w, h;
    getWindowWidth(&w, &h);

    double scalew = w / TARGET_WIDTH;   // IMPORTANT : permet d'adapter à toutes les résolutions
    double scaleh = h / TARGET_HEIGHT;  // IMPORTANT : permet d'adapter à toutes les résolutions

    SDL_Renderer *renderer = getRenderer();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, 0xFF);
    SDL_RenderClear(renderer);

    renderBackground(GAME); // Affiche le fond d'écran

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect rect = {(int) (128 * scalew), (int) (92 * scaleh),
                     (int) (1664 * scalew), (int) (896 * scaleh)};
    SDL_RenderFillRect(renderer, &rect);

    double currentX = 128 * scalew;
    double currentY = 92 * scaleh;

    double boxSizeW = (64 * scalew);
    double boxSizeH = (64 * scaleh);

    SDL_Rect rectScore = {(int) (122 * scalew), (int) (995 * scaleh),   // Positions des score/teps
                          (int) (244 * scalew), (int) (44 * scaleh)};   // Positions des score/teps
    SDL_Rect rectTime = {(int) (1552 * scalew), (int) (994 * scaleh),   // Positions des score/teps
                         (int) (245 * scalew), (int) (44 * scaleh)};    // Positions des score/teps

    SDL_RenderFillRect(renderer, &rectScore);   // Affiche ces rectangles
    SDL_RenderFillRect(renderer, &rectTime);    // Affiche ces rectangles

    SDL_Color color = {0, 0, 0};

    char scoreinfo[100];
    char timeInfo[100];

    if (retroFont == NULL) {
        retroFont = TTF_OpenFont(FONTPATH, (int) (50 * scalew)); // Charge la police
    }

    sprintf(scoreinfo, "Score : %i", getScore());
    sprintf(timeInfo, "Temps : %i", getPlayTime());

    text = TTF_RenderText_Solid(retroFont, scoreinfo, color);
    textTimeSurface = TTF_RenderText_Solid(retroFont, timeInfo, color);

    textTexture = SDL_CreateTextureFromSurface(renderer, text);
    textTime = SDL_CreateTextureFromSurface(renderer, textTimeSurface);

    SDL_RenderCopy(renderer, textTexture, NULL, &rectScore);
    SDL_RenderCopy(renderer, textTime, NULL, &rectTime);


    int tile = 0;

    for (int i = 0; i < GAME_WIDTH; ++i) {
        for (int j = 0; j < GAME_HEIGHT; ++j) {

            SDL_Rect bigPos = {(int) ((currentX) - 1),
                               ((int) currentY) - 1,
                               (int) boxSizeW + 1, (int) boxSizeH + 1};

            if (tile % 2 == 1)
                SDL_SetRenderDrawColor(renderer, 103, 46, 0, 0xFF);
            else
                SDL_SetRenderDrawColor(renderer, 139, 76, 25, 0xFF);

            SDL_RenderFillRect(renderer, &bigPos);

            GameObject current = getObjectOnPosition(i, j);

            if (current.type != EMPTY) {
                renderSprite(current, &bigPos); // affichage des sprites
            }

            tile++;

            currentY += boxSizeH;
        }
        tile++;

        currentY = 92 * scaleh;
        currentX += boxSizeW;
    }

    if (getGameState() == PAUSE) {
        SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        fadeTexture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_SetTextureBlendMode(fadeTexture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(fadeTexture, 150);

        SDL_RenderCopy(renderer, fadeTexture, NULL, NULL);

        SDL_FreeSurface(surface);
    }

    SDL_RenderPresent(renderer);
}

