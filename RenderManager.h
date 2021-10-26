#pragma once
#include "IncludeManager.h"
#include "Buffer.h"
#include "Camera.h"
#include "Model.h"
#include <queue>
#include <stdio.h>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Shader.h"
#include "Light.h"

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
	void AddModel(const char* model_name, const char* tex_path, Transform t);
	void initRenderManager(HWND hwnd);
	void ChangeCameraPos(Vector3f offset);
	void IncreaseLightIntensity();
	void RotateModels(Vector3f rot);
	bool FaceCulling(Vector3f v0, Vector3f v1, Vector3f v2);//ÃæÌÞ³ý

	void DrawLine(Vertex v1, Vertex v2, Color color);
	void DrawTriangle(Vertex v0, Vertex v1, Vertex v2, Color color);
	void PerspectiveDivision(Vector3f& v);
	void ViewPortMapping(Vector3f& v);
	void DrawPixel(int x, int y, float z, Color color, bool recomputez = true);

	void ScanLineTriangle(Vertex& v1, Vertex& v2, Vertex& v3);
	void UpTriangle(Vertex& v1, Vertex& v2, Vertex& v3);
	void DownTriangle(Vertex& v1, Vertex& v2, Vertex& v3);
	void ScanLine(Vertex& left, Vertex& right);
	Vector3f LerpA(Vector3f& v1, Vector3f& v2, float factor);
	Vertex lerp(Vertex& v1, Vertex& v2, float& factor);
private:
	static RenderManager* m_RenderManager;
	Camera* m_MainCamera;
	std::queue<Model*> model_queue;
	HDC hdc;
	float width;
	float height;
	Matrix4 viewportMatrix;
	Buffer frameBuffer;
	Shader shader;
	Light* light;
};