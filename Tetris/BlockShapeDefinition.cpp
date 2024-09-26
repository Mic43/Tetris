#include "stdafx.h"
#include "BlockShapeDefinition.h"
#include "Board.h"

BlockShapeDefinition::BlockShapeDefinition(int sizeX, int SizeY): size_x_(sizeX), size_y_(SizeY)
{
	ocuppationMatrix = new bool*[size_y_];
	for (int i = 0; i < size_y_; ++i)
		ocuppationMatrix[i] = new bool[size_x_];

	for (int i = 0; i < size_y_; ++i)
	{
		for (int j = 0; j < size_x_; ++j)
		{
			ocuppationMatrix[i][j] = false;
		}
	}
}

BlockShapeDefinition::~BlockShapeDefinition()
{
	for (int i = 0; i < size_y_; ++i)
		delete[] ocuppationMatrix[i];
	delete[] ocuppationMatrix;
}

std::vector<Position2D> BlockShapeDefinition::GetOccupied() const
{
	std::vector<Position2D> occupied;
	for (int i = 0; i < GetMaxColumns(); ++i)
	{
		for (int j = 0; j < GetMaxRows(); ++j)
		{
			if (isOccupied(j, i))
			{
				occupied.push_back(Position2D(j, i));
			}
		}
	}
	return occupied;
}

void BlockShapeDefinition::setOccupied(std::vector<Position2D> tobeOccupied) const
{
	for (Position2D occupied : tobeOccupied)
	{
		ocuppationMatrix[occupied.row][occupied.column] = true;
	}
}

bool BlockShapeDefinition::isPossibleOn(const Board& board, Position3D shapePosition) const
{
	std::vector<Position2D> occupied = GetOccupied();
	for (Position2D pos : occupied)
	{
		Position3D analysedPos = shapePosition.Translate(pos.row, pos.column, 0);

		if (!board.IsInBounds(analysedPos))
			return false;
		if (board.GetArea(analysedPos).isOccupied)
			return false;
	}

//	for (int i = 0; i < GetMaxColumns(); ++i)
//	{
//		for (int j = 0; j < GetMaxRows(); ++j)
//		{
//			if (isOccupied(j,i))
//			{
//				Position3D analysedPos = shapePosition.Translate(j, i, 0);
//
//				if (!board.IsInBounds(analysedPos))
//					return false;
//				if (board.GetArea(analysedPos).isOccupied)
//					return false;
//			}
//		}
//	}
	return true;
}
