#include <SDL.h>
#include <iostream>
#include <math.h>
#include <iostream>
#include <string> 
#include "Render.h"
#include <time.h>

Render::Render(const char* title, int w, int h, int diff):window(NULL), renderer(NULL)
{
    //init SDL environment
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

        //x   //y            //w //h
    SDL_Rect leftPaddle = { size, h / 2 - h / 8, 12, h / 4 };
    SDL_Rect rightPaddle = { w - 12 - size, h / 2 - h / 8, 12, h / 4 };
    SDL_Rect ball = { w / 2, h / 2,  size, size };

    while (isRunning) //while game is on, do following fuctions (runs until ESC pressed - line 55)
    {
        init(leftPaddle, rightPaddle, ball);
        controls(leftPaddle, rightPaddle, ball, diff);
        restrictions(leftPaddle, rightPaddle, ball, w, h);
        physics(leftPaddle, rightPaddle, ball, w, h);
        botMove(rightPaddle, ball);
    }

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }
}

//draw sdl on window
void Render::init(SDL_Rect& leftPaddle, SDL_Rect &rightPaddle, SDL_Rect& ball) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //green color
    SDL_RenderFillRect(renderer, &leftPaddle); //right rect
    SDL_RenderFillRect(renderer, &rightPaddle); //left rect
    SDL_RenderFillRect(renderer, &ball); //ball

    SDL_RenderPresent(renderer);
}

void Render::controls(SDL_Rect &leftPaddle, SDL_Rect &rightPaddle, SDL_Rect &ball, int diff) {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (state[SDL_SCANCODE_ESCAPE]) //ESC to end game
        {
            isRunning = false;
        }
        if (state[SDL_SCANCODE_UP]) //up arrow to move up...
        {
            leftPaddle.y -= 20;
        }
        if (state[SDL_SCANCODE_DOWN]) //down to move down...
        {
            leftPaddle.y += 20;
        }
        if (state[SDL_SCANCODE_SPACE] && speedX == 0 && speedY == 0)//space to resume game
        {
            switch (diff) //difficulty 0 = easy, 1 = normal, 2 = hard //only speed changes
            {
            case 0:
                if (GetLScore() == true)
                {
                    speedX = -0.032;
                    speedY = 0;
                    ballSpeed = 0.032;
                }
                else if (GetRScore() == true)
                {
                    speedX = 0.032;
                    speedY = 0;
                    ballSpeed = 0.032;
                }
                break;
            case 1:
                if (GetLScore() == true)
                {
                    speedX = -0.064;
                    speedY = 0;
                    ballSpeed = 0.064;
                }
                else if (GetRScore() == true)
                {
                    speedX = 0.064;
                    speedY = 0;
                    ballSpeed = 0.064;
                }
                break;
            case 2:
                if (GetLScore() == true)
                {
                    speedX = -0.1;
                    speedY = 0;
                    ballSpeed = 0.1;
                }
                else if (GetRScore() == true)
                {
                    speedX = 0.1;
                    speedY = 0;
                    ballSpeed = 0.1;
                }
                break;
            default:
                break;
            }
        }
    }
}

//
void Render::restrictions(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle, SDL_Rect& ball, int w, int h) {
    if (leftPaddle.y < 0)//if rectangle at the bottom of screen, its position is still 0
    {
        leftPaddle.y = 0;
    }
    if (leftPaddle.y + leftPaddle.h > h)//if  highest point of rectangle is at the top, ...
    {
        leftPaddle.y = h - leftPaddle.h;
    }
    if (rightPaddle.y < 0) 
    {
        rightPaddle.y = 0;
    }
    if (rightPaddle.y + rightPaddle.h > h)
    {
        rightPaddle.y = h - rightPaddle.h;
    }
}

void Render::physics(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle, SDL_Rect& ball, int w, int h) {
    SDL_Event event;
    const int c = 10;
    ball.x = bX;
    ball.y = bY;

    if (SDL_HasIntersection(&ball, &rightPaddle)) {
        float rel = (rightPaddle.y + (rightPaddle.h / 2)) - (bY + (size / 2));//middle of paddle - middle of ball
        float norm = rel / (rightPaddle.h / 2);//(middle of paddle - middle of ball)/middle of paddle = closer to middle means lower angle
        speedX = -ballSpeed * cos(norm);
        speedY = ballSpeed * -sin(norm) * c;
    }
    if (SDL_HasIntersection(&ball, &leftPaddle)) {
        float rel = (leftPaddle.y + (leftPaddle.h / 2)) - (bY + (size / 2));
        float norm = rel / (leftPaddle.h / 2);
        speedX = ballSpeed * cos(norm) * c;
        speedY = ballSpeed * -sin(norm) * c;
    }
    if (bX <= 0) { //if right player wins
        SetRScore(true);
        SetLScore(false);
        rScore++;
        bX = w / 2; //reset ball position
        bY = h / 2;
        speedX = 0; //init speed 0 until SPACE pressed
        speedY = 0;
        leftPaddle.y = h / 2 - h / 8; //reset paddle positions
    }
    if (bX + size >= w){
        SetRScore(false);
        SetLScore(true);
        lScore++;
        bX = w / 2;
        bY = h / 2;
        speedX = 0;
        speedY = 0;
        rightPaddle.y = h / 2 - h / 8;
    }
    if (bY <= 0) {//bounce off the bottom
        bY = 0; //keep at 0
        speedY = -speedY; //reverse Y speed
    }
    if (bY + size >= h) //bounce off the top
    {
        bY = h - size; //keep at top position
        speedY = -speedY;
    }

    bX += speedX; //update ball positions
    bY += speedY;
}

//always move its middle point where the ball is
void Render::botMove(SDL_Rect& rightPaddle, SDL_Rect& ball) {
    ball.x = bX;
    ball.y = bY;
    if (bY > rightPaddle.y + (rightPaddle.h / 2)) {
        rightPaddle.y += 1;
    }
    if (bY < rightPaddle.y + (rightPaddle.h / 2)) {
        rightPaddle.y -= 1;
    }
}

//free memory
Render::~Render() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}