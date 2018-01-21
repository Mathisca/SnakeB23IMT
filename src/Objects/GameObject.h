
#ifndef B23PROJET_GAMEOBJECT_H
#define B23PROJET_GAMEOBJECT_H

#include "../includes.h"

// Direction de l'objet
enum DIRECTION {
    NORTH,
    WEST,
    SOUTH,
    EAST,
    NODIRECTION
};
typedef enum DIRECTION DIRECTION;

// Sprite de l'objet
enum OBJECT_TYPE {
    EMPTY,
    SNAKE_HEAD,
    SNAKE_CORPSE,
    FRUIT,
    BANANA,
    ROCK_0,
    ROCK_1,
    ROCK_2,
    ROCK_3,
    ROCK_FLIP,
    STATIC_ROCK_0,
    STATIC_ROCK_1,
    STATIC_ROCK_2,
    LOGO_MENU
};
typedef enum OBJECT_TYPE OBJECT_TYPE;

// Structure des objets du jeu
struct GameObject {
    OBJECT_TYPE type;
    DIRECTION directionTo;
    int x;
    int y;
};
typedef struct GameObject GameObject;

#endif