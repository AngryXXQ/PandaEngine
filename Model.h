#pragma once
#include "ModelImportor.h"
#include "IncludeManager.h"

class Model
{
public:
	Model();
	~Model();

	bool LoadModel(std::string modelName, std::string texpath);
	void SetModelTransform(Transform t);
	Matrix4 GetModelTransform();
public:
	Transform modelTransform;
	Matrix4 modelMatrix;
	std::vector<std::vector<Vertex>> vertexVector;
	std::string texturePath;
};