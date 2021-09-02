#include "Matrix.h"

Matrix4 Matrix4::operator*(const Matrix4& mat)
{
	Matrix4 tempM4;
	for (int i = 0;i < 4;++i)
	{
		for (int j = 0;j < 4;++j)
		{

		}
	}
	return tempM4;
}

Vector3f Matrix4::operator*(const Vector3f& vec3)
{
	Vector3f tempVec3;
	tempVec3.x = vec3.x * (*this)(0, 0) + vec3.y * (*this)(0, 1) + vec3.z * (*this)(0, 2) + (*this)(0, 3);
	tempVec3.y = vec3.x * (*this)(1, 0) + vec3.y* (*this)(1, 1) + vec3.z * (*this)(1, 2) + (*this)(1, 3);
	tempVec3.z = vec3.x * (*this)(2, 0) + vec3.y * (*this)(2, 1) + vec3.z * (*this)(2, 2) + (*this)(2, 3);
	tempVec3.w = vec3.x * (*this)(3, 0) + vec3.y * (*this)(3, 1) + vec3.z * (*this)(3, 2) + (*this)(3, 3);
	return tempVec3;
}