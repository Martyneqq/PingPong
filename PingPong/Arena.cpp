#include <iomanip>
#include <iostream>
#include "Arena.h"
#include "Ball.h"
#include "Panel.h"

using namespace std;

void Arena::Draw(int resX, int resY)
{
	arena = new char* [resY];
	//memory alloc
	for (int i = 0; i < resY; i++)
	{
		arena[i] = new char[resY];
	}

	for (int i = 1; i <= resX; i++)
	{
		for (int j = 1; j <= resY; j++)
		{
			if (i == 1 || i == resX || j == 1 || j == resY) {
				arena[i][j] = '*';
				cout << arena[i][j];
			}
			else {
				arena[i][j] = ' ';
				cout << arena[i][j];
			}
		}
		cout << endl;
	}
}