#include<SDL2/SDL.h>
#include<iostream>
#include<math.h>
int height = 480,width = 640;
using namespace std;
class simulation
{
    private:
        float posx,posy,initx,inity;
        float xspeed,yspeed;
        float speed,acc;
        float range,tof;
        float time;
        float angle;
        int Height;
        int pointspos[1500][2];
        int countx = 0;
        int length,breadth;
        bool running;
        bool move = false;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect rect;
        SDL_Event event;
    public:
        simulation()
        {
            running = true;
            length = 20;
            breadth = 20;
            posx = width/2-length;
            posy = height/2-breadth;
            acc = 0;
            Height = posy + 0;
            initx = posx;
            inity = posy;
        }
        void getinfo()
        {
            cout<<"At what height your projectile is from Ground?(Enter 0 if it is in ground)";
            cin>>Height;
            Height +=posy;
            cout<<"At what speed your projectile is thrown?";
            cin >>speed;
            cout<<"At what angle your projectile is thrown?(Enter 0 if thrown horizontally and 90 if thrown vertically)";
            cin>>angle;
            cout<<"At what rate speed in horizontal direction is changing ?";
            cin>>acc;
            Angle(angle*3.14/180);
            TOF();
            Range();
            start();
        }
        void start()
        {
            window = SDL_CreateWindow("Projectile Motion",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            pointspos[0][0] = rect.x;
            pointspos[0][1] = rect.y;
            draw();//drawing logic in here
            gameloop();//go to function gameloop
        }   
        void gameloop() //called in start()
        {
            while(running)
            {
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_QUIT:
                            running = false;
                            break;     
                    }
                }
                animate();
                countx++;
                Speed();
                SDL_Delay(16);    
            }
        }
        void draw() //Called in Animate Function and start function
        {
            rect.x = posx;
            rect.y = posy;
            rect.w = length;
            rect.h = breadth;
            pointspos[countx][0] = rect.x;
            pointspos[countx][1] = rect.y;
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderFillRect(renderer,&rect);
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            for(int i = 0;i<=countx;i++){
                SDL_RenderDrawPoint(renderer,pointspos[i][0],pointspos[i][1]);
                SDL_RenderDrawLine(renderer,initx,inity,pointspos[i][0],inity);
                SDL_RenderDrawLine(renderer,initx,inity,initx,pointspos[i][1]);
            }
            SDL_RenderPresent(renderer);
        }
        void animate() // Called in Gameloop
        {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            if(rect.x<range + initx || rect.y<Height)
                {
                    posx += (xspeed*16/1000);
                    posy -= (yspeed*16/1000);
                }
             draw(); //Drawing Logic goes here    
        }
        void Angle(float Angle)
        {
            float angle = Angle;
            xspeed += speed*cos(angle);
            yspeed += speed*sin(angle);
        }
        void Range()
        {
            range = xspeed * tof;
        }
        void TOF()
        {
            tof = 2*yspeed/9.8;
        }
        void Speed()
        {
            xspeed += (acc*16/1000);
            yspeed -= (9.8*16/1000);
        }
};
int main(int argc,char* argv[])
{
    simulation s;
    s.getinfo();
    return 0;
}