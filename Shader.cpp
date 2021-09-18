#include "Shader.h"

Shader::Shader()
{
	M.UnitMatrix4();
	V.UnitMatrix4();
	P.UnitMatrix4();
	MVP.UnitMatrix4();
}

Shader::~Shader()
{

}

Vertex Shader::VertexShader(Vertex v)
{
	v.vertex = MVP * v.vertex;
	return v;
}