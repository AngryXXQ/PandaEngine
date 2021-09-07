#include "Model.h"

Model::Model()
{
	vertexVector.clear();
	modelTransform.position = Vector3f(0,0,0);
	modelTransform.rotation = Vector3f(0, 0, 0);
	modelTransform.scale = Vector3f(1, 1, 1);
	modelMatrix = modelMatrix.ModelMatrix(modelTransform);
}

Model::~Model()
{

}

void Model::SetModelTransform(Transform t)
{
	modelTransform = t;
	modelMatrix = modelMatrix.ModelMatrix(modelTransform);
}

Matrix4 Model::GetModelTransform()
{
	modelMatrix = modelMatrix.ModelMatrix(modelTransform);
	return modelMatrix;
}

bool Model::LoadModel(const char* modelName)
{
	if (ModelImportor::getInstance()->importModel(modelName))
	{
		vertexVector = ModelImportor::getInstance()->vertexVector;
	}
	return true;
}