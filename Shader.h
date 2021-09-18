#pragma once
#include "IncludeManager.h"

class Shader
{
public:
	Shader();
	~Shader();

	Vertex VertexShader(Vertex v);

public:
	Matrix4 M;
	Matrix4 V;
	Matrix4 P;
	Matrix4 MVP;
};

