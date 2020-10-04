#include "Color.h"
#include "Random.h"

Color::Color()
	: Color(0, 0, 0, 0)
{

}

Color::Color(uchar r, uchar g, uchar b, uchar a)
	: R(r)
	, G(g)
	, B(b)
	, A(a)
{
}

Color::~Color()
{
}

Color Color::GetRandomColor()
{
	Random rng;
	uchar r = rng(256);
	uchar g = rng(256);
	uchar b = rng(256);
	uchar a = rng(256);

	return Color(r, g, b, a);
}

const Color Color::RED(255, 0, 0, 255);
const Color Color::GREEN(0, 255, 0, 255);
const Color Color::BLUE(0, 0, 255, 255);
const Color Color::BLACK(0, 0, 0, 255);
const Color Color::WHITE(255, 255, 255, 255);