#pragma once
#include "Board.h"
#include "Block.h"
#include "Constants.h"
#include <array>
#include "BlockSpawner.h"


// stan gry 
enum GameState
{
	GameNotStarted = 0,
	BlockFalling = 1,
	BlockLanded = 2	
};
// pomoczncza struktura reprezentuaca kolory wszystkich pol planszy
struct GameVisualState
{
	Color values[MaxColumns][MaxRows][MaxDepth];
	void SetValue(Position3D position,Color color)
	{
		values[position.column] [position.row][position.depth] = color;
	}
};
// glowna klasa zajmujaca sie logika rozgrywki
class Game
{
	Board board;
	GameState currentState;
	BlockSpawner newBlockSpawner;
public:
	Game(): currentState(GameNotStarted), newBlockSpawner(board)
	{		
	}
	void ReStart()
	{
		//if (currentState != GameNotStarted)
			//throw std::logic_error("Game must be in not started state!");
		currentState = BlockLanded;
		board.Reset();
		Tick();
	}
	GameVisualState GetVisualState() const; // funkcja zwraca aktualny stan calego pola gry, w celu jego pozniejszego wyswietlenia
	bool CanPlaceNewBlock(); // funkcja srawdza, czy jest mozliwe postawienie nowego klocka na planszy
	// jesli nie - to znaczy ze mamy do czynienia z koncem gry
	void Tick(); // glowna funkcja odpowiadajaca za przebieg rozgrywki 
			//- w zaleznosci od aktualnego stanu gry wkonuje wszelakie zmiany takie jak poruszanie klocka, kasowanie itp

	// funkcje oblsugujace interakcje z graczem
	void TryMoveBlockLeft() const
	{
		if (newBlockSpawner.GetCurrent().CanMoveLeft() && currentState == BlockFalling)
			newBlockSpawner.GetCurrent().MoveLeft();
	}
	void TryMoveBlockRight() const
	{
		if (newBlockSpawner.GetCurrent().CanMoveRight() && currentState == BlockFalling)
			newBlockSpawner.GetCurrent().MoveRight();
	}
	void TryRotateBlockRight() const
	{
		if(newBlockSpawner.GetCurrent().CanRotateRight() && currentState == BlockFalling)
			newBlockSpawner.GetCurrent().RotateRight();
	}
	void TryRotateBlockLeft() const
	{
		if (newBlockSpawner.GetCurrent().CanRotateLeft() && currentState == BlockFalling)
			newBlockSpawner.GetCurrent().RotateLeft();
	}
	void TryMoveBlockFront() const
	{
		if (newBlockSpawner.GetCurrent().CanMoveFront() && currentState == BlockFalling)
			newBlockSpawner.GetCurrent().MoveFront();
	}
	void TryMoveBlockBack() const
	{
		if (newBlockSpawner.GetCurrent().CanMoveBack() && currentState == BlockFalling)
			newBlockSpawner.GetCurrent().MoveBack();
	}
};
