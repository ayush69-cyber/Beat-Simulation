#include<SDL2/SDL.h>
#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;
int xoffset = 270,yoffset = 270;
int xorigin = 225,yorigin = 225;
int SCREEN_WIDTH  = 450,SCREEN_HEIGHT = 450,DICE_SIZE = 40;
class ludo{
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool gameover;
    int pc1x,pc2x,pc3x,pc4x;
    int pc1y,pc2y,pc3y,pc4y;
    int gridx[56],gridy[56];
    bool noactive;
    bool move1;
    int count6;
    public:
    ludo()
    {
        gameover = false;
        noactive = true;
        count6 = 0;
        move1 = true;
    }
    
    void drawplayer(int plx,int ply,int red,int green,int blue,int l,int w)
    {
        SDL_Rect rect = {plx,ply,l,w};
        SDL_SetRenderDrawColor(renderer,red,green,blue,255);
        SDL_RenderDrawRect(renderer,&rect);
        SDL_RenderFillRect(renderer,&rect);   
    }
    void drawline(int xtail,int ytail)
        {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderDrawLine(renderer,xorigin,yorigin,xtail,ytail);
        }
    void drawhome(int xtail,int ytail,int code)
    {
        int x,y,dx,dy;
        switch(code){
            case 1:
                for(x = xorigin;x>=xtail;x--)
                {
                    for(y = yorigin;y<=ytail;y++)
                    {
                        dx = abs(xorigin - x);
                        dy = abs(yorigin - y);
                        if(dx<dy){
                            SDL_SetRenderDrawColor(renderer,0,0,255,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                            }
                        if(dx>dy)
                        {
                            SDL_SetRenderDrawColor(renderer,255,0,0,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                        }    
                    }
                }
                break;
            case 2:
                for(x = xorigin;x>=xtail;x--)
                {
                    for(y = yorigin;y>=ytail;y--)
                    {
                        dx = abs(xorigin - x);
                        dy = abs(yorigin - y);
                        if(dx<dy){
                            SDL_SetRenderDrawColor(renderer,0,255,0,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                            }
                        if(dx>dy)
                        {
                            SDL_SetRenderDrawColor(renderer,255,0,0,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                        }    
                    }
                }
                break; 
            case 3:
                for(x = xorigin;x<=xtail;x++)
                {
                    for(y = yorigin;y>=ytail;y--)
                    {
                        dx = abs(xorigin - x);
                        dy = abs(yorigin - y);
                        if(dx<dy){
                            SDL_SetRenderDrawColor(renderer,0,255,0,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                            }
                        if(dx>dy)
                        {
                            SDL_SetRenderDrawColor(renderer,255,255,0,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                        }    
                    }
                }
                break;
            case 4:
                for(x = xorigin;x<=xtail;x++)
                {
                    for(y = yorigin;y<=ytail;y++)
                    {
                        dx = abs(xorigin - x);
                        dy = abs(yorigin - y);
                        if(dx<dy){
                            SDL_SetRenderDrawColor(renderer,0,0,255,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                            }
                        if(dx>dy)
                        {
                            SDL_SetRenderDrawColor(renderer,255,255,0,255);
                            SDL_RenderDrawPoint(renderer,x,y);
                        }    
                    }
                }
                break; 
            default:
                break;                  
        }
    }
    void drawline(int x1,int y1,int x2,int y2) 
    {
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
    }
    void grid(int n,int prevx,int prevy)
    {
        int offset = 30;
        for(int i = 0;i<=56;i++)
        {
            switch(n){
                case 1:
                    if(i<=4){gridx[i] = prevx; gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i==5){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i<=10&&i>5){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>10&&i<=12){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i>12&&i<=17){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==18){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>18&&i<=23){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i>23&&i<=25){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>25&&i<=30){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i==31){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>31&&i<=36){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>36&&i<=38){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i>38&&i<=43){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==44){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>44&&i<=49){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i==50){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>50&&i<=56){gridx[i] = prevx; gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    break;
                case 2:
                    if(i>50&&i<=56){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==44){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i<=49&&i>44){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==50){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i<=4){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==5){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>5&&i<10){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i>10&&i<=12){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>12&&i<=17){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i==18){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>18&&i<=23){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>23&&i<=25){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i>25&&i<=20){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==31){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>31&&i<=36){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i>36&&i<=38){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>38&&i<=43){gridx[i] = prevx; gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    break;
                case 3:
                    if(i>50&&i<=56){gridx[i] = prevx; gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i==31){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i<=36&&i>31){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>36&&i<=38){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i>38&&i<=43){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==44){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>44&&i<=49){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i==50){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i<=4){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i==5){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>5&&i<=10){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>10&&i<=12){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i>12&&i<=17){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==18){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>18&&i<=23){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i>23&&i<=25){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>25&&i<=30){gridx[i] = prevx; gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    break;
                case 4:
                    if(i>50&&i<=56){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==18){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i<=23&&i>18){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>23&&i<=25){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i>25&&i<=30){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==31){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy-i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>31&&i<36){gridx[i] = abs(prevx); gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    if(i>36&&i<=38){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>38&&i<=43){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i==44){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>44&&i<=49){gridx[i] = abs(prevx+i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==50){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i<=4){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i==5){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy+i*offset);prevx = gridx[i];prevy = gridy[i];}
                    if(i>5&&i<=10){gridx[i] = abs(prevx); gridy[i] = abs(prevy+i*offset);prevy = gridy[i];}
                    if(i>10&&i<=12){gridx[i] = abs(prevx-i*offset); gridy[i] = abs(prevy);prevx = gridx[i];}
                    if(i>12&&i<=17){gridx[i] = prevx; gridy[i] = abs(prevy-i*offset);prevy = gridy[i];}
                    break;
                default:
                    break;              
            }
        }
    }
    void start()
    {
        window = SDL_CreateWindow("ludo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,450,450,SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        int x=30,y=300;
        int l = 120,w = 120;
    for(int i = 1;i<=4;i++)
    {
        switch(i){
            case 1:
                drawplayer(x, y, 0, 0, 255,l,w);
                break;
            case 2:
                drawplayer(x, y - yoffset, 255, 0, 0,l,w);
                y-=yoffset;
                break;
            case 3:
                drawplayer(x + xoffset, y, 0, 255, 0,l,w);
                x+=xoffset;
                break;
            case 4:
                drawplayer(x, y + yoffset, 255, 255, 0,l,w);
                y+=yoffset;
                break;
            default:
             break;                   
        }
    }
        x = 210;y = 270;
        xoffset = 180;
        yoffset = 60;
        l = 30;
        w = 150;
        int temp;
        for(int i = 1;i<=4;i++)
        {
            switch(i){
                case 1:
                    drawplayer(x,y,0,0,255,l,w);
                    temp = l;
                    l = w;
                    w =temp;
                    drawline(180,270,180,450);
                    drawline(180,270,0,270);
                    for(int i = 0;i<=6;i++)
                    {
                        drawline(180,270+i*30,270,270+i*30);
                    }
                    for(int i = 0;i<=3;i++)
                    {
                        drawline(180+i*30,270,180+i*30,450);
                    }
                    drawline(180,270);
                    drawhome(180,270,i);
                    break;
                case 2:
                    x-=xoffset;
                    y-=yoffset;
                    drawplayer(x,y,255,0,0,l,w);
                    drawline(180,180);
                    drawline(180,180,0,180);
                    drawline(180,180,180,0);
                    for(int i = 0;i<=3;i++)
                    {
                        drawline(0,180+i*30,180,180+i*30);
                    }
                    for(int i = 0;i<=6;i++)
                    {
                        drawline(0+i*30,180,0+i*30,270);
                    }
                    drawhome(180,180,i);
                    yoffset = xoffset;
                    temp = l;
                    l = w;
                    w =temp;
                    break;
                case 3:
                    x+=xoffset;
                    y-=yoffset;     
                    drawplayer(x,y,0,255,0,l,w);
                    drawline(270,180);
                    drawline(270,180,270,0);
                    drawline(270,180,450,180);
                    for(int i = 0;i<=6;i++)
                    {
                        drawline(180,0+i*30,270,0+i*30);
                    }
                    for(int i = 0;i<=3;i++)
                    {
                        drawline(180+i*30,0,180+i*30,180);
                    }
                    drawhome(270,180,i);
                    xoffset = 60;
                    temp = l;
                    l = w;
                    w =temp;
                    break;
                case 4:
                    x+=xoffset;
                    y+=yoffset;
                    drawplayer(x,y,255,255,0,l,w);
                    drawline(270,270);
                    drawline(270,270,450,270);
                    drawline(270,270,270,450);
                    for(int i = 0;i<=3;i++)
                    {
                        drawline(270,180+i*30,450,180+i*30);
                    }
                    for(int i = 0;i<=6;i++)
                    {
                        drawline(270+i*30,180,270+i*30,270);
                    }
                    drawhome(270,270,i);
                    temp = l;
                    l = w;
                    w =temp;
                    break;
                default:
                    break;      
            }
        }
        ludo player1,player2,player3,player4;
        player1.grid(1,180+15,450-15);
        player2.grid(2,30+15,180+15);
        player3.grid(3,180+60+15,30+15);
        player4.grid(4,450-15,180+60+15);
        SDL_Event event;
        while(!gameover)
        {
            while(SDL_PollEvent(&event))
            {
               if(event.type == SDL_QUIT)
               gameover = true;
            }
        
         SDL_RenderPresent(renderer);   
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();   
    }
    int rollDiceWithAnimation() {
        int finalResult;
        for (int i = 0; i < 10; ++i) {
            int result = rand() % 6 + 1;
            drawDiceFace(result);
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
        finalResult = rand() % 6 + 1;
        drawDiceFace(finalResult);
        return finalResult;
    }

    void drawDiceFace(int number) {
        SDL_Rect rect = {450 / 2 - 40 / 2, 450 / 2 - 40 / 2, 40, 40};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        if (number == 1 || number == 3 || number == 5) {
            drawDot(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        }
        if (number >= 2) {
            drawDot(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 20);
            drawDot(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 + 20);
        }
        if (number >= 4) {
            drawDot(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 - 20);
            drawDot(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 20);
        }
        if (number == 6) {
            drawDot(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20);
            drawDot(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20);
        }
    }

    void drawDot(int x, int y) {
        SDL_Rect rect = {x - 5, y - 5, 10, 10};
        SDL_RenderFillRect(renderer, &rect);
    }
    
};
int main(int argc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    ludo play;
    play.start();
    return 0;
}