#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

    // 初始化 SDL2 和 SDL2_image
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // 定义窗口大小
    int windowWidth = 600;
    int windowHeight = 800;

    // 创建窗口和渲染器
    SDL_Window* window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

    // 设置窗口背景颜色
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    // 定义玩家矩形初始位置
    int playerX = 270;
    int playerY = 640;
    int playerWidth = 60;
    int playerHeight = 80;

    // 定义玩家矩形速度
    int playerSpeed = 10;

    // 创建玩家矩形
    SDL_Rect playerRect = { playerX, playerY, playerWidth, playerHeight };

    // 定义敌人矩形初始位置和速度
    int enemyX = rand() % (windowWidth - playerWidth);
    int enemyY = rand() % (windowHeight - playerHeight);
    int enemyWidth = 30;
    int enemyHeight = 40;
    int enemySpeedX = rand() % 5 + 1;
    int enemySpeedY = rand() % 5 + 1;

    // 等待窗口关闭事件
    bool quit = false;
    SDL_Event event;
    const int NUM_ENEMIES = 10;  // 定义敌人数量

    SDL_Rect enemyRects[NUM_ENEMIES];  // 定义敌人矩形数组

    for (int i = 0; i < NUM_ENEMIES; i++) {
    // 定义敌人矩形初始位置和速度
    int enemyX[NUM_ENEMIES];
    int enemyY[NUM_ENEMIES];
    int enemyWidth = 30;
    int enemyHeight = 40;
    int enemySpeedX[NUM_ENEMIES];
    int enemySpeedY[NUM_ENEMIES];

    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemyX[i] = rand() % (windowWidth - enemyWidth);
        enemyY[i] = rand() % (windowHeight - enemyHeight);
        enemySpeedX[i] = rand() % 5 + 1;
        enemySpeedY[i] = rand() % 5 + 1;
    }
    SDL_Rect enemyRect[NUM_ENEMIES] = { enemyX[i], enemyY[i], enemyWidth, enemyHeight };
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_a:
                    playerX -= playerSpeed;
                    break;
                case SDLK_d:
                    playerX += playerSpeed;
                    break;
                case SDLK_w:
                    playerY -= playerSpeed;
                    break;
                case SDLK_s:
                    playerY += playerSpeed;
                    break;
                }
            }
        }

        // 在渲染器上重新绘制敌人矩形和玩家矩形
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int i = 0; i < NUM_ENEMIES; i++) {
            enemyRects[i].x = enemyX[i];
            enemyRects[i].y = enemyY[i];
            SDL_RenderFillRect(renderer, &enemyRects[i]);
        }

        // 移动敌人矩形
        for (int i = 0; i < NUM_ENEMIES; i++) {
        enemyX[i] += enemySpeedX[i];
        enemyY[i] += enemySpeedY[i];

            // 如果敌人矩形碰到了窗口的边缘，改变它的移动方向
            if (enemyX[i] <= 0 || enemyX[i] >= windowWidth - enemyWidth) {
                enemySpeedX[i] = -enemySpeedX[i];
            }
            if (enemyY[i] <= 0 || enemyY[i] >= windowHeight - enemyHeight) {
                enemySpeedY[i] = -enemySpeedY[i];
            }
    }

        // 清除渲染器上的所有内容
        SDL_RenderClear(renderer);
        // 在渲染器上绘制一个与窗口大小相同的白色矩形
        SDL_Rect backgroundRect = { 0, 0, windowWidth, windowHeight };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &backgroundRect);

        // 在渲染器上重新绘制敌人矩形和玩家矩形
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &enemyRect[NUM_ENEMIES]);

        // 检测键盘事件，移动玩家矩形
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_A]) {
            playerX -= 5;
        }
        if (state[SDL_SCANCODE_D]) {
            playerX += 5;
        }
        if (state[SDL_SCANCODE_W]) {
            playerY -= 5;
        }
        if (state[SDL_SCANCODE_S]) {
            playerY += 5;
        }

        // 检查玩家矩形是否超出窗口边界
        if (playerX < 0) {
            playerX = 0;
        }
        if (playerY < 0) {
            playerY = 0;
        }
        if (playerX > windowWidth - playerWidth) {
            playerX = windowWidth - playerWidth;
        }
        if (playerY > windowHeight - playerHeight) {
            playerY = windowHeight - playerHeight;
        }

        // 更新玩家矩形位置
        playerRect.x = playerX;
        playerRect.y = playerY;


        // 在渲染器上绘制玩家矩形
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &playerRect);

        // 更新屏幕
        SDL_RenderPresent(renderer);

    }
    }
    

// 释放资源
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
IMG_Quit();
SDL_Quit();
return 0;
}

