#pragma once

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
		return Vector3(x + arg.x, y + arg.y, z + arg.z);
	}

	Vector3 operator-(const Vector3& arg)
	{
		return Vector3(x - arg.x, y - arg.y, z - arg.z);
	}

	Vector3 operator-=(const Vector3& arg)
	{
		return Vector3(x - arg.x, y - arg.y, z - arg.z);
	}

	Vector3 operator*(const T& arg)
	{
		return Vector3(x * arg, y * arg, z * arg);
	}

	Vector3 operator*=(const T& arg)
	{
		return Vector3(x * arg, y * arg, z * arg);
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

	Vector3& normalize()
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