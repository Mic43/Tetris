#pragma once
#include "Constants.h"
#include <array>
#include "BlockShapeDefinition.h"
#include "Block.h"


// struktura reprezentuje jedno pole w grze
struct Area
{
	bool isOccupied; // czy jest zajete przez kiedys upadniete klocki
	Color color; // kolor pola

	Area(bool is_occupied, const Color& color)
		: isOccupied(is_occupied),
		  color(color)
	{
	}
	Area() : Area(false,Color())
	{		
	}

};
// klasa reprezentuje plansze gry
class Board
{	
	//Area*** areas;	
	Area areas[MaxColumns][MaxRows][MaxDepth]; // trojwymiarowa tablica pol, reprezentujaca stan planaszy
		
	//std::array<int, x> a;

//	int size_x_;
//	int size_y_;
//	int size_z_;

public:
	Board()
	{
		
	}
	Area GetArea(int column,int row,int depth) const
	{
		return areas[column][row][depth];
	}
	Area GetArea(const Position3D& pos) const
	{
		return GetArea(pos.column, pos.row, pos.depth);
	}
	// funcja sprawdza czy podana pozycja znajduje sie na planszy
	bool IsInBounds(const Position3D& pos) const
	{
		return pos.column > -1 && pos.row > -1 && pos.depth > -1
			&& pos.column < MaxColumns && pos.row < MaxRows && pos.depth < MaxDepth;
	}

	// funkcja powoduje zamiane klocka, ktory wlasnie spadl w zajete pola planszy
	void LockBlock(const Block& block); 
	//
	//int GetFullLinesCount();
	bool IsLineFull(int row) const; // funkcja sprawdza czy plazczyzna o podanym numerze jest cala zajeta
	void DeleteLine(int row); // funkcja "kasuje" plazczyne o podanym numerze zgodnie z zasadami gry w tetris
	void ClearFullLines(); // funkcja "kasuje" wszystkie zapelnione plazczyzny zgodnie z zasadami gry w tetris
	void Reset() // resetowania stanu planszy
	{

		for (int i = 0; i < MaxColumns; ++i)
		{
			for (int j = 0; j < MaxRows; ++j)
			{
				for (int k = 0; k < MaxDepth; ++k)
				{
					areas[i][j][k].isOccupied = false;
					areas[i][j][k].color = Color();
				}
			}
		}		
	}
};
