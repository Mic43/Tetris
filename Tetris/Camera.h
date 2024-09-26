#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include "BlockShapeDefinition.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Klasa udostepnia funkcje manipulujace kamera w opengl
class Camera
{	
	double angleX = -M_PI / 2; // kat pochylenia kamery -dol gora
	double angleY = M_PI / 2; // kat pochylenia kamery -lewo prawo

	double distance = 20; // odleglosc kamery od punku, na ktory sie patrzy

	double centerX = 4; // wspolrzedne punkty na ktory patrzy sie kamera
	double centerY = 4;
	double centerZ = 4;


public:
	// ustawienie kamery w opengl na podstawie wartosci reprezentowanych przez kąty i punkty
	void Update()
	{
		double y = centerY + distance*cos(angleX);
		double z = centerZ + cos(angleY) * distance * sin(angleX);
		double x = centerX + sin(angleY) * sin(angleX)* distance;

		gluLookAt(x, y, z, centerX, centerY, centerZ, 0, 1, 0);
	}

public:

	Camera()
	{
		Update();
	}

	

	void Reset()
	{				
		Update();
	}

//	void MoveBy(Position3D aPositionOffset)
//	{
//		x += aPositionOffset.column;
//		y += aPositionOffset.row;
//		z += aPositionOffset.depth;
//
//		targetX += aPositionOffset.column;
//		targetY += aPositionOffset.row;
//		targetZ += aPositionOffset.depth;
//
//		Update();
//	}

	void RotateYBy(double angle)
	{
		angleY += angle;
	
		Update();
	}
	void RotateXBy(double angle)
	{
		angleX += angle;	
		Update();
	}
	void IncreaseDistanceBy(double change)
	{
		if ( distance + change > 0 )
			distance += change;
	}		
};
