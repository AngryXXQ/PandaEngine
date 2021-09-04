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

	Matrix4 Transpose();//ת�þ���
	Matrix4 Inverse();//�����
	Matrix4 TranslateMatrix(float x, float y, float z);//ƽ�ƾ���
	Matrix4 ScaleMatrix(float x, float y, float z);//���ž���
	Matrix4 RotateMatrix(float x, float y, float z);//��ת����
	Matrix4 ModelMatrix(Transform t);//ģ�ͱ任����
	Matrix4 ViewMatrix(Vector3f& position, Vector3f& target, Vector3f& uparg);//��ͼ����
	Matrix4 ProjectionMatrix(float fov, float aspect, float near, float far);//ͶӰ����
private:
	std::array<float,16> mMatrix{};
};