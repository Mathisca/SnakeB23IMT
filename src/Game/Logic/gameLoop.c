#include "gameLoop.h"

long long getCurrentTimestamp() {
    struct timeval currentTime;
    gettimeofday(&currentTime, 0);
    return currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000;
}

void startGameLoop() {
    setEngineState(PLAYING);
    setGameState(LOADING);

    pthread_t assetsLoadThread;
    pthread_create(&assetsLoadThread, NULL, (void *(*)(void *)) loadAssets, NULL);

    long long previous = getCurrentTimestamp();

    long long beginFps = previous;
    long long totalBeginFps = previous;

    long long frames = 0;
    long long totalFrame = 0;

    double lag = 0.0;

    while (getEngineState() == PLAYING) {
        long long currentTime = getCurrentTimestamp();
        long long elapsed = currentTime - previous;

        lag += elapsed;
        previous = currentTime;

        processEvents();

        while (lag >= GAME_LOGIC_PERIOD) {    // Maintenir le rythme des updates constant
            updateGame();
            lag -= GAME_LOGIC_PERIOD;
        }

        render(lag / GAME_LOGIC_PERIOD);

        frames++;
        totalFrame++;

        currentTime = getCurrentTimestamp();

        if (beginFps < currentTime - 1000.0) {
            double fps = (frames * 1000.0) / (currentTime - beginFps);
            double allFps = (totalFrame * 1000.0) / (currentTime - totalBeginFps);

            setFps(fps, allFps);
            frames = 0;
            beginFps = currentTime;
        }
    }

    stopGame();
}
