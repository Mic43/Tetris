﻿#include "stdafx.h"
#include "BlockRightL.h"

BlockRightL::BlockRightL(Position3D currentPosition, const Board& board)
	: Block(currentPosition, board, Color(239, 121, 34))
{
	blockRotations[0] = new BlockShapeDefinition(3, 3);
	blockRotations[0]->setOccupied(
	{
		Position2D(0, 2),
		Position2D(1, 0),
		Position2D(1, 1),
		Position2D(1, 2),
	});
	blockRotations[1] = new BlockShapeDefinition(3, 3);
	blockRotations[1]->setOccupied(
	{
		Position2D(0, 1),
		Position2D(1, 1),
		Position2D(2, 1),
		Position2D(2, 2),
	});
	blockRotations[2] = new BlockShapeDefinition(3, 3);
	blockRotations[2]->setOccupied(
	{
		Position2D(1, 0),
		Position2D(1, 1),
		Position2D(1, 2),
		Position2D(2, 0),
	});
	blockRotations[3] = new BlockShapeDefinition(3, 3);
	blockRotations[3]->setOccupied(
	{
		Position2D(0, 0),
		Position2D(0, 1),
		Position2D(1, 1),
		Position2D(2, 1),
	});
}
