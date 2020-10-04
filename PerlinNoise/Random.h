#pragma once
#include <random>
#include <time.h>

class Random
{
public:
	Random();
	~Random();

	float operator() (float max);
	float operator () (float min, float max);

	int operator() (int max);
	int operator () (int min, int max);

private:
	std::mt19937 m_engine;
	std::random_device m_randomDevice;
	unsigned int m_seed;
};
