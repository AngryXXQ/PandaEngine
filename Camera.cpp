#include "Camera.h"

Camera::Camera()
{
	position = Vector3f(0, 0, 15);
	target = Vector3f(0,0,1);
	up = Vector3f(0,1,0);

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
	viewMatrix = viewMatrix.ViewMatrix(position, target, up);
	projectionMatrix = projectionMatrix.ProjectionMatrix(fov, aspect,znear,zfar);
}