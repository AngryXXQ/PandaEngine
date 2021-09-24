#include "Shader.h"

Shader::Shader()
{
	M.UnitMatrix4();
	V.UnitMatrix4();
	P.UnitMatrix4();
	MV.UnitMatrix4();
	MVP.UnitMatrix4();
	tex = new Texture();
}

Shader::~Shader()
{
	delete tex;
}

Vertex Shader::VertexShader(Vertex v)
{
	v.vertex = MVP * v.vertex;
	return v;
}

Color Shader::FragmentShader(Vertex v)
{
	Color color(255, 255, 255, 255);
	if (tex->data)
	{
		Vector3f c3 = tex->Sample2D(v.uv[0]);
		color.r = c3.x;
		color.g = c3.y;
		color.b = c3.z;
		color.a = c3.w;
	}
	return color;
}

bool Shader::SetTexture(std::string filepath)
{
	tex->LoadTexture(filepath);
	return true;
}