#include "Model.h"

Model::Model()
{
	vertexVector.clear();
}

Model::~Model()
{

}

bool Model::LoadModel(const char* modelName)
{
	if (ModelImportor::getInstance()->importModel(modelName))
	{
		vertexVector = ModelImportor::getInstance()->vertexVector;
	}
	return true;
}