#pragma once
#include "Block.h"

// klasa repreztnujaca klock w ksztalcie szescianu
// reszta klas z przedrostkiem Block - analogicznie reprezentuja poszczegolne rodzaje klockow
class BlockCube : public Block
{
public:
	BlockCube(const Position3D& currentPosition, const Board& board);
};
