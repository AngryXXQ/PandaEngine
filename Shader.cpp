#include "Shader.h"

Shader::Shader()
{
	M.UnitMatrix4();
	V.UnitMatrix4();
	P.UnitMatrix4();
	MV.UnitMatrix4();
	MVP.UnitMatrix4();
	tex = new Texture();
	lightDir = Vector3f(0, 0, 0);
	viewDir = Vector3f(0, 0, 0);
}

Shader::~Shader()
{
	delete tex;
}

Vertex Shader::VertexShader(Vertex v)
{
	v.vertex = MVP * v.vertex;
	v.normal = MVP * v.normal;
	return v;
}

Color Shader::FragmentShader(Vertex v)
{
	if (light)
	{
		lightDir = light->pos - v.vertex;
		lightDir = lightDir.normalized();
	}
	if (mainCamera)
	{
		viewDir = mainCamera->position - v.vertex;
		viewDir = viewDir.normalized();
	}
	float r = lightDir.length();

	//calculate diffuse
	float vdl = v.normal.Dot(lightDir);
	if (vdl < 0)
	{
		vdl = 0;
	}
	//float diffuse = (light->lightIntensity / (r * r)) * vdl;
	Color diffuse = light->lightColor * vdl;

	//calculate specular
	/*
	Vector3f h = (lightDir + viewDir)* (1 / (lightDir + viewDir).length());
	float vdh = v.normal.Dot(h);
	if (vdh < 0)
	{
		vdh = 0;
	}
	float specular = (light->lightIntensity / (r * r)) * vdh;
	*/

	Color color(255, 255, 255, 255);
	if (tex->data)
	{
		Vector3f c3 = tex->Sample2D(v.uv[0]);
		color.r = c3.x;
		color.g = c3.y;
		color.b = c3.z;
		color.a = c3.w;
		color = color + diffuse;
	}
	return color;
}

bool Shader::SetTexture(std::string filepath)
{
	tex->LoadTexture(filepath);
	return true;
}
