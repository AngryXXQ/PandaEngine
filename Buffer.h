#pragma once
#include "IncludeManager.h"

struct Color
{
    unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;

	Color()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	Color(unsigned int c1, unsigned int c2, unsigned int c3, unsigned int c4)
	{
		r = c1;
		g = c2;
		b = c3;
		a = c4;
	}
};

class Buffer
{
public:
	Buffer();
	Buffer(float w,float h);
	~Buffer();

	void ResizeBuffer(float w, float h);
	void ClearBuffer(Color color);
	void WriteBuffer(const int& x, const int& y, const Color& color);

	std::vector<unsigned char> buffer;
private:
	float width;
	float height;
};

