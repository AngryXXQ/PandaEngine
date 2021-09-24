#pragma once
#include "IncludeManager.h"
#include "Texture.h"

class Shader
{
public:
	Shader();
	~Shader();

	Vertex VertexShader(Vertex v);

	Color FragmentShader(Vertex v);

	bool SetTexture(std::string filename);
public:
	Matrix4 M;
	Matrix4 V;
	Matrix4 P;
	Matrix4 MV;
	Matrix4 MVP;
	Texture* tex;
};

