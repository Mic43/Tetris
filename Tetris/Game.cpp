#include "stdafx.h"
#include "Game.h"
#include <urlmon.h>

GameVisualState Game::GetVisualState() const
{
	// skopiuj do zwracanej stuktury aktualne wartosci kolorow na planszy
	GameVisualState visual_state;
	for (int i = 0; i < MaxColumns; ++i)
	{
		for (int j = 0; j < MaxRows; ++j)
		{
			for (int k = 0; k < MaxDepth; ++k)
			{
				visual_state.values[i][j][k] = board.GetArea(i, j, k).color;
			}
		}		
	}	

	// nanies na zwracana strukture informacje o aktualnie spadajacym klocku
	Position3D currentBlockPos = newBlockSpawner.GetCurrent().GetCurrentPosition();

	std::vector<Position2D> occupied = newBlockSpawner.GetCurrent().GetBlockShape().GetOccupied();
	for (Position2D pos : occupied)
	{		
		visual_state.SetValue(currentBlockPos.Translate(pos.row, pos.column, 0)
							 ,newBlockSpawner.GetCurrent().GetColor());
	}

	return visual_state;
}

bool Game::CanPlaceNewBlock()
{
	return newBlockSpawner.GetCurrent().IsPositionValid(newBlockSpawner.GetCurrent().GetCurrentPosition());
}

void Game::Tick()
{
	if (currentState == GameNotStarted)
		return;

	if (currentState == BlockLanded) // jesli  nie ma aktualnie spadajacego klocka
	{	
		newBlockSpawner.SpawnNew(); // zmaterialialzuj nowy

		if (!CanPlaceNewBlock()) // jesli nie mozna tego uczynic
		{
			newBlockSpawner.ResetCurrentBlock(); // skasuj nowy klocek. bo nie mozna go tam umiescic
			currentState = GameNotStarted;			// koniec gry
		}
		else
			currentState = BlockFalling;
	}
	else if(currentState == BlockFalling) // mamy spadajacy klocek
	{
		//if !canmovedown		
		// set state to landed
		// clear lines
		if (newBlockSpawner.GetCurrent().CanMoveDown()) // jesli moze spadac dalej
		{
			newBlockSpawner.GetCurrent().MoveDown();
			return;
		}		
		// jesli nie moze - obsluz kasowanie linii, skasuj klocek i zmien stan gry
		board.LockBlock(newBlockSpawner.GetCurrent());
		newBlockSpawner.ResetCurrentBlock();
		board.ClearFullLines();

		currentState = BlockLanded;
	}
}

