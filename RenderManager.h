#pragma once
#include "IncludeManager.h"
#include "Camera.h"
#include "Model.h"
#include <queue>
#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


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

	void DrawLine(Vector3f p1,Vector3f p2);
	void DrawPoint(Vector3f p);

	void Init(HWND hwnd, float w, float h);
	void Update();
	void Destory();
	void AddModel(const char* model_name, Transform t);
	void initRenderManager(HWND hwnd);
	void ChangeCameraPos(Vector3f offset);
	void RotateModels(Vector3f rot);
private:
	static RenderManager* m_RenderManager;
	Camera* m_MainCamera;
	std::queue<Model*> model_queue;
	HDC hdc;
	float width;
	float height;
	Matrix4 viewportMatrix;
};