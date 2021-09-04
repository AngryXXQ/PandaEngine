#pragma once
#include "IncludeManager.h"

class Camera 
{
public:
	Camera();
	~Camera();

	Vector3f position;
	Matrix4 viewMatrix;
	Matrix4 projectionMatrix;

	void Update();

private:
	Vector3f target;
	Vector3f up;

	float fov;
	float aspect;
	float znear;
	float zfar;
};