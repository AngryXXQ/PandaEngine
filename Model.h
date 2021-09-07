#pragma once
#include "ModelImportor.h"
#include "IncludeManager.h"

class Model
{
public:
	Model();
	~Model();

	bool LoadModel(const char* modelName);
	void SetModelTransform(Transform t);
	Matrix4 GetModelTransform();
public:
	Transform modelTransform;
	Matrix4 modelMatrix;
	std::vector<std::vector<Vector3f>> vertexVector;
};