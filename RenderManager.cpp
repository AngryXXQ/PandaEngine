#include "RenderManager.h"

RenderManager* RenderManager::m_RenderManager = NULL;

RenderManager::RenderManager()
{
	m_MainCamera = NULL;
}

RenderManager::~RenderManager() 
{

}

void RenderManager::AddModel(const char* model_name)
{
	Model* mod = new Model();
	mod->LoadModel(model_name);
	model_queue.push(mod);
}

void RenderManager::Init()
{
	m_MainCamera = new Camera();
}

void RenderManager::Update()
{
	if (m_MainCamera != NULL)
	{
		m_MainCamera->Update();
	}
}

void RenderManager::Destory()
{
	if (m_MainCamera != NULL)
	{
		delete m_MainCamera;
	}

	for (int i = 0; i < model_queue.size(); ++i)
	{
		Model* m = model_queue.front();
		delete m;
		model_queue.pop();
	}
}