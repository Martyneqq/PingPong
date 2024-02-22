/*#include "SDL_Object.h"

using namespace std;

SDL_Object::SDL_Object(int x0, int y0, int w0, int h0, int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2): leftPaddle(), rightPaddle(), ball() {
    
    if (&leftPaddle)
    {
        leftPaddle.x = x0;
        leftPaddle.y = y0;
        leftPaddle.w = w0;
        leftPaddle.h = h0;

        free(&leftPaddle);
    }

    if (&rightPaddle)
    {
        rightPaddle.x = x1;
        rightPaddle.y = y1;
        rightPaddle.w = w1;
        rightPaddle.h = h1;

        free(&rightPaddle);
    }

    if (&ball)
    {
        ball.x = x2;
        ball.y = y2;
        ball.w = w2;
        ball.h = h2;

        free(&ball);
    }
}

void SDL_Object::restrictions() {
    if (leftPaddle.y < 0)
    {
        leftPaddle.y = 0;
    }
    if (leftPaddle.y + leftPaddle.h > height)
    {
        leftPaddle.y = height - leftPaddle.h;
    }
    if (rightPaddle.y < 0)
    {
        rightPaddle.y = 0;
    }
    if (rightPaddle.y + rightPaddle.h > height)
    {
        rightPaddle.y = height - rightPaddle.h;
    }
}

void SDL_Object::physics() {
    SDL_Event event;

    if (SDL_HasIntersection(&ball, &rightPaddle)) {
        float rel = (rightPaddle.y + (rightPaddle.h / 2)) - (ball.y + (size / 2));
        float norm = rel / (rightPaddle.h / 2);
        float bounce = norm * (5 * M_PI / 12);
        speedX = -ballSpeed * cos(bounce);
        speedY = ballSpeed * -sin(bounce);
    }
    if (SDL_HasIntersection(&ball, &leftPaddle)) {
        float rel = (leftPaddle.y + (leftPaddle.h / 2)) - (ball.y + (size / 2));
        float norm = rel / (leftPaddle.h / 2);
        float bounce = norm * (5 * M_PI / 12);
        speedX = ballSpeed * cos(bounce);
        speedY = ballSpeed * -sin(bounce);
    }
    if (ball.y > rightPaddle.y + (rightPaddle.h / 2)) {
        rightPaddle.y += 1;
    }
    if (ball.y < rightPaddle.y + (rightPaddle.h / 2)) {
        rightPaddle.y -= 1;
    }
    if (ball.x <= 0) {
        rScore++;
        ball.x = width / 2;
        ball.y = height / 2;
        speedX = 0;
        speedY = 0;
    }
    if (ball.x + size >= width) {
        lScore++;
        ball.x = width / 2;
        ball.y = height / 2;
        speedX = 0;
        speedY = 0;
    }
    if (ball.y <= 0) {
        ball.y = 0;
        speedY = -speedY;
        ball.y += speedY;
    }
    if (ball.y + size >= height)
    {
        ball.y = height - size;
        speedY = -speedY;
    }

    ball.x += speedX;
    ball.y += speedY;
}

void SDL_Object::controls() {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (state[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }
        if (state[SDL_SCANCODE_UP])
        {
            leftPaddle.y -= 20;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            leftPaddle.y += 20;
        }
        if (state[SDL_SCANCODE_SPACE] && speedX == 0 && speedY == 0)
        {
            speedX = 0.064;
            speedY = 0.064;
        }
    }
}*/