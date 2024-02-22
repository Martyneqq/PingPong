#include <SDL.h>
#include <stdio.h> 
#include <stdlib.h> 
#include "Object.h"

#pragma once

class Render:Object{
private:
	int lScore = 0, rScore = 0;
	bool _bLScore = false, _bRScore = false;
	bool isRunning = true;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect leftPaddle;
	SDL_Rect rightPaddle;
	SDL_Rect ball;

	float bX = ball.x;
	float bY = ball.y;

public:
	Render(const char* title, int w, int h, int diff); //title, window width, window height, difficulty
	~Render();//free renderer and window

	void SetLScore(bool lScore) {
		_bLScore = lScore;
	}
	bool GetLScore() {
		return _bLScore;
	}
	void SetRScore(bool rScore) {
		_bRScore = rScore;
	}
	bool GetRScore() {
		return _bRScore;
	}

	void controls(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle, SDL_Rect& ball, int diff);
	void physics(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle, SDL_Rect& ball, int w, int h);
	void restrictions(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle, SDL_Rect& ball, int w, int h);
	void init(SDL_Rect& leftPaddle, SDL_Rect& rightPaddle, SDL_Rect& ball);
	void botMove(SDL_Rect& rightPaddle, SDL_Rect& ball);
};