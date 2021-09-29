#pragma once
#include "IncludeManager.h"

class Light
{
public:
	Light();
	~Light();

	Light(Vector3f p, LightType type, Color lc);
public:
	Vector3f pos;
	Color lightColor;
	LightType lightType;
	float lightIntensity;
};

