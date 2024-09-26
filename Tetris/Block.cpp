#include "stdafx.h"
#include "Block.h"


bool Block::IsPositionValid(Position3D newPosition)
{
	return blockRotations[currentRotationIndex]->isPossibleOn(board_, newPosition);
}


