#pragma once
#include <fbxsdk.h>
#include "IncludeManager.h"

using namespace fbxsdk;

class ModelImportor
{
public:
	ModelImportor();
	~ModelImportor();

	static ModelImportor* getInstance()
	{
		if (m_ModelImportor == NULL)
		{
			m_ModelImportor = new ModelImportor();
		}
		return m_ModelImportor;
	}

	void PrintNode(FbxNode* pNode, std::vector<std::vector<Vertex>>& vertexDatas);
	int importModel(const char* lFilename,std::vector<std::vector<Vertex>>& vertexDatas);
	void PrintAttribute(FbxNodeAttribute* pAttribute);
	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	void PrintTabs();

	void ReadVertex(FbxMesh* pMesh, int ctrlPointIndex, Vector3f* pVertex);
	void ReadColor(FbxMesh* pMesh, int ctrlPointIndex, int vertexCounter, Vector3f* pColor);
	void ReadUV(FbxMesh* pMesh, int ctrlPointIndex, int textureUVIndex, int uvLayer, Vector3f* pUV);
	void ReadNormal(FbxMesh* pMesh, int ctrlPointIndex, int vertexCounter, Vector3f* pNormal);
	void ReadTangent(FbxMesh* pMesh, int ctrlPointIndex, int vertecCounter, Vector3f* pTangent);
private:
	static ModelImportor* m_ModelImportor;
	int numTabs;
};
