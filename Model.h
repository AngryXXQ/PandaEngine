#pragma once
#include "ModelImportor.h"
#include "IncludeManager.h"

class Model
{
public:
	Model();
	~Model();

	bool LoadModel(const char* modelName);
public:

	std::vector<std::vector<Vector3f>> vertexVector;
};