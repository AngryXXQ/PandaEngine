#include "Camera.h"

Camera::Camera()
{
	position = Vector3f(0, 0, 0);
	target = Vector3f(0,0,16);
	up = Vector3f(0,1,0);
	dir = (target - position).normalized();

	fov = M_PI / 3;
	aspect = 0.5;
	znear = 0.3;
	zfar = 1000;
	width = 1;
	height = 1;
}

Camera::~Camera()
{

}

void Camera::SetAspect(float w, float h)
{
	width = w;
	height = h;
	aspect = w/h;
}

void Camera::Update()
{
	dir = (target - position).normalized();
	viewMatrix = viewMatrix.ViewMatrix(position, target, up);
	projectionMatrix = projectionMatrix.ProjectionMatrix(fov, aspect,znear,zfar,width/2,height/2);
}