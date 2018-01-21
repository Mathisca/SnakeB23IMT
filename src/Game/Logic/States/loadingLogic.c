#include "loadingLogic.h"

static char initText[] = "Chargement";
static char updateText[15] = "";

static int loadState = 1;

static int loadingWaiter = 0;

void updateLoadingLogic() {
    if (loadingWaiter == 20) { // Réduction de la clock (25/sec vers ~ 1/sec)
        fixedTimeUpdateClock();
        loadingWaiter = 0;
    }

    loadingWaiter++;
}


static void fixedTimeUpdateClock() {
    if (loadState > 3)
        loadState = 1;

    char dots[3] = {0};

    for (int i = 0; i < loadState; ++i) {
        dots[i] = '.';
    }
    sprintf(updateText, "\n%s %s", initText, dots);
    loadState++;
}

char *getUpdateText() {
    if (strlen(updateText) == 0)
        fixedTimeUpdateClock();

    return updateText;
}

void onLoadingEnd() {
    setGameState(MAIN_MENU);
}