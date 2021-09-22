#include "Matrix.h"
#include <corecrt_math_defines.h>

Matrix4 Matrix4::UnitMatrix4()
{
    Matrix4 temp;
    temp(0, 0) = 1;
    temp(1, 1) = 1;
    temp(2, 2) = 1;
    temp(3, 3) = 1;
    return temp;
}

Matrix4 Matrix4::operator*(Matrix4& matrix)
{
	Matrix4 tempM4;
	int temp = 4;
	for (int i = 0;i < temp;++i)
	{
		for (int count = 0;count < temp;++count)
		{
			float result = 0;
			for (int j = 0;j < temp;++j)
			{
				result += (*this)(i, j) * matrix(j, count);
			}
			tempM4(i, count) = result;
		}
	}
	return tempM4;
}

Vector3f Matrix4::operator*(const Vector3f& vec3)
{
	Vector3f tempVec3(0,0,0);
	tempVec3.x = vec3.x * (*this)(0, 0) + vec3.y * (*this)(0, 1) + vec3.z * (*this)(0, 2) + (*this)(0, 3);
	tempVec3.y = vec3.x * (*this)(1, 0) + vec3.y* (*this)(1, 1) + vec3.z * (*this)(1, 2) + (*this)(1, 3);
	tempVec3.z = vec3.x * (*this)(2, 0) + vec3.y * (*this)(2, 1) + vec3.z * (*this)(2, 2) + (*this)(2, 3);
	tempVec3.w = vec3.x * (*this)(3, 0) + vec3.y * (*this)(3, 1) + vec3.z * (*this)(3, 2) + (*this)(3, 3);
	return tempVec3;
}

Matrix4 Matrix4::Transpose() {
    Matrix4 tMatrix;
    //First row
    tMatrix(0, 0) = (*this)(0, 0);
    tMatrix(0, 1) = (*this)(1, 0);
    tMatrix(0, 2) = (*this)(2, 0);
    tMatrix(0, 3) = (*this)(3, 0);

    //Second row
    tMatrix(1, 0) = (*this)(0, 1);
    tMatrix(1, 1) = (*this)(1, 1);
    tMatrix(1, 2) = (*this)(2, 1);
    tMatrix(1, 3) = (*this)(3, 1);

    //Third row
    tMatrix(2, 0) = (*this)(0, 2);
    tMatrix(2, 1) = (*this)(1, 2);
    tMatrix(2, 2) = (*this)(2, 2);
    tMatrix(2, 3) = (*this)(3, 2);

    //Fourth row
    tMatrix(3, 0) = (*this)(0, 3);
    tMatrix(3, 1) = (*this)(1, 3);
    tMatrix(3, 2) = (*this)(2, 3);
    tMatrix(3, 3) = (*this)(3, 3);
    return tMatrix;
}

