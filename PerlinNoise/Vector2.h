#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float startValue);
	Vector2(float x, float y);
	~Vector2() = default;

	float Dot(Vector2 rhs) const;
	void Normalize();
public:
	float X;
	float Y;
};

