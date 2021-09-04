#include "Model.h"

Model::Model()
{

}

Model::~Model()
{

}

bool Model::LoadModel(char* modelName)
{
	ModelImportor::getInstance()->importModel(modelName);
	return true;
}