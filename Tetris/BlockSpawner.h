#pragma once
#include "Block.h"

// Klasa zajmuje sie tworzeniem klocka, ktory ma spadac
class BlockSpawner
{
	Board& board;
	Block* current = nullptr;
	const int blocksCount = 3;
public:
	BlockSpawner(Board& board)
		: board(board)
	{
		ResetCurrentBlock();
	}
	~BlockSpawner()
	{
		delete current;
	}

	void SpawnNew(); // funkcja losuje nowy klocek z mozliwych rodzajow
	void ResetCurrentBlock() // 
	{
		if (current!= nullptr)
			delete current;
		current = new NullBlock(board);
	}
	Block& GetCurrent() const
	{
		return *current;
	}
};

