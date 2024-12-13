#include<SDL2/SDL.h>
#include<iostream>
#include<cmath>
using namespace std;

const float g = 9.8;
const int width = 640, height = 480;

class simulation {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    float pos[2000][2];
    float mass, xspeed, yspeed, forcex, forcey;
    float accx, accy;
    float posx, posy;
    float angularspeed, angularpos;
    float force, force_angle, speed, speed_angle;
    int radius;
    int centerx, centery;
    int count = 0;

public:
    simulation() : mass(1), xspeed(0), forcex(0), forcey(mass * g), posx(width / 2), posy(height / 2), angularspeed(0), angularpos(0) {}

    void getinfo() {
        cout << "Enter The Mass, speed, angle at which it is moving, force acting on it, and angle at which it is acting: ";
        cin >> mass >> speed >> speed_angle >> force >> force_angle;

        // Convert angles to radians
        speed_angle = speed_angle * M_PI / 180;
        force_angle = force_angle * M_PI / 180;

        // Initialize speed components
        xspeed = speed * cos(speed_angle);
        yspeed = speed * sin(speed_angle);

        // Calculate angular speed and radius
        angularspeed = force / (mass * speed);
        radius = (mass * xspeed * xspeed) / force;

        // Set the center based on the initial position
        centerx = posx;
        centery = posy - radius;
    }

    void handlecalculation() {
        // Update angular position based on angular speed
        angularpos += angularspeed * (16.0 / 1000); // Time step adjustment

        // Compute the new position based on the constant radius and updated angular position
        posx = centerx + radius * sin(angularpos);
        posy = centery + radius * cos(angularpos);

        // Recalculate the speed components based on the updated position
        xspeed = -angularspeed * radius * sin(angularpos);
        yspeed = angularspeed * radius * cos(angularpos);
    }

    void start() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Circular Motion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        gameloop();
    }

    void draw() {
        rect.x = static_cast<int>(posx);
        rect.y = static_cast<int>(posy);
        rect.w = 20;
        rect.h = 20;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        // Draw trail points
        for (int i = 0; i <= count; i++) {
            SDL_RenderDrawPoint(renderer, static_cast<int>(pos[i][0]), static_cast<int>(pos[i][1]));
        }
    }

    void gameloop() {
        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT)
                    running = false;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            draw();
            SDL_RenderPresent(renderer);

            handlecalculation();

            // Update trail positions with precise float values
            pos[count][0] = posx;
            pos[count][1] = posy;
            count++;

            SDL_Delay(16);
        }

        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }
};

int main(int argc, char* argv[]) {
    simulation s;
    s.getinfo();
    s.start();
    return 0;
}
