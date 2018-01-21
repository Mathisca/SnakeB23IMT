#ifndef B23PROJET_BACKGROUND_H
#define B23PROJET_BACKGROUND_H

#include "../../../includes.h"

enum BACKGROUND_TYPE {
    GAME,
    MAINMENU_0,
    MAINMENU_1,
    MAINMENU_2,
    MAINMENU_3,
    MAINMENU_4
};

typedef enum BACKGROUND_TYPE BACKGROUND_TYPE;

void initBackgrounds();

void renderBackground(BACKGROUND_TYPE);


#endif
