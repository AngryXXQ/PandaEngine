#pragma once
#include <array>
#include "Vector.h"

struct Transform
{
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

	Transform():scale(1.0f, 1.0f, 1.0f){}
};

class Matrix4
{
public:
	Matrix4() {}
	~Matrix4(){}

	float operator()(size_t x, size_t y) { return matrixArray[x * 4 + y]; }

	Matrix4 operator* (const Matrix4& mat);
	Vector3f operator* (const Vector3f& vec3);

private:
	std::array<float,16> matrixArray{};
};