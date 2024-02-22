#include <SDL.h>
#include <iostream>
#include <Windows.h>
#include "Render.h"
#undef main

using namespace std;

int main()
{
	//hide console
	/*HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);*/

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 1;
	}
	//title, width, height, difficulty(0 = easy, 1 = normal, 2 = hard)
	Render rend("PingPong_SDL2", 720, 720, 2);

	SDL_Quit();

	return 0;
}