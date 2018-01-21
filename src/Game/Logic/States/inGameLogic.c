#include "inGameLogic.h"

GAMEPLAY_STATE gameState = NOT_STARTED;
GameObject gGameMap[GAME_WIDTH][GAME_HEIGHT];

GameObject snakeTrail[GAME_WIDTH * GAME_HEIGHT];
int snakeTrailSize;

int advancement = 0;
int bot = 0;
int score = 0;
long playTime = 0;

double speed = 5.0;

void setInGameState(GAMEPLAY_STATE newState) {
    if (!bot) {
        gameState = newState;
        setGameState(PAUSE);
    }

}

int infinite = 0;

void startNewGame(int isbot, int isinfinite, int newspeed, int initscore) {
    setGameState(INGAME);

    bot = isbot;
    infinite = isinfinite;
    playTime = 0;
    speed = newspeed;
    score = initscore;
    gameState = NOT_STARTED;
}

void setSpeed(double newSpeed) {
    speed = newSpeed;
}

int getPlayTime() {
    return (int) (time(0) - playTime);
}

int getScore() {
    return score;
}

int canMove(DIRECTION d) {
    GameObject snake = snakeTrail[0];
    GameObject newObj;

    int newy = snake.y;
    int newx = snake.x;

    if (d == SOUTH && snake.y + 1 <= GAME_HEIGHT - 1) {
        newy = snake.y + 1;
    }
    if (d == NORTH && snake.y - 1 >= 0) {
        newy = snake.y - 1;
    }
    if (d == WEST && snake.x - 1 >= 0) {
        newx = snake.x - 1;
    }
    if (d == EAST && snake.x + 1 < GAME_WIDTH - 1) {
        newx = snake.x + 1;
    }

    newObj = gGameMap[newx][newy];

    if (newObj.type == FRUIT || newObj.type == EMPTY || newObj.type == BANANA)
        return 1;

    return 0;

}

void makeBotMove() {
    if (bot) {
        GameObject snake = snakeTrail[0];
        GameObject fruit;

        for (int i = 0; i < GAME_WIDTH; ++i) {
            for (int j = 0; j < GAME_HEIGHT; ++j) {
                if (gGameMap[i][j].type == FRUIT || gGameMap[i][j].type == BANANA)
                    fruit = gGameMap[i][j];
            }
        }

        if (snake.x > fruit.x && canMove(WEST))
            changeDirection(WEST);
        if (snake.x < fruit.x && canMove(EAST))
            changeDirection(EAST);
        if (snake.y > fruit.y && canMove(NORTH))
            changeDirection(NORTH);
        if (snake.y < fruit.y && canMove(SOUTH))
            changeDirection(SOUTH);
    }

}

void computeNextValues(int *nextX, int *nextY) {
    GameObject snake = snakeTrail[0];

    if (snake.directionTo == NORTH) {
        *nextX = snake.x;

        if ((snake.y - 1) >= 0)
            *nextY = snake.y - 1;
        else
            *nextY = GAME_HEIGHT - 1;
    } else if (snake.directionTo == WEST) {
        *nextY = snake.y;

        if ((snake.x - 1) >= 0)
            *nextX = snake.x - 1;
        else
            *nextX = GAME_WIDTH - 1;
    } else if (snake.directionTo == EAST) {
        *nextY = snake.y;

        if (snake.x + 1 <= GAME_WIDTH - 1)
            *nextX = snake.x + 1;
        else
            *nextX = 0;

    } else if (snake.directionTo == SOUTH) {
        *nextX = snake.x;

        if ((snake.y + 1) <= GAME_HEIGHT - 1)
            *nextY = snake.y + 1;
        else
            *nextY = 0;
    }
}

void updateInGameLogic() {
    if (gameState == NOT_STARTED)
        initGame();
    gameState = GAME_STARTED;

    advancement++;
    GameObject snake = snakeTrail[0];
    if (advancement >= speed) {
        int nextX = 0;
        int nextY = 0;

        makeBotMove();
        computeNextValues(&nextX, &nextY);

        int oldx = snakeTrail[0].x;
        int oldy = snakeTrail[0].y;
        DIRECTION olddir = snakeTrail[0].directionTo;

        snakeTrail[0].x = nextX;
        snakeTrail[0].y = nextY;

        OBJECT_TYPE obtype = gGameMap[nextX][nextY].type;

        if (obtype == FRUIT || obtype == BANANA) { // Bonus
            newFruit();

            GameObject trail = {SNAKE_CORPSE, snakeTrail[snakeTrailSize - 1].directionTo, oldx, oldy};

            gGameMap[trail.x][trail.y] = trail;
            snakeTrail[snakeTrailSize] = trail;

            score++;

            snakeTrailSize++;
        } else if (obtype == SNAKE_CORPSE || obtype == SNAKE_HEAD) {
            setInGameState(PLAYER_DIED);
        } else if (obtype >= ROCK_0)
            setInGameState(PLAYER_DIED);


        gGameMap[nextX][nextY] = snake;

        int tempx = 0;
        int tempy = 0;
        DIRECTION tempdir;

        for (int i = 1; i <= snakeTrailSize; ++i) {
            gGameMap[oldx][oldy] = snakeTrail[i];

            tempx = snakeTrail[i].x;
            tempy = snakeTrail[i].y;
            tempdir = snakeTrail[i].directionTo;


            snakeTrail[i].x = oldx;
            snakeTrail[i].y = oldy;
            snakeTrail[i].directionTo = olddir;

            oldx = tempx;
            oldy = tempy;
            olddir = tempdir;
        }

        advancement = 0;
    }
}

void newFruit() {
    Point posAvailable[GAME_WIDTH * GAME_HEIGHT];
    int nbpos = 0;

    for (int j = 0; j < GAME_WIDTH; ++j) {
        for (int i = 0; i < GAME_HEIGHT; ++i) {
            int valid = 0;

            if (gGameMap[j][i].type == EMPTY) {
                valid = 1;

                for (int k = 0; k < snakeTrailSize; ++k) {
                    int x = snakeTrail[k].x;
                    int y = snakeTrail[k].y;

                    if (j == x && i == y) {
                        valid = 0;
                    }
                }
            }

            if (valid) {
                posAvailable[nbpos] = (Point) {j, i};
                nbpos++;
            }
        }
    }

    if (nbpos > 0) {
        Point p = posAvailable[rand() % nbpos];
        gGameMap[p.x][p.y] = (GameObject) {(rand() % 2 ? FRUIT : BANANA), NODIRECTION, p.x, p.y};
    } else {
        printf("GG !");
        setInGameState(GAME_WON);
    }
}

void changeDirection(DIRECTION newDirection) {
    if (snakeTrail[0].directionTo != getInverted(newDirection))
        snakeTrail[0].directionTo = newDirection;
}


DIRECTION getInverted(DIRECTION d) {
    switch (d) {
        case NORTH:
            return SOUTH;
        case SOUTH:
            return NORTH;
        case EAST:
            return WEST;
        case WEST:
            return EAST;
        default:
            return NODIRECTION;
    }
}

int difficulty = 1;

void initGame() {
    playTime = time(0);
    for (int i = 0; i < GAME_WIDTH; ++i) {
        for (int j = 0; j < GAME_HEIGHT; ++j) {
            GameObject ob = {EMPTY, NODIRECTION, i, j};

            if (rand() % (20 / difficulty) == 0 && j != GAME_HEIGHT / 2 && !infinite) {
                int rocktype = rand() % 3;
                switch (rocktype) {
                    case 0:
                        ob.type = STATIC_ROCK_0;
                        break;
                    case 1:
                        ob.type = STATIC_ROCK_1;
                        break;
                    case 2:
                        ob.type = STATIC_ROCK_2;
                        break;
                    default:
                        ob.type = FRUIT;
                }
            }

            if ((j == 0 || i == 0 || j == GAME_HEIGHT - 1 || i == GAME_WIDTH - 1) && !infinite) {
                int rocktype = rand() % 4;
                switch (rocktype) {
                    case 0:
                        ob.type = ROCK_0;
                        break;
                    case 1:
                        ob.type = ROCK_1;
                        break;
                    case 2:
                        ob.type = ROCK_2;
                        break;
                    case 3:
                        ob.type = ROCK_3;
                        break;
                    default:
                        ob.type = BANANA;
                }
            }
            gGameMap[i][j] = ob;

        }
    }

    GameObject snake = {SNAKE_HEAD, WEST, GAME_WIDTH / 2, GAME_HEIGHT / 2};
    GameObject initTrail = {SNAKE_CORPSE, WEST, GAME_WIDTH / 2 + 1, GAME_HEIGHT / 2};

    gGameMap[GAME_WIDTH / 2][GAME_HEIGHT / 2] = snake;
    gGameMap[GAME_WIDTH / 2 + 1][GAME_HEIGHT / 2] = initTrail;

    newFruit();

    snakeTrail[0] = snake;
    snakeTrail[1] = initTrail;
    snakeTrailSize = 2;
}

double getOffset() {
    return advancement / speed;
}


GameObject getObjectOnPosition(int x, int y) {
    return gGameMap[x][y];
}

GAMEPLAY_STATE getInGameState() {
    return gameState;
}