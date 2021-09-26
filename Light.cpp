#include "Light.h"

Light::Light()
{
	pos = Vector3f(0,0,0);
	lightType = LightType::DIRECTION_LIGHT;
	lightIntensity = 1;
}

Light::~Light()
{

}

Light::Light(Vector3f p, LightType type)
{
	pos = p;
	lightType = type;
	lightIntensity = 1;
}

