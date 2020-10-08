#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
	: X(0)
	, Y(0)
{
	//
}

Vector2::Vector2(float startValue)
	: X(startValue)
	, Y(startValue)
{
}

Vector2::Vector2(float x, float y)
	: X(x)
	, Y(y)
{
}

float Vector2::Dot(Vector2 rhs) const
{
	return (X * rhs.X) + (Y * rhs.Y);
}

void Vector2::Normalize()
{
	float length = sqrt((X * X) + (Y * Y));
	X /= length;
	Y /= length;
}
