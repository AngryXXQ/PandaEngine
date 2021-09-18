#include "Camera.h"

Camera::Camera()
{
	position = Vector3f(0, 0, 0);
	target = Vector3f(0,0,16);
	up = Vector3f(0,1,0);
	dir = (target - position).normalized();

	fov = 60;
	aspect = 0.5;
	znear = 0.3;
	zfar = 1000;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	dir = (target - position).normalized();
	viewMatrix = viewMatrix.ViewMatrix(position, target, up);
	projectionMatrix = projectionMatrix.ProjectionMatrix(fov, aspect,znear,zfar);
}