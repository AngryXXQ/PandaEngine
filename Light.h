#pragma once
#include "IncludeManager.h"

class Light
{
public:
	Light();
	~Light();

	Light(Vector3f p, LightType type);
public:
	Vector3f pos;
	LightType lightType;
};

