#include "stdafx.h"
#include "BlockLeftTurn.h"

BlockLeftTurn::BlockLeftTurn(Position3D currentPosition, const Board& board)
	: Block(currentPosition, board, Color(1.0f, 0.0f, 0.0f))
{
	blockRotations[0] = new BlockShapeDefinition(3, 3);
	blockRotations[0]->setOccupied(
	{
		Position2D(0, 0),
		Position2D(0, 1),
		Position2D(1, 1),
		Position2D(1, 2),
	});
	blockRotations[1] = new BlockShapeDefinition(3, 3);
	blockRotations[1]->setOccupied(
	{
		Position2D(0, 2),
		Position2D(1, 1),
		Position2D(1, 2),
		Position2D(2, 1),
	});
	blockRotations[2] = new BlockShapeDefinition(3, 3);
	blockRotations[2]->setOccupied(
	{
		Position2D(1, 0),
		Position2D(1, 1),
		Position2D(2, 1),
		Position2D(2, 2),
	});
	blockRotations[3] = new BlockShapeDefinition(3, 3);
	blockRotations[3]->setOccupied(
	{
		Position2D(0, 1),
		Position2D(1, 0),
		Position2D(1, 1),
		Position2D(2, 0),
	});
}
