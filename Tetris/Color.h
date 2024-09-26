#pragma once

struct Color
{
	float r;
	float g;
	float b;


	Color(float r, float g, float b)
		: r(r),
		g(g),
		b(b)
	{
	}
	Color(int r, int g, int b)
		: r(r/256.0),
		g(g/256.0),
		b(b/256.0)
	{
	}
	Color() : Color(0.0f, 0.0f,0.0f)
	{

	}
	bool IsBlack() const
	{
		return r == 0 && g == 0 && b == 0;
	}
};