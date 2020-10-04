#include "PerlinNoise.h"
#include "Random.h"


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
}

PerlinNoise::~PerlinNoise()
{
	DestroyGrid();
}

void PerlinNoise::GenerateGrid()
{
	Random rng;

	m_unitVectorGrid = new Vector2* [kCellCountX + 1];
	for (int x = 0; x < kCellCountX + 1; ++x)
	{
		m_unitVectorGrid[x] = new Vector2[kCellCountY + 1];
		for (int y = 0; y < kCellCountY + 1; ++y)
		{
			Vector2 unit;
			unit.x = rng(-1.F, 1.F);
			unit.y = rng(-1.F, 1.F);
			unit.Normalize();
			m_unitVectorGrid[x][y] = unit;
		}
	}
}

float PerlinNoise::NoiseValue(float xPos, float yPos)
{
	int x0 = (int)xPos;
	int x1 = xPos + 1;// >= kCellCountX + 1 ? 0 : xPos + 1;
	int y0 = (int)yPos;
	int y1 = y0 + 1;// >= kCellCountY + 1 ? 0 : yPos + 1;

	// "Gradient" unit vectors
	Vector2 topLeft = m_unitVectorGrid[x0][y0];
	Vector2 topRight = m_unitVectorGrid[x1][y0];
	Vector2 bottomRight = m_unitVectorGrid[x1][y1];
	Vector2 bottomLeft = m_unitVectorGrid[x0][y1];

	// Offset vectors
	Vector2 v1 = { xPos - x0, yPos - y0 };
	Vector2 v2 = { xPos - x1, yPos - y0 };
	Vector2 v3 = { xPos - x1, yPos - y1 };
	Vector2 v4 = { xPos - x0, yPos - y1 };

	// Dot products
	float uv1 = (topLeft.x * v1.x) + (topLeft.y * v1.y);
	float uv2 = (topRight.x * v2.x) + (topRight.y * v2.y);
	float uv3 = (bottomRight.x * v3.x) + (bottomRight.y * v3.y);
	float uv4 = (bottomLeft.x * v4.x) + (bottomLeft.y * v4.y);

	float dx = SmootherStep(xPos, x0, xPos - x0);
	float dy = SmootherStep(yPos, y0, yPos - y0);

	float dx1 = Lerp(uv1, uv2, dx);
	float dx2 = Lerp(uv4, uv3, dx);

	return PerlinNormalize(Lerp(dx1, dx2, dy));
}

void PerlinNoise::DestroyGrid()
{
	for (int x = 0; x < kCellCountX + 1; ++x)
	{
		delete[] m_unitVectorGrid[x];
		m_unitVectorGrid[x] = nullptr;
	}

	delete[] m_unitVectorGrid;
}

float PerlinNoise::PerlinNormalize(float t)
{
	static const float R = sqrt(2);
	return (t + R) / (2 * R);
}
