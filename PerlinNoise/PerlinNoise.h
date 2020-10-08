#pragma once
//#include <math.h>
#include <cmath>

#include "Vector2.h"

class PerlinNoise
{
public:
	PerlinNoise(int sizeX, int sizeY, int gridSizeX, int gridSizeY);
	~PerlinNoise();

	void GenerateGrid();

	float CalculateNoiseAtScreenPosition(float xPos, float yPos);

	size_t GetCellCountX() const { return kCellCountX; }
	size_t GetCellCountY() const { return kCellCountY; }

	int GetSizeX() const { return kSizeX; }
	int GetSizeY() const { return kSizeY; }

	//void SetOffsetX(float offsetX) { m_offsetX = offsetX; }

private:
	Vector2 GetGridPosition(float xPosition, float yPosition);
	float NoiseValue(float xPos, float yPos);
	void DestroyGrid();
	float PerlinNormalize(float t);

	Vector2** m_unitVectorGrid;

private:
	// The nuber of cells
	size_t kCellCountX;
	size_t kCellCountY;

	// The full size of the grid, in pixels
	int kSizeX;
	int kSizeY;

	float m_cellSize;

	//float m_offsetX = 0.F;
	//float m_offsetY = 0.F;
};

