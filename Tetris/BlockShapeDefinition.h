#pragma once
#include <vector>
#include <stdexcept>

class Board;

struct Position2D
{
	int row;
	int column;


	Position2D(int row, int column)
		: row(row),
		  column(column)
	{
		
	}
};

struct Position3D
{
	int row;
	int column;
	int depth;

	Position3D(int column, int row,int depth)
		: row(row),
		column(column), depth(depth)
	{		
	}
	Position3D TranslateRow(int count) const
	{
		return Position3D(column,row+ count, depth);
	}
	Position3D TranslateColumn(int count) const
	{
		return Position3D(column + count, row, depth);
	}
	Position3D TranslateDepth(int count) const
	{
		return Position3D(column, row, depth + count);
	}
	Position3D Translate(int row,int column,int depth) const
	{
		return Position3D(this->column + column, this->row + row, this->depth + depth);
	}

};

// Definicja ksztaltu danego klocka
class BlockShapeDefinition
{
private:
	bool** ocuppationMatrix; // tablica reprezentujaca klocek, true - miejsce zajete przez klocek;false - miejsce puste
	int size_x_; // rozmiar tablicy reprezetnujacej klocek w wymiarze poziomym
	int size_y_; // rozmiar tablicy reprezetnujacej klocek w wymiarze pionowym
public:
	BlockShapeDefinition(int sizeX, int SizeY);


	~BlockShapeDefinition();


	int GetMaxColumns() const
	{
		return size_x_;
	}

	int GetMaxRows() const
	{
		return size_y_;
	}
	bool isOccupied(int row,int column) const
	{
		return ocuppationMatrix[row][column];
	}

	std::vector<Position2D> GetOccupied() const; // funkcja zwraca wektor tych wspolrzednych, ktore zajmuje ten klocek
	void setOccupied(std::vector<Position2D> tobeOccupied) const; // funkcja ustawia podane wspolrzedne jako zajmowane przez klocek
	bool isPossibleOn(const Board& board, Position3D shapePosition) const; 
		// funkcja sprawdza czy mozliwe jest ustawienie klocka o tym kszalcie w danej pozycji na planszy
};

