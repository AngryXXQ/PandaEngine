#pragma once
#include "IncludeManager.h"
#include "Camera.h"
#include "Model.h"
#include <queue>

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	static RenderManager* getInstance()
	{
		if (m_RenderManager == NULL)
		{
			m_RenderManager = new RenderManager();
		}
		return m_RenderManager;
	}

	void Init();
	void Update();
	void Destory();
	void AddModel(char* model_name);
private:
	static RenderManager* m_RenderManager;
	Camera* m_MainCamera;
	std::queue<Model> model_queue;
};