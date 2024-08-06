#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

using namespace std;

const int xorigin = 320, yorigin = 240;
const int windowWidth = 640, windowHeight = 480;

class Game {
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    float xOffset;

public:
    Game() : renderer(nullptr), window(nullptr), xOffset(0) {}

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            cout << "SDL_Init Error: " << SDL_GetError() << endl;
            exit(1);
        }
    }

    void createWindow() {
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
            SDL_Quit();
            exit(1);
        }
    }

    void createRenderer() {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(1);
        }
    }

    void drawCoordinates() {
        SDL_SetRenderDrawColor(renderer, 225, 220, 0, 255);
        SDL_RenderDrawLine(renderer, xorigin, 0, xorigin, windowHeight);
        SDL_RenderDrawLine(renderer, 0, yorigin, windowWidth, yorigin);
    }

    void movewave(float x, int y) {
        SDL_RenderDrawPoint(renderer, static_cast<int>(x * 10), y);
    }

    void drawWave() {
        SDL_SetRenderDrawColor(renderer, 225, 220, 0, 255);  // Set color for the first wave

        for (float x = 0; x <= 20 * M_PI; x += 0.01f) {
            int y1 = yorigin - static_cast<int>(50 * sin(x - xOffset));  // First wave
            movewave(x, y1);  // Draw the first wave

            int y2 = yorigin - static_cast<int>(50 * sin(x * 1.3 - xOffset));  // Second wave
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Set color for the second wave
            movewave(x, y2);  // Draw the second wave

            // Calculate and draw the beat wave below the original waves
            int beatY = yorigin + 120 - (static_cast<int>(50 * sin(x - xOffset))+static_cast<int>(50 * sin(x * 1.3 - xOffset)));  // Position beat wave below original waves
            SDL_SetRenderDrawColor(renderer, 225, 192, 203, 255);  // Set color for beats
            movewave(x, beatY);  // Draw the beat wave
        }
    }

    void gameLoop() {
        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            drawCoordinates();
            drawWave();

            SDL_RenderPresent(renderer);

            // Update the wave position for animation
            xOffset += 0.05f;
            if (xOffset >= 10 * M_PI) {
                xOffset -= 10 * M_PI;
            }

            SDL_Delay(16); // Delay to limit frame rate (~60 FPS)
        }
    }

    void close() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, char* argv[]) {
    Game game;
    game.init();
    game.createWindow();
    game.createRenderer();
    game.gameLoop();
    game.close();
    cout << "Thanks For Visiting" << endl;
    return 0;
}