//Taken from Mesa implementation of GLU library
Matrix4 Matrix4::Inverse() {
    Matrix4 inverseMat;

    float det;
    int i, j;

    inverseMat(0, 0) = mMatrix[5] * mMatrix[10] * mMatrix[15] -
        mMatrix[5] * mMatrix[11] * mMatrix[14] -
        mMatrix[9] * mMatrix[6] * mMatrix[15] +
        mMatrix[9] * mMatrix[7] * mMatrix[14] +
        mMatrix[13] * mMatrix[6] * mMatrix[11] -
        mMatrix[13] * mMatrix[7] * mMatrix[10];

    inverseMat(1, 0) = -mMatrix[4] * mMatrix[10] * mMatrix[15] +
        mMatrix[4] * mMatrix[11] * mMatrix[14] +
        mMatrix[8] * mMatrix[6] * mMatrix[15] -
        mMatrix[8] * mMatrix[7] * mMatrix[14] -
        mMatrix[12] * mMatrix[6] * mMatrix[11] +
        mMatrix[12] * mMatrix[7] * mMatrix[10];

    inverseMat(2, 0) = mMatrix[4] * mMatrix[9] * mMatrix[15] -
        mMatrix[4] * mMatrix[11] * mMatrix[13] -
        mMatrix[8] * mMatrix[5] * mMatrix[15] +
        mMatrix[8] * mMatrix[7] * mMatrix[13] +
        mMatrix[12] * mMatrix[5] * mMatrix[11] -
        mMatrix[12] * mMatrix[7] * mMatrix[9];

    inverseMat(3, 0) = -mMatrix[4] * mMatrix[9] * mMatrix[14] +
        mMatrix[4] * mMatrix[10] * mMatrix[13] +
        mMatrix[8] * mMatrix[5] * mMatrix[14] -
        mMatrix[8] * mMatrix[6] * mMatrix[13] -
        mMatrix[12] * mMatrix[5] * mMatrix[10] +
        mMatrix[12] * mMatrix[6] * mMatrix[9];

    inverseMat(0, 1) = -mMatrix[1] * mMatrix[10] * mMatrix[15] +
        mMatrix[1] * mMatrix[11] * mMatrix[14] +
        mMatrix[9] * mMatrix[2] * mMatrix[15] -
        mMatrix[9] * mMatrix[3] * mMatrix[14] -
        mMatrix[13] * mMatrix[2] * mMatrix[11] +
        mMatrix[13] * mMatrix[3] * mMatrix[10];

    inverseMat(1, 1) = mMatrix[0] * mMatrix[10] * mMatrix[15] -
        mMatrix[0] * mMatrix[11] * mMatrix[14] -
        mMatrix[8] * mMatrix[2] * mMatrix[15] +
        mMatrix[8] * mMatrix[3] * mMatrix[14] +
        mMatrix[12] * mMatrix[2] * mMatrix[11] -
        mMatrix[12] * mMatrix[3] * mMatrix[10];

    inverseMat(2, 1) = -mMatrix[0] * mMatrix[9] * mMatrix[15] +
        mMatrix[0] * mMatrix[11] * mMatrix[13] +
        mMatrix[8] * mMatrix[1] * mMatrix[15] -
        mMatrix[8] * mMatrix[3] * mMatrix[13] -
        mMatrix[12] * mMatrix[1] * mMatrix[11] +
        mMatrix[12] * mMatrix[3] * mMatrix[9];

    inverseMat(3, 1) = mMatrix[0] * mMatrix[9] * mMatrix[14] -
        mMatrix[0] * mMatrix[10] * mMatrix[13] -
        mMatrix[8] * mMatrix[1] * mMatrix[14] +
        mMatrix[8] * mMatrix[2] * mMatrix[13] +
        mMatrix[12] * mMatrix[1] * mMatrix[10] -
        mMatrix[12] * mMatrix[2] * mMatrix[9];

    inverseMat(0, 2) = mMatrix[1] * mMatrix[6] * mMatrix[15] -
        mMatrix[1] * mMatrix[7] * mMatrix[14] -
        mMatrix[5] * mMatrix[2] * mMatrix[15] +
        mMatrix[5] * mMatrix[3] * mMatrix[14] +
        mMatrix[13] * mMatrix[2] * mMatrix[7] -
        mMatrix[13] * mMatrix[3] * mMatrix[6];

    inverseMat(1, 2) = -mMatrix[0] * mMatrix[6] * mMatrix[15] +
        mMatrix[0] * mMatrix[7] * mMatrix[14] +
        mMatrix[4] * mMatrix[2] * mMatrix[15] -
        mMatrix[4] * mMatrix[3] * mMatrix[14] -
        mMatrix[12] * mMatrix[2] * mMatrix[7] +
        mMatrix[12] * mMatrix[3] * mMatrix[6];

    inverseMat(2, 2) = mMatrix[0] * mMatrix[5] * mMatrix[15] -
        mMatrix[0] * mMatrix[7] * mMatrix[13] -
        mMatrix[4] * mMatrix[1] * mMatrix[15] +
        mMatrix[4] * mMatrix[3] * mMatrix[13] +
        mMatrix[12] * mMatrix[1] * mMatrix[7] -
        mMatrix[12] * mMatrix[3] * mMatrix[5];

    inverseMat(3, 2) = -mMatrix[0] * mMatrix[5] * mMatrix[14] +
        mMatrix[0] * mMatrix[6] * mMatrix[13] +
        mMatrix[4] * mMatrix[1] * mMatrix[14] -
        mMatrix[4] * mMatrix[2] * mMatrix[13] -
        mMatrix[12] * mMatrix[1] * mMatrix[6] +
        mMatrix[12] * mMatrix[2] * mMatrix[5];

    inverseMat(0, 3) = -mMatrix[1] * mMatrix[6] * mMatrix[11] +
        mMatrix[1] * mMatrix[7] * mMatrix[10] +
        mMatrix[5] * mMatrix[2] * mMatrix[11] -
        mMatrix[5] * mMatrix[3] * mMatrix[10] -
        mMatrix[9] * mMatrix[2] * mMatrix[7] +
        mMatrix[9] * mMatrix[3] * mMatrix[6];

    inverseMat(1, 3) = mMatrix[0] * mMatrix[6] * mMatrix[11] -
        mMatrix[0] * mMatrix[7] * mMatrix[10] -
        mMatrix[4] * mMatrix[2] * mMatrix[11] +
        mMatrix[4] * mMatrix[3] * mMatrix[10] +
        mMatrix[8] * mMatrix[2] * mMatrix[7] -
        mMatrix[8] * mMatrix[3] * mMatrix[6];

    inverseMat(2, 3) = -mMatrix[0] * mMatrix[5] * mMatrix[11] +
        mMatrix[0] * mMatrix[7] * mMatrix[9] +
        mMatrix[4] * mMatrix[1] * mMatrix[11] -
        mMatrix[4] * mMatrix[3] * mMatrix[9] -
        mMatrix[8] * mMatrix[1] * mMatrix[7] +
        mMatrix[8] * mMatrix[3] * mMatrix[5];

    inverseMat(3, 3) = mMatrix[0] * mMatrix[5] * mMatrix[10] -
        mMatrix[0] * mMatrix[6] * mMatrix[9] -
        mMatrix[4] * mMatrix[1] * mMatrix[10] +
        mMatrix[4] * mMatrix[2] * mMatrix[9] +
        mMatrix[8] * mMatrix[1] * mMatrix[6] -
        mMatrix[8] * mMatrix[2] * mMatrix[5];

    det = mMatrix[0] * inverseMat(0, 0) + mMatrix[1] * inverseMat(1, 0) + mMatrix[2] * inverseMat(2, 0) + mMatrix[3] * inverseMat(3, 0);

    det = 1.0 / det;

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            inverseMat(i, j) = inverseMat(i, j) * det;
        }
    }

    return inverseMat;
}

Matrix4 Matrix4::TranslateMatrix(float x, float y, float z)
{
    Matrix4 temp = UnitMatrix4();
    temp(0, 3) = x;
    temp(1, 3) = y;
    temp(2, 3) = z;
    return temp;
}

Matrix4 Matrix4::ScaleMatrix(float x, float y, float z)
{
    Matrix4 temp = UnitMatrix4();
    temp(0, 0) = x;
    temp(1, 1) = y;
    temp(2, 2) = z;
    return temp;
}

//分别计算出绕X Y Z轴选择的矩阵，然后按Z Y X的顺序矩阵相乘计算出旋转矩阵
//参数x y z为分别绕X Y Z轴选择的角度
Matrix4 Matrix4::RotateMatrix(float x, float y, float z)
{
    x = M_PI * x / 180;
    y = M_PI * y / 180;
    z = M_PI * z / 180;
    Matrix4 temp = UnitMatrix4();
    float cosx = cos(x);
    float sinx = sin(x);
    float cosy = cos(y);
    float siny = sin(y);
    float cosz = cos(z);
    float sinz= sin(z);

    //First row
    temp(0, 0) = cosy * cosz;
    temp(0, 1) = -cosx * sinz + sinx * siny * cosz;
    temp(0, 2) = sinx * sinz + cosx * siny * cosz;

    //Second row
    temp(1, 0) = cosy * sinz;
    temp(1, 1) = cosx * cosz + sinx * siny * sinz;
    temp(1, 2) = -sinx * cosz + cosx * siny * sinz;

    //Third row
    temp(2, 0) = -siny;
    temp(2, 1) = sinx * cosy;
    temp(2, 2) = cosx * cosy;

    //Fourth row
    temp(3, 3) = 1;
    return temp;
}

Matrix4 Matrix4::ModelMatrix(Transform t)
{
    Matrix4 scale_mat = ScaleMatrix(t.scale.x, t.scale.y, t.scale.z);
    Matrix4 rotate_mat = RotateMatrix(t.rotation.x, t.rotation.y, t.rotation.z);
    Matrix4 translate_mat = TranslateMatrix(t.position.x, t.position.y, t.position.z);
    Matrix4 temp;
    temp = rotate_mat * scale_mat;
    return translate_mat * temp;
}

Matrix4 Matrix4::ViewMatrix(Vector3f& position, Vector3f& target, Vector3f& uparg) {
    //Gram–Schmidt process
    Vector3f forward = (target - position).normalized();
    Vector3f side = (uparg.Cross(forward)).normalized();
    Vector3f up = forward.Cross(side);

    Matrix4 worldToCam;
    //First row
    worldToCam(0, 0) = side.x;
    worldToCam(0, 1) = side.y;
    worldToCam(0, 2) = side.z;
    worldToCam(0, 3) = -side.Dot(position);

    //Second row
    worldToCam(1, 0) = up.x;
    worldToCam(1, 1) = up.y;
    worldToCam(1, 2) = up.z;
    worldToCam(1, 3) = -up.Dot(position);

    //Third row
    worldToCam(2, 0) = forward.x;
    worldToCam(2, 1) = forward.y;
    worldToCam(2, 2) = forward.z;
    worldToCam(2, 3) = -forward.Dot(position);

    //Fourth row
    worldToCam(3, 3) = 1;

    return worldToCam;
}

Matrix4 Matrix4::ProjectionMatrix(float fov, float aspect, float near, float far, float r, float t) {
    Matrix4 projectionMat;
    float fax = 1.0f / (float)tan(fov * 0.5f);
    projectionMat(0, 0) = (float)(fax / aspect);
    projectionMat(1, 1) = (float)(fax);
    projectionMat(2, 2) = far / (far - near);
    projectionMat(2, 3) = -near * far / (far - near);
    projectionMat(3, 2) = 1;

    /*
    projectionMat(0, 0) = near;
    projectionMat(1, 1) = near;
    projectionMat(2, 2) = far / (far - near);
    projectionMat(2, 3) = -near * far / (far - near);
    projectionMat(3, 2) = 1;
    */
    
    return projectionMat;
}