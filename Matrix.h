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

	Matrix4 UnitMatrix4();

	float& operator()(size_t x, size_t y) { return mMatrix[x * 4 + y]; }
	Matrix4 operator*(Matrix4& mat);
	Vector3f operator*(const Vector3f& vec3);

	Matrix4 Transpose();//×ªÖÃ¾ØÕó
	Matrix4 Inverse();//Äæ¾ØÕó
	Matrix4 TranslateMatrix(float x, float y, float z);//Æ½ÒÆ¾ØÕó
	Matrix4 ScaleMatrix(float x, float y, float z);//Ëõ·Å¾ØÕó
	Matrix4 RotateMatrix(float x, float y, float z);//Ğı×ª¾ØÕó
	Matrix4 ModelMatrix(Transform t);//Ä£ĞÍ±ä»»¾ØÕó
	Matrix4 ViewMatrix(Vector3f& position, Vector3f& target, Vector3f& uparg);//ÊÓÍ¼¾ØÕó
	Matrix4 ProjectionMatrix(float fov, float aspect, float near, float far);//Í¶Ó°¾ØÕó
private:
	std::array<float,16> mMatrix{};
};