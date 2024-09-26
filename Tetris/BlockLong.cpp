#include "stdafx.h"
#include "BlockLong.h"

BlockLong::BlockLong(Position3D currentPosition, const Board& board)
	: Block(currentPosition, board, Color(48, 199, 239))
{
	blockRotations[0] = new BlockShapeDefinition(4, 4);
	blockRotations[0]->setOccupied(
	{
		Position2D(0, 2),
		Position2D(1, 2),
		Position2D(2, 2),
		Position2D(3, 2),
	});
	blockRotations[1] = new BlockShapeDefinition(4, 4);
	blockRotations[1]->setOccupied(
	{
		Position2D(2, 0),
		Position2D(2, 1),
		Position2D(2, 2),
		Position2D(2, 3),
	});
	blockRotations[2] = new BlockShapeDefinition(4, 4);
	blockRotations[2]->setOccupied(
	{
		Position2D(0, 2),
		Position2D(1, 2),
		Position2D(2, 2),
		Position2D(3, 2),
	});
	blockRotations[3] = new BlockShapeDefinition(4, 4);
	blockRotations[3]->setOccupied(
	{
		Position2D(2, 0),
		Position2D(2, 1),
		Position2D(2, 2),
		Position2D(2, 3),
	});
}
