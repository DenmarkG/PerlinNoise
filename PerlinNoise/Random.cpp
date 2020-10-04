#include "Random.h"

Random::Random()
	: m_engine()
	, m_randomDevice()
{
	m_seed = m_randomDevice();
	m_engine.seed(m_seed);
}

Random::~Random()
{
	//
}

float Random::operator()(float max)
{
	std::uniform_real_distribution<float> distribution(0, max);
	return distribution(m_engine);
}

float Random::operator()(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(m_engine);
}

int Random::operator()(int max)
{
	std::uniform_int_distribution<int> distribution(0, max);
	return distribution(m_engine);
}

int Random::operator()(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(m_engine);
}