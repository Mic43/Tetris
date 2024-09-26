#include "stdafx.h"
#include "BlockSpawner.h"
#include "Constants.h"
#include "BlockLong.h"

#include <time.h>
#include <stdlib.h>
#include "BlockCube.h"
#include "BlockTriangle.h"
#include "BlockRightTurn.h"
#include "BlockLeftTurn.h"
#include "BlockLeftL.h"
#include "BlockRightL.h"


void BlockSpawner::SpawnNew()
{
	delete current;

	Position3D newPosition = Position3D(MaxColumns / 2 - 1, 0, MaxDepth / 2 );

	int count = 7;
	int value = std::rand() % count;

	switch (value) 
	{
		case  0:
			current = new BlockLeftL(newPosition, board);
			break;
		case  1:
			current = new BlockRightL(newPosition, board);
			break;
		case  2:
			current = new BlockLeftTurn(newPosition, board);
			break;
		case  3:
			current = new BlockRightTurn(newPosition, board);
			break;
		case  4:
			current = new BlockLong(newPosition, board);
			break;
		case  5:
			current = new BlockCube(newPosition, board);
			break;
		case  6:
			current = new BlockTriangle(newPosition, board);
			break;
		
	}	
}
