#pragma once
#include <string>
#include <type_traits>
#include <math.h>

template<typename T>
struct Vector3
{
	union
	{
		T data[3];
		struct
		{
			T x;
			T y;
			T z;
		};
	};

	T w;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	Vector3(T val)
	{
		x = val;
		y = val;
		z = val;
		w = 1;
	}

	Vector3(T xval, T yval, T zval)
	{
		x = xval;
		y = yval;
		z = zval;
		w = 1;
	}

	Vector3(T xval, T yval, T zval, T wval)
	{
		x = xval;
		y = yval;
		z = zval;
		w = wval;
	}

	Vector3& PerspectiveDivide()
	{
		x /= w;
		y /= w;
		z /= w;
		return *this;
	}

	Vector3 operator+(const Vector3& arg)
	{
		return Vector3(x+arg.x,y+arg.y,z+arg.z);
	}

	Vector3 operator+=(const Vector3& arg)
	{
		x += arg.x;
		y += arg.y;
		z += arg.z;
		return (*this);
	}

	Vector3 operator-(const Vector3& arg)
	{
		return Vector3(x - arg.x, y - arg.y, z - arg.z);
	}

	Vector3 operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		return (*this);
	}

	Vector3 operator-=(const Vector3& arg)
	{
		x -= arg.x;
		y -= arg.y;
		z -= arg.z;
		return (*this);
	}

	Vector3 operator*(const T& arg)
	{
		return Vector3(x * arg, y * arg, z * arg);
	}

	Vector3 operator*=(const T& arg)
	{
		x *= arg;
		y *= arg;
		z *= arg;
		return (*this);
	}

	T Dot(const Vector3& arg)
	{
		return x * arg.x + y * arg.y + z * arg.z;
	}

	Vector3 Cross(const Vector3& arg)
	{
		return Vector3((y * arg.z - z * arg.y), (z * arg.x - x * arg.z), (x * arg.y - y * arg.x));
	}

	T length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3& normalized()
	{
		T len = length();
		T factor = 1.0f / len;
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	void zero() {
		x = 0;
		y = 0;
		z = 0;
	}
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3Int;

struct Vertex
{
	Vector3f vertex;   //顶点
	Vector3f color;    //颜色
	Vector3f uv[2];    //纹理坐标
	Vector3f normal;   //法线
	Vector3f tangent;  //切线
};