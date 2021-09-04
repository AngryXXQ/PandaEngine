#include "ModelImportor.h"

ModelImportor* ModelImportor::m_ModelImportor = NULL;

ModelImportor::ModelImportor()
{
	numTabs = 0;
    vertexVector.clear();
}

ModelImportor::~ModelImportor()
{

}

/**
     * Print the required number of tabs.
     */
void ModelImportor::PrintTabs() {
    for (int i = 0; i < numTabs; i++)
        printf("\t");
}

/**
 * Return a string-based representation based on the attribute type.
 */
FbxString ModelImportor::GetAttributeTypeName(FbxNodeAttribute::EType type) {
    switch (type) {
    case FbxNodeAttribute::eUnknown: return "unidentified";
    case FbxNodeAttribute::eNull: return "null";
    case FbxNodeAttribute::eMarker: return "marker";
    case FbxNodeAttribute::eSkeleton: return "skeleton";
    case FbxNodeAttribute::eMesh: return "mesh";
    case FbxNodeAttribute::eNurbs: return "nurbs";
    case FbxNodeAttribute::ePatch: return "patch";
    case FbxNodeAttribute::eCamera: return "camera";
    case FbxNodeAttribute::eCameraStereo: return "stereo";
    case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
    case FbxNodeAttribute::eLight: return "light";
    case FbxNodeAttribute::eOpticalReference: return "optical reference";
    case FbxNodeAttribute::eOpticalMarker: return "marker";
    case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
    case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
    case FbxNodeAttribute::eBoundary: return "boundary";
    case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
    case FbxNodeAttribute::eShape: return "shape";
    case FbxNodeAttribute::eLODGroup: return "lodgroup";
    case FbxNodeAttribute::eSubDiv: return "subdiv";
    default: return "unknown";
    }
}

/**
 * Print an attribute.
 */
void ModelImportor::PrintAttribute(FbxNodeAttribute* pAttribute) {
    if (!pAttribute) return;

    FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
    FbxString attrName = pAttribute->GetName();
    PrintTabs();
    // Note: to retrieve the character array of a FbxString, use its Buffer() method.
    printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
}

/**
 * Print a node, its attributes, and all its children recursively.
 */
void ModelImportor::PrintNode(FbxNode* pNode) {
    PrintTabs();
    const char* nodeName = pNode->GetName();
    FbxDouble3 translation = pNode->LclTranslation.Get();
    FbxDouble3 rotation = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    // Print the contents of the node.
    printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
        nodeName,
        translation[0], translation[1], translation[2],
        rotation[0], rotation[1], rotation[2],
        scaling[0], scaling[1], scaling[2]
    );
    numTabs++;

    // Print the node's attributes.
    /*
    for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
        PrintAttribute(pNode->GetNodeAttributeByIndex(i));
    */

    Vector3f vertex[3];
    FbxMesh* pMesh = pNode->GetMesh();
    if (pMesh)
    {
        int pcount = pMesh->GetPolygonCount();
        int vertexCounter = 0;
        for (int i = 0; i < pcount; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                int ctrlPointIndex = pMesh->GetPolygonVertex(i, j);
                // Read the vertex  
                ReadVertex(pMesh, ctrlPointIndex, &vertex[j]);

                vertexCounter++;
            }
            std::vector<Vector3f> temp;
            temp.clear();
            for (int k = 0; k < 3; ++k)
            {
                temp.push_back(vertex[k]);
            }
            if (temp.size() > 0)
            {
                vertexVector.push_back(temp);
            }
        }
    }
    
    // Recursively print the children.
    for (int j = 0; j < pNode->GetChildCount(); j++)
        PrintNode(pNode->GetChild(j));

    numTabs--;
    PrintTabs();
    printf("</node>\n");
}

void ModelImportor::ReadVertex(FbxMesh* pMesh, int ctrlPointIndex, Vector3f* pVertex)
{
    FbxVector4* pCtrlPoint = pMesh->GetControlPoints();
    pVertex->x = pCtrlPoint[ctrlPointIndex][0];
    pVertex->y = pCtrlPoint[ctrlPointIndex][1];
    pVertex->z = pCtrlPoint[ctrlPointIndex][2];
}

/**
 * Main function - loads the hard-coded fbx file,
 * and prints its contents in an xml format to stdout.
 */
int ModelImportor::importModel(const char* lFilename) {
    vertexVector.clear();
    // Initialize the SDK manager. This object handles all our memory management.
    FbxManager* lSdkManager = FbxManager::Create();

    // Create the IO settings object.
    FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Load plug-ins from the executable directory  
    FbxString lExtension = "dll";
    FbxString lPath = FbxGetApplicationDirectory();
    lSdkManager->LoadPluginsDirectory(lPath.Buffer(), lExtension.Buffer());

    // Create an importer using the SDK manager.
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");

    // Use the first argument as the filename for the importer.
    if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings())) {
        printf("Call to FbxImporter::Initialize() failed.\n");
        const char* error = lImporter->GetStatus().GetErrorString();
        printf("Error returned: %s\n\n", error);
        return 0;
    }

    // Create a new scene so that it can be populated by the imported file.
    FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");

    // Import the contents of the file into the scene.
    lImporter->Import(lScene);

    // The file is imported; so get rid of the importer.
    lImporter->Destroy();

    // Print the nodes of the scene and their attributes recursively.
    // Note that we are not printing the root node because it should
    // not contain any attributes.
    FbxNode* lRootNode = lScene->GetRootNode();
    if (lRootNode) {
        for (int i = 0; i < lRootNode->GetChildCount(); i++)
            PrintNode(lRootNode->GetChild(i));
    }
    // Destroy the SDK manager and all the other objects it was handling.
    lSdkManager->Destroy();
    return 1;
}