#include "gameManager.h"

static ENGINE_STATE gEngineState = UNINITIALIZED;
static GAME_STATE gGameState;

void startGame() {
    setEngineState(INIT); // Initialisation du moteur

    if (!initGraphics()) { // Création des variables / fenêtres SDL
        printf("Fenêtre non créée, fermeture.\n");
        stopGame(); // Si on ne réussit pas, on ferme le prog
    }

    startGameLoop(); // Début du loop principal
}

void stopGame() {
    gEngineState = STOPPED; // On arrête le moteur

    printf(KRED "Fermeture en cours...\n" KRESET);

    freeGraphics(); // On libère les ressources graphiques
    exit(0);
}

void setEngineState(ENGINE_STATE new_state) {
    printf(KMAG "Nouvel état du 'moteur' : %d\n" KRESET, new_state);
    gEngineState = new_state;
}

ENGINE_STATE getEngineState() {
    return gEngineState;
}

void setGameState(GAME_STATE new_state) {
    printf(KYEL "Nouvel état du jeu : %d\n" KRESET, new_state);
    gGameState = new_state;
}

GAME_STATE getGameState() {
    return gGameState;
}