#pragma once
#include <SDL.h>

using namespace std;

class Object{
	
protected:
	int size = 16;
	float speedX;
	float speedY;
	float ballSpeed;
public:
	void SetSpeedX(float _speedX) {
		speedX = _speedX;
	}
	bool GetSpeedX() {
		return speedX;
	}
	void SetSpeedY(float _speedY) {
		speedY = _speedY;
	}
	bool GetSpeedY() {
		return speedY;
	}
	void SetBallSpeed(float _ballSpeed) {
		ballSpeed = _ballSpeed;
	}
	bool GetBallSpeed() {
		return ballSpeed;
	}
};