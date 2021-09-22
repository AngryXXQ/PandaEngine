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

	void SetAspect(float w,float h);
	void Update();
	Vector3f dir;
private:
	Vector3f target;
	Vector3f up;

	float fov;
	float aspect;
	float znear;
	float zfar;
	float width;
	float height;
};