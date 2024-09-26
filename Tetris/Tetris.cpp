// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Block.h"
#include "Game.h"
#include <conio.h>
#include <windows.h>
#include <iostream>
#include "Scene.h"
#include <ctime>


void Draw(const GameVisualState& game_visual_state)
{	
	for (int i = 0; i < MaxRows; ++i)
	{
		for (int j = 0; j < MaxColumns; ++j)
		{
			if (!game_visual_state.values[j][i][0].IsBlack())
				std::cout << "*";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}
int inkey()
{
	if (_kbhit()) return _getch();
	else return EOF;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	Scene scene(&argc, argv);
	scene.Start();
	return 0;
}

