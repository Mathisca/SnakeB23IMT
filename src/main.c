#include "includes.h"

int main(int argc, char *args[]) { // Modif des args pour multiplateforme SDL
    if (!DEBUG) // Log dans un fichier si compilé en RELEASE
        freopen("debug.log", "w+", stdout);

    srand((unsigned int) time(0)); // Gestion de l'aléatoire

    startGame(); // Début du programme
}