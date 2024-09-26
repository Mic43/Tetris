#pragma once
#include "BlockShapeDefinition.h"
#include "Color.h"
//#include "Board.h"

class Board;

// Bazowa klasa reprezntująca klocek w grze
class Block
{
	Position3D current_position_; // pozycja w trojwymiarowej przestrzeni
	int currentRotationIndex = 0; // inndex aktualnej rotacji klocka, z tablicy blockRotations
	const Board& board_;	
	Color color_;
	
	// funkcja sprawdza czy jest możliwy obrot klocka na r
	bool CanRotate(int rotationIndex) const
	{
		return blockRotations[rotationIndex]->isPossibleOn(board_, current_position_);
	}

	int GetRotationIndex(int rotationIndexChange) const
	{
		return (currentRotationIndex + rotationIndexChange) % rotationsCount;
	}

	void RotateBy(int rotationIndexChange)
	{
		int newRotationIndex = GetRotationIndex(rotationIndexChange);
		if (!CanRotate(newRotationIndex))
			throw std::logic_error("cannot rotate");
		currentRotationIndex = newRotationIndex;
	}

protected:
	static const int rotationsCount = 4;
	// tablica zajmowanych pol przez klocek w roznych ustawieniach jego obrotu
	BlockShapeDefinition* blockRotations[rotationsCount];		
	
	// funkcja przesuwa klocek w miejsce podane jako argument, o ile to mozliwe
	void MoveTo(Position3D newPosition)
	{
		if (!IsPositionValid(newPosition))
			throw std::logic_error("new position is not valid");
		current_position_ = newPosition; 
	}
public:

	Block(Position3D currentPosition,const Board& board,Color color): current_position_(currentPosition), board_(board), color_(color)
	{
		for (int i = 0; i < rotationsCount; ++i)
		{
			blockRotations[i] = nullptr;
		}
	}
	~Block()
	{		
		for (int i = 0; i < rotationsCount; ++i)
		{
			if (blockRotations[i]!= nullptr)
				delete blockRotations[i];
		}
	}
	// funkcja sprawdza czy klocek moze zostac ustawiony w podanej pozycji zgodnie z zasadami
	bool IsPositionValid(Position3D newPosition);

	// Zestaw funkcji ktore poruszaja klockiem w poszczegolnych kierunkach
	void MoveFront()
	{
		if (!CanMoveFront())
			throw std::logic_error("cannot move more");
		MoveTo(current_position_.TranslateDepth(1));
	}
	void MoveBack()
	{
		if (!CanMoveBack())
			throw std::logic_error("cannot move more");
		MoveTo(current_position_.TranslateDepth(-1));
	}
	void MoveDown()
	{
		if (!CanMoveDown())
			throw std::logic_error("cannot move more");
		MoveTo(current_position_.TranslateRow(1));
	}
	void MoveLeft()
	{
		if (!CanMoveLeft())
			throw std::logic_error("cannot move more");
		MoveTo(current_position_.TranslateColumn(-1));
	}
	void MoveRight()
	{
		if (!CanMoveRight())
			throw std::logic_error("cannot move more");
		MoveTo(current_position_.TranslateColumn(1));
	}
	// Zestaw funkcji ktore sprawdzaja czy mozliwe jest wykonanie poszczegolnych przesuniec

	bool CanMoveBack()
	{		
		return IsPositionValid(current_position_.TranslateDepth(-1));
	}
	bool CanMoveFront()
	{
		return IsPositionValid(current_position_.TranslateDepth(1));
	}
	bool CanMoveLeft()
	{
		return IsPositionValid(current_position_.TranslateColumn(-1));
	}
	bool CanMoveRight()
	{
		return IsPositionValid(current_position_.TranslateColumn(1));
	}
	bool CanMoveDown()
	{
		return IsPositionValid(current_position_.TranslateRow(1));
	}
	// funkcje do obrotu klocka o 90 stopni w wybrana strone
	void RotateLeft()
	{
		RotateBy(-1);
	}
	void RotateRight()
	{
		RotateBy(1);
	}
	// funkcje sprawdzajace czy obrot jest mozliwy
	bool CanRotateLeft() const
	{
		return CanRotate(GetRotationIndex(-1));
	}
	bool CanRotateRight() const
	{
		return CanRotate((GetRotationIndex(1)));
	}

	Position3D GetCurrentPosition() const
	{
		return current_position_;
	}

	int virtual GetCurrentRotationIndex() const
	{
		return currentRotationIndex;
	}
	const virtual BlockShapeDefinition& GetBlockShape() const
	{
		return *(blockRotations[currentRotationIndex]);
	}
	Color GetColor() const
	{
		return color_;
	}
};

// klasa reprezentujaca "pusty klocek" - czy niewidoczny klocek np w przypadku gdy gra nie jest rozpoczeta
class NullBlock : public Block
{
public:
	NullBlock(const Board& board): Block(Position3D(0,0,0),board,Color())
	{
		blockRotations[0] = new BlockShapeDefinition(4, 4);		
		blockRotations[1] = new BlockShapeDefinition(4, 4);		
		blockRotations[2] = new BlockShapeDefinition(4, 4);		
		blockRotations[3] = new BlockShapeDefinition(4, 4);				
	}
		
};
