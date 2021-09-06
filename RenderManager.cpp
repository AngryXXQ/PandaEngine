#include "RenderManager.h"

RenderManager* RenderManager::m_RenderManager = NULL;

RenderManager::RenderManager()
{
	m_MainCamera = NULL;
	width = 1000;
	height = 800;
	viewportMatrix = viewportMatrix.UnitMatrix4();
}

RenderManager::~RenderManager() 
{

}



void RenderManager::initRenderManager(HWND hwnd) {
	HDC dc = GetDC(hwnd);
	hdc = dc;
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);
}

void RenderManager::DrawLine(Vector3f p1, Vector3f p2)
{
	glColor4ub(0, 0, 0, 255);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

void RenderManager::DrawPoint(Vector3f p)
{
	glColor4ub(255, 0, 0, 255);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}

void RenderManager::AddModel(const char* model_name)
{
	Model* mod = new Model();
	mod->LoadModel(model_name);
	model_queue.push(mod);
}

void RenderManager::Init(HWND hwnd,float w, float h)
{
	initRenderManager(hwnd);
	m_MainCamera = new Camera();
	width = w;
	height = h;

	viewportMatrix(0, 0) = w / 2;
	viewportMatrix(0, 3) = w / 2;
	viewportMatrix(1, 1) = h / 2;
	viewportMatrix(1, 3) = h / 2;
}

void RenderManager::Update()
{
	if (m_MainCamera != NULL)
	{
		m_MainCamera->Update();
	}
	else
	{
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	Matrix4 tM = m_MainCamera->projectionMatrix * m_MainCamera->viewMatrix;
	tM = viewportMatrix * tM;
	//DrawPoint(Vector3f(0.1,0.2,0.1));
	std::queue<Model*> render_queue = model_queue;
	for (int i = 0; i < render_queue.size(); ++i)
	{
		Model* m = render_queue.front();
		if (m)
		{
			for (int j = 0; j < m->vertexVector.size(); ++j)
			{
				std::vector<Vector3f> vlist = m->vertexVector[j];
				Vector3f v0 = tM * vlist[0];
				Vector3f v1 = tM * vlist[1];
				Vector3f v2 = tM * vlist[2];
				DrawPoint(v0);
				DrawPoint(v1);
				DrawPoint(v2);
				/*
				DrawLine(v0, v1);
				DrawLine(v1, v2);
				DrawLine(v2, v1);
				*/
			}
		}
		render_queue.pop();
	}
	SwapBuffers(hdc);
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