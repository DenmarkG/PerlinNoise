#pragma once
//#include <math.h>
#include <cmath>

class PerlinNoise
{
	struct Vector2
	{
		float x;
		float y;

		void Normalize()
		{
			float length = sqrt((x * x) + (y * y));
			x /= length;
			y /= length;
		}
	};

public:
	PerlinNoise(int sizeX, int sizeY, int gridSizeX, int gridSizeY);
	~PerlinNoise();

	void GenerateGrid();

	float NoiseValue(float xPos, float yPos);

private:
	void DestroyGrid();
	float PerlinNormalize(float t);

	Vector2** m_unitVectorGrid;

public:
	const size_t kCellCountX;
	const size_t kCellCountY;
	const int kSizeX;
	const int kSizeY;
};

