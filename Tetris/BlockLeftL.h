#pragma once
#include "Block.h"

class Board;
struct Position3D;

class BlockLeftL : public Block
{
public:
	BlockLeftL(Position3D currentPosition, const Board& board);

	
};
