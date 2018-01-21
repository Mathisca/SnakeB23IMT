#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Graphics/Renderer/Sprites/Background.h"

#include "Game/Input/States/mainMenuInputHandler.h"
#include "Game/Input/inputHandler.h"
#include "Game/Input/States/gameInputHandler.h"
#include "Game/Logic/States/loadingLogic.h"
#include "Game/Logic/States/mainMenuLogic.h"
#include "Game/Logic/States/inGameLogic.h"
#include "Game/Logic/gameLogic.h"
#include "Game/Logic/gameLoop.h"
#include "Game/gameManager.h"

#include "Graphics/Renderer/States/loadingRenderer.h"
#include "Graphics/Renderer/States/mainMenuRenderer.h"
#include "Graphics/Renderer/States/inGameRenderer.h"
#include "Graphics/Renderer/fontManager.h"
#include "Graphics/Renderer/gameRender.h"
#include "Graphics/Renderer/Sprites/Sprite.h"
#include "Graphics/guiManager.h"

#include "Objects/GameObject.h"
#include "Objects/Point.h"

#include <stdio.h>
#include <sys/time.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#include "const.h"