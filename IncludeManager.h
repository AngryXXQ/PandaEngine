#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <vector>
#include <corecrt_math_defines.h>
#include <string>

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