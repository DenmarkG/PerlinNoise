#pragma once


class Color
{
	
public:
	typedef unsigned char uchar;
	Color();
	Color(uchar r, uchar g, uchar b, uchar a);
	~Color();

	static Color GetRandomColor();

public:
	uchar R;
	uchar G;
	uchar B;
	uchar A;

public:
	static const Color RED;
	static const Color BLUE;
	static const Color GREEN;
	static const Color BLACK;
	static const Color WHITE;
};

