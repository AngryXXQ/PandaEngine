#include "RenderManager.h"

RenderManager* RenderManager::m_RenderManager = NULL;

RenderManager::RenderManager()
{
	m_MainCamera = NULL;
	width = 1000;
	height = 800;
	viewportMatrix = viewportMatrix.UnitMatrix4();
	frameBuffer.ResizeBuffer(width, height);
}

RenderManager::~RenderManager() 
{

}

void RenderManager::ChangeCameraPos(Vector3f offset)
{
	if (m_MainCamera)
	{
		m_MainCamera->position += offset;
	}
}

void RenderManager::RotateModels(Vector3f rot)
{
	std::queue<Model*> render_queue = model_queue;
	for (int i = 0; i < render_queue.size(); ++i)
	{
		Model* m = render_queue.front();
		if (m)
		{
			m->modelTransform.rotation += rot;
		}
		render_queue.pop();
	}
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
	glLineWidth(0.1);
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

void RenderManager::DrawPoint(Vector3f p)
{
	glColor4ub(255, 0, 0, 255);
	//glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}

void RenderManager::AddModel(const char* model_name,Transform t)
{
	Model* mod = new Model();
	mod->LoadModel(model_name);
	mod->SetModelTransform(t);
	model_queue.push(mod);
}

void RenderManager::Init(HWND hwnd,float w, float h)
{
	width = w;
	height = h;
	initRenderManager(hwnd);
	m_MainCamera = new Camera();
	/*
	width = 1;
	height = 1;
	*/
	viewportMatrix(0, 0) = width / 2;
	viewportMatrix(0, 3) = width / 2;
	viewportMatrix(1, 1) = height / 2;
	viewportMatrix(1, 3) = height / 2;
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
	Color pcolor(255, 255, 255, 255);
	Color tcolor(125, 125, 125, 255);
	frameBuffer.ClearBuffer(tcolor);
	std::queue<Model*> render_queue = model_queue;
	for (int i = 0; i < render_queue.size(); ++i)
	{
		Model* m = render_queue.front();
		if (m)
		{
			Matrix4 modelMatrix = m->GetModelTransform();
			Matrix4 tM = m_MainCamera->viewMatrix * modelMatrix;
			tM = m_MainCamera->projectionMatrix * tM;
			tM = viewportMatrix * tM;
			for (int j = 0; j < m->vertexVector.size(); ++j)
			{
				std::vector<Vector3f> vlist = m->vertexVector[j];
				Vector3f v0 = tM * vlist[0];
				Vector3f v1 = tM * vlist[1];
				Vector3f v2 = tM * vlist[2];
				DrawLine(v0, v1, pcolor);
				DrawLine(v1, v2, pcolor);
				DrawLine(v2, v0, pcolor);
			}
		}
		render_queue.pop();
	}
	glDrawPixels(1000, 800, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer.buffer.data());
	glFlush();
	SwapBuffers(hdc);
}


// ªÊ÷∆œﬂ∂Œ
void RenderManager::DrawLine(Vector3f v1,Vector3f v2, Color color) {
	int x, y, rem = 0;
	if (v1.x == v2.x && v1.y == v2.y) {
		frameBuffer.WriteBuffer(v1.x, v1.y, color);
	}
	else if (v1.x == v2.x) {
		int inc = (v1.y <= v2.y) ? 1 : -1;
		for (y = v1.y; y != v2.y; y += inc)
		{
			frameBuffer.WriteBuffer(v1.x, y, color);
		}
		frameBuffer.WriteBuffer(v2.x, v2.y, color);
	}
	else if (v1.y == v2.y) {
		int inc = (v1.x <= v2.x) ? 1 : -1;
		for (x = v1.x; x != v2.x; x += inc)
		{
			frameBuffer.WriteBuffer(x, v1.y, color);
		}
		frameBuffer.WriteBuffer(v2.x, v2.y, color);
	}
	else {
		int dx = (v1.x < v2.x) ? v2.x - v1.x : v1.x - v2.x;
		int dy = (v1.y < v2.y) ? v2.y - v1.y : v1.y - v2.y;
		if (dx >= dy) {
			if (v2.x < v1.x) x = v1.x, y = v1.y, v1.x = v2.x, v1.y = v2.y, v2.x = x, v2.y = y;
			for (x = v1.x, y = v1.y; x <= v2.x; x++) {
				frameBuffer.WriteBuffer(x, y, color);
				rem += dy;
				if (rem >= dx) {
					rem -= dx;
					y += (v2.y >= v1.y) ? 1 : -1;
					frameBuffer.WriteBuffer(x, y, color);
				}
			}
			frameBuffer.WriteBuffer(v2.x, v2.y, color);
		}
		else {
			if (v2.y < v1.y) x = v1.x, y = v1.y, v1.x = v2.x, v1.y = v2.y, v2.x = x, v2.y = y;
			for (x = v1.x, y = v1.y; y <= v2.y; y++) {
				frameBuffer.WriteBuffer(x, y, color);
				rem += dx;
				if (rem >= dy) {
					rem -= dy;
					x += (v2.x >= v1.x) ? 1 : -1;
					frameBuffer.WriteBuffer(x, y, color);
				}
			}
			frameBuffer.WriteBuffer(v2.x, v2.y, color);
		}
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