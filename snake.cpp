#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;
const int GRID_SIZE = 20;
const int MAX_LENGTH = 100;
const int CIRCLE_RADIUS = 10;
void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}
class SnakeGame {
    int posX[MAX_LENGTH];
    int posY[MAX_LENGTH];
    int length;
    int xspeed, yspeed;
    bool gameover;
    int fruitX, fruitY;
    SDL_Renderer* renderer;
    SDL_Window* window;
    int score;
public:
    SnakeGame() {
        posX[0] = SCREEN_WIDTH / 2;
        posY[0] = SCREEN_HEIGHT / 2;
        length = 1;
        xspeed = 0;
        yspeed = 0;
        score = 0;
        gameover = false;
        fruitX = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
        fruitY = (rand() % (SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE;
    }
    void start() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            cout << "SDL Initialization Error: " << SDL_GetError() << endl;
            return;
        }
        window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            cout << "Window Creation Error: " << SDL_GetError() << endl;
            return;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            cout << "Renderer Creation Error: " << SDL_GetError() << endl;
            return;
        }
        eventLoop();
    }
    void eventLoop() {
        SDL_Event event;
        while (!gameover) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)
                    gameover = true;
            }
            handleInput();
            update();
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw();
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
        cout << "Game Over! Score = " << score << endl;
        gameExit();
    }
    void handleInput() {
        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        if (keystate[SDL_SCANCODE_W] && yspeed == 0 &&posY[0] > CIRCLE_RADIUS) {
            xspeed = 0;
            yspeed = -GRID_SIZE;
        }
        if (keystate[SDL_SCANCODE_S] && yspeed == 0 && posY[0] < SCREEN_HEIGHT - CIRCLE_RADIUS) {
            xspeed = 0;
            yspeed = GRID_SIZE;
        }
        if (keystate[SDL_SCANCODE_A] && xspeed == 0 && posX[0] > CIRCLE_RADIUS) {
            xspeed = -GRID_SIZE;
            yspeed = 0;
        }
        if (keystate[SDL_SCANCODE_D] && xspeed == 0 && posX[0] < SCREEN_WIDTH - CIRCLE_RADIUS) {
            xspeed = GRID_SIZE;
            yspeed = 0;
        }
    }
    void update() {
        for (int i = length - 1; i > 0; i--) {
            posX[i] = posX[i - 1];
            posY[i] = posY[i - 1];
        }
        posX[0] += xspeed;
        posY[0] += yspeed;
        if (posX[0] < CIRCLE_RADIUS || posX[0] > SCREEN_WIDTH - CIRCLE_RADIUS || posY[0] < CIRCLE_RADIUS || posY[0] > SCREEN_HEIGHT - CIRCLE_RADIUS) {
            gameover = true;
        }
        for (int i = 1; i < length; i++) {
            if ((posX[0] == posX[i]) && (posY[0] == posY[i])) {
                gameover = true;
                break;
            }
        }
        if ((posX[0] - fruitX) * (posX[0] - fruitX) + (posY[0] - fruitY) * (posY[0] - fruitY) <= CIRCLE_RADIUS * CIRCLE_RADIUS) {
            length++;
            score += 5;
            fruitX = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
            fruitY = (rand() % (SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE;

        }
    }
    void draw() {
        SDL_SetRenderDrawColor(renderer, 230, 0, 0, 255);
        for (int i = 0; i < length; i++) {
            drawCircle(renderer, posX[i], posY[i], CIRCLE_RADIUS);
        }
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        drawCircle(renderer, fruitX, fruitY, CIRCLE_RADIUS);
    }

    void gameExit() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char* argv[]) {
    srand(time(0));
    SnakeGame game;
    game.start();
    return 0;
}
