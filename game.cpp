#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm> // For std::remove_if
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLAYER_SIZE = 35;
const int OBSTACLE_WIDTH = 50;
const int OBSTACLE_HEIGHT = 50;

struct Obstacle {
    int x, y, speed;

    Obstacle(int posX, int posY, int spd) : x(posX), y(posY), speed(spd) {}

    void update() {
        y += speed;
    }

    bool isOffScreen() const {
        return y > SCREEN_HEIGHT;
    }
};

class Game {
public:
    Game()
        : window(nullptr), renderer(nullptr), running(true), playerX(SCREEN_WIDTH / 2 - PLAYER_SIZE / 2), playerY(SCREEN_HEIGHT - PLAYER_SIZE - 10), level(1), score(0), obstacleSpeed(2), obstacleFrequency(60), frames(0) {}

    bool init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        window = SDL_CreateWindow("Obstacle Dodging Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        srand(static_cast<unsigned int>(time(nullptr)));
        return true;
    }

    void run() {
        SDL_Event event;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);

        while (running) {
            handleEvents(keyState);
            update();
            render();
            SDL_Delay(16); // Roughly 60 FPS
        }
    }

    void cleanUp() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    int playerX, playerY;
    int level;
    int score;
    int obstacleSpeed;
    int obstacleFrequency;
    int frames;
    std::vector<Obstacle> obstacles;

    void handleEvents(const Uint8* keyState) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        if (keyState[SDL_SCANCODE_LEFT]) {
            playerX -= 5; // Adjust the speed as needed
            if (playerX < 0) playerX = 0; // Prevent moving out of bounds
        }

        if (keyState[SDL_SCANCODE_RIGHT]) {
            playerX += 5; // Adjust the speed as needed
            if (playerX > SCREEN_WIDTH - PLAYER_SIZE) playerX = SCREEN_WIDTH - PLAYER_SIZE; // Prevent moving out of bounds
        }
    }

    void update() {
        frames++;
        if (frames % obstacleFrequency == 0) {
            int x = rand() % (SCREEN_WIDTH - OBSTACLE_WIDTH);
            obstacles.emplace_back(x, 0, obstacleSpeed);
        }

        for (auto& obs : obstacles) {
            obs.update();
        }

        obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle& obs) { return obs.isOffScreen(); }), obstacles.end());

        checkCollision();

        if (score % 100 == 0 && score > 0) {
            levelUp();
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect playerRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (const auto& obs : obstacles) {
            SDL_Rect obstacleRect = {obs.x, obs.y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
            SDL_RenderFillRect(renderer, &obstacleRect);
        }

        SDL_RenderPresent(renderer);
    }

    void checkCollision() {
        SDL_Rect playerRect = {playerX, playerY, PLAYER_SIZE, PLAYER_SIZE};

        for (const auto& obs : obstacles) {
            SDL_Rect obstacleRect = {obs.x, obs.y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
            if (SDL_HasIntersection(&playerRect, &obstacleRect)) {
                running = false;
                std::cout << "Game Over! Your Score: " << score << std::endl;
                break;
            }
        }

        score++;
    }

    void levelUp() {
        level++;
        obstacleSpeed++;
        obstacleFrequency = std::max(20, obstacleFrequency - 10);
        std::cout << "Level Up! Current Level: " << level << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init()) {
        std::cout << "Failed to initialize game!" << std::endl;
        return -1;
    }

    game.run();
    game.cleanUp();

    return 0;
}
