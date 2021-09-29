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

	Color operator*(float t)
	{
		Color temp(r,g,b,a);
		temp.r *= t;
		temp.g *= t;
		temp.b *= t;
		temp.a *= t;
		return temp;
	}

	Color operator+(Color t)
	{
		r += t.r;
		g += t.g;
		b += t.b;
		a += t.a;
		return *this;
	}
};

enum LightType
{
	NONE = 0,
	DIRECTION_LIGHT,//平行光
	AMBIENT_LIGHT,  //环境光
	POINT_LIGHT     //点光源
};