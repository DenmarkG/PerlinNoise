#include "PerlinNoise.h"
#include "Random.h"
#include "Vector2.h"

#include <iostream>

float Lerp(float a, float b, float t)
{
	return ((1.F - t) * a) + (b * t);
}

float SmootherStep(float a, float b, float t)
{
	if (t >= 1)
	{
		return 1;
	}

	if (t <= 0)
	{
		return 0;
	}

	return t * t * (3 - 2 * t);
}

PerlinNoise::PerlinNoise(int sizeX, int sizeY, int gridSizeX, int gridSizeY)
	: kSizeX(sizeX)
	, kSizeY(sizeY)
	, kCellCountX(gridSizeX)
	, kCellCountY(gridSizeY)
{
	m_unitVectorGrid = nullptr;
	m_cellSize = (float)kSizeX / (float)kCellCountX;
	std::cout << "cell size = " << m_cellSize << std::endl;
}

PerlinNoise::~PerlinNoise()
{
	DestroyGrid();
}

void PerlinNoise::GenerateGrid()
{
	Random rng;

	m_unitVectorGrid = new Vector2* [kCellCountX];
	for (size_t x = 0; x < kCellCountX; ++x)
	{
		m_unitVectorGrid[x] = new Vector2[kCellCountY];
		for (size_t y = 0; y < kCellCountY; ++y)
		{
			Vector2 unit;
			unit.X = rng(-1.F, 1.F);
			unit.Y = rng(-1.F, 1.F);
			unit.Normalize();
			m_unitVectorGrid[x][y] = unit;
		}
	}
}

float PerlinNoise::CalculateNoiseAtScreenPosition(float xPos, float yPos)
{
	Vector2 gridPosition = GetGridPosition(xPos, yPos);
	return NoiseValue(gridPosition.X, gridPosition.Y);
}

Vector2 PerlinNoise::GetGridPosition(float xPosition, float yPosition)
{
	float gridX = (xPosition / kSizeX) * kCellCountX;
	float gridY = (yPosition / kSizeY) * kCellCountY;

	return Vector2(gridX, gridY);
}

float PerlinNoise::NoiseValue(float xPos, float yPos)
{
	int x0 = (int)xPos;
	int x1 = x0 == kCellCountX - 1 ? 0 : x0 + 1;
	int y0 = (int)yPos;
	int y1 = y0 == kCellCountY - 1 ? 0 : y0 + 1;

	// "Gradient" unit vectors
	Vector2 topLeft = m_unitVectorGrid[x0][y0];
	Vector2 topRight = m_unitVectorGrid[x1][y0];
	Vector2 bottomRight = m_unitVectorGrid[x1][y1];
	Vector2 bottomLeft = m_unitVectorGrid[x0][y1];

	// Offset vectors
	Vector2 v1 = { xPos - x0, yPos - y0 };
	Vector2 v2 = { xPos - (x0 + 1), yPos - y0 };
	Vector2 v3 = { xPos - (x0 + 1), yPos - (y0 + 1) };
	Vector2 v4 = { xPos - x0, yPos - (y0 + 1)};

	// Dot products
	float uv1 = (topLeft.X * v1.X) + (topLeft.Y * v1.Y);
	float uv2 = (topRight.X * v2.X) + (topRight.Y * v2.Y);
	float uv3 = (bottomRight.X * v3.X) + (bottomRight.Y * v3.Y);
	float uv4 = (bottomLeft.X * v4.X) + (bottomLeft.Y * v4.Y);

	float dx = SmootherStep(xPos, (float)x0, xPos - x0);
	float dy = SmootherStep(yPos, (float)y0, yPos - y0);

	float dx1 = Lerp(uv1, uv2, dx);
	float dx2 = Lerp(uv4, uv3, dx);

	return PerlinNormalize(Lerp(dx1, dx2, dy));
}

void PerlinNoise::DestroyGrid()
{
	for (int x = 0; x < kCellCountX; ++x)
	{
		delete[] m_unitVectorGrid[x];
		m_unitVectorGrid[x] = nullptr;
	}

	delete[] m_unitVectorGrid;
}

float PerlinNoise::PerlinNormalize(float t)
{
	static const float R = sqrt(2.F);
	return (t + R) / (2 * R);
}
