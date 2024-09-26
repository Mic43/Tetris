#include "stdafx.h"
#include "Board.h"

void Board::LockBlock(const Block& block)
{
	const BlockShapeDefinition& currentDef = block.GetBlockShape();
	std::vector<Position2D> occupiedPos = currentDef.GetOccupied();
	for (Position2D occupied : occupiedPos)
	{
		Position3D posOnBoard = block.GetCurrentPosition().Translate(occupied.row, occupied.column, 0);
		Area& area = areas[posOnBoard.column][posOnBoard.row][posOnBoard.depth];
		area.isOccupied = true;
		area.color = block.GetColor();
	}
}

bool Board::IsLineFull(int row) const
{
	for (int c = 0; c < MaxColumns; ++c)
	{
		for (int d = 0; d < MaxDepth; ++d)
		{
			if (!areas[c][row][d].isOccupied)
				return false;
		}
	}
	return true;
}

void Board::DeleteLine(int row)
{
	for (int c = 0; c < MaxColumns; ++c)
	{
		for (int d = 0; d < MaxDepth; ++d)
		{
			for (int r = row; r >= 1; --r)
			{
				areas[c][r][d] = areas[c][r - 1][d];
			}			
			areas[c][0][d] = Area();			
		}

	}
}

void Board::ClearFullLines()
{
	for (int r = MaxRows - 1; r >= 0; --r)
	{
		if (IsLineFull(r))
		{
			DeleteLine(r);
			r++;
		}
	}

}
