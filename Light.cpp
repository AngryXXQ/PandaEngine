#include "Light.h"

Light::Light()
{
	pos = Vector3f(0,0,0);
	lightType = LightType::DIRECTION_LIGHT;
	lightIntensity = 100;
	lightColor = Color(1, 1, 1, 1);
}

Light::~Light()
{

}

Light::Light(Vector3f p, LightType type, Color lc)
{
	pos = p;
	lightType = type;
	lightIntensity = 1;
	lightColor = lc;
}

