#pragma once
#include "Object.h"

class SDL_Object : Object {
public:
	SDL_Rect leftPaddle;
	SDL_Rect rightPaddle;
	SDL_Rect ball;

	float speedX = 0.064;
	float speedY = 0.064;
	float ballSpeed = 0.064;

	void init();
	void controls();
	void physics();
	void restrictions();
};