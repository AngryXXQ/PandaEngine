#pragma once
#include "Vector.h"
#include "Matrix.h"
#include <vector>
#include <corecrt_math_defines.h>
#include <string>

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	Color(float c1, float c2, float c3, float c4)
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
		Color temp(r, g, b, a);
		temp.r += t.r;
		temp.g += t.g;
		temp.b += t.b;
		temp.a += t.a;
		return temp;
	}

	Color operator*(Color t)
	{
		Color temp(r, g, b, a);
		temp.r *= t.r;
		temp.g *= t.g;
		temp.b *= t.b;
		temp.a *= t.a;
		return temp;
	}
};

enum LightType
{
	NONE = 0,
	DIRECTION_LIGHT,//ƽ�й�
	AMBIENT_LIGHT,  //������
	POINT_LIGHT     //���Դ
};