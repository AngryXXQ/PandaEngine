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
	ambient = Color(1,1,1,1);
}

Shader::~Shader()
{
	delete tex;
}

Vertex Shader::VertexShader(Vertex v)
{
	v.vWorldPos = M * v.vertex;
	v.vertex = MVP * v.vertex;
	v.normal = M.Inverse().Transpose() * v.normal;
	v.normal.normalized();
	return v;
}

Color Shader::FragmentShader(Vertex v)
{
	float r = lightDir.length();
	if (light)
	{
		lightDir = light->pos - v.vWorldPos;
		lightDir.normalized();
	}
	if (mainCamera)
	{
		viewDir = mainCamera->position - v.vWorldPos;
		viewDir.normalized();
	}

	//calculate diffuse
	float vdl = v.normal.Dot(lightDir);
	if (vdl < 0)
	{
		vdl = 0;
	}
	//float diffuse = (light->lightIntensity / (r * r)) * vdl;
	Color diffuse = light->lightColor * vdl * light->lightIntensity;

	//calculate specular
	Vector3f h = (lightDir + viewDir).normalized();
	float vdh = v.normal.Dot(h.normalized());
	if (vdh < 0)
	{
		vdh = 0;
	}
	vdh = pow(vdh,15);
	//float specular = (light->lightIntensity / (r * r)) * vdh;
	Color specular = light->lightColor * vdh * light->lightIntensity;

	Color color(1, 1, 1, 1);
	if (tex->data)
	{
		Vector3f c3 = tex->Sample2D(v.uv[0]);
		color.r = c3.x;
		color.g = c3.y;
		color.b = c3.z;
		color.a = c3.w;
	}
	color = ambient*color +specular;
	return color;
}

bool Shader::SetTexture(std::string filepath)
{
	if(filepath != "")
	{
		tex->LoadTexture(filepath);
	}
	return true;
}
