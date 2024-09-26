#pragma once
#include "Block.h"

struct Position3D;
class Board;

class BlockLong : public Block
{
public:

	BlockLong(Position3D currentPosition, const Board& board);

};
