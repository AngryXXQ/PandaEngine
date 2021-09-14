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
	int render_count = render_queue.size();
	for (int i = 0; i < render_count; ++i)
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
	viewportMatrix(0, 0) = width / 2;
	viewportMatrix(0, 3) = width / 2;
	viewportMatrix(1, 1) = height / 2;
	viewportMatrix(1, 3) = height / 2;
}

#define DRAW_LINE 1

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
	int model_count = render_queue.size();
	for (int i = 0; i < model_count; ++i)
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
#ifdef  DRAW_LINE
				DrawLine(v0, v1, pcolor);
				DrawLine(v1, v2, pcolor);
				DrawLine(v2, v0, pcolor);
#endif //  DRAW_LINE

#ifndef DRAW_LINE
				DrawTriangle(v0, v1, v2, pcolor);
#endif // !DRAW_LINE

			}
		}
		render_queue.pop();
	}
	glDrawPixels(1000, 800, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer.buffer.data());
	glFlush();
	SwapBuffers(hdc);
}

// 绘制三角形
void RenderManager::DrawTriangle(Vector3f v0, Vector3f v1, Vector3f v2, Color color) {
	int x, y, rem = 0;
	int x1 = v1.x;
	int y1 = v1.y;
	int x2 = v2.x;
	int y2 = v2.y;
	if (x1 == x2 && y1 == y2) {
		frameBuffer.WriteBuffer(x1, y1, color);
		DrawLine(v0, v1, color);
	}
	else if (x1 == x2) {
		int inc = (y1 <= y2) ? 1 : -1;
		for (y = y1; y != y2; y += inc)
		{
			frameBuffer.WriteBuffer(x1, y, color);
			DrawLine(v0, Vector3f(x1, y, 0), color);
		}
		frameBuffer.WriteBuffer(x2, y2, color);
		DrawLine(v0, Vector3f(x2, y2, 0), color);
	}
	else if (y1 == y2) {
		int inc = (x1 <= x2) ? 1 : -1;
		for (x = x1; x != x2; x += inc)
		{
			frameBuffer.WriteBuffer(x, y1, color);
			DrawLine(v0, Vector3f(x, y1, 0), color);
		}
		frameBuffer.WriteBuffer(x2, y2, color);
		DrawLine(v0, Vector3f(x2, y2, 0), color);
	}
	else {
		int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
		int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
		if (dx >= dy) {
			if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; x <= x2; x++) {
				frameBuffer.WriteBuffer(x, y, color);
				DrawLine(v0, Vector3f(x, y, 0), color);
				rem += dy;
				if (rem >= dx) {
					rem -= dx;
					y += (y2 >= y1) ? 1 : -1;
					frameBuffer.WriteBuffer(x, y, color);
					DrawLine(v0, Vector3f(x, y, 0), color);
				}
			}
			frameBuffer.WriteBuffer(x2, y2, color);
			DrawLine(v0, Vector3f(x2, y2, 0), color);
		}
		else {
			if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; y <= y2; y++) {
				frameBuffer.WriteBuffer(x, y, color);
				DrawLine(v0, Vector3f(x, y, 0), color);
				rem += dx;
				if (rem >= dy) {
					rem -= dy;
					x += (x2 >= x1) ? 1 : -1;
					frameBuffer.WriteBuffer(x, y, color);
					DrawLine(v0, Vector3f(x, y, 0), color);
				}
			}
			frameBuffer.WriteBuffer(x2, y2, color);
			DrawLine(v0, Vector3f(x2, y2, 0), color);
		}
	}
}


// 绘制线段
void RenderManager::DrawLine(Vector3f v1,Vector3f v2, Color color) {
	int x, y, rem = 0;
	int x1 = v1.x;
	int y1 = v1.y;
	int x2 = v2.x;
	int y2 = v2.y;
	if (x1 == x2 && y1 == y2) {
		frameBuffer.WriteBuffer(x1, y1, color);
	}
	else if (x1 == x2) {
		int inc = (y1 <= y2) ? 1 : -1;
		for (y = y1; y != y2; y += inc)
		{
			frameBuffer.WriteBuffer(x1, y, color);
		}
		frameBuffer.WriteBuffer(x2, y2, color);
	}
	else if (y1 == y2) {
		int inc = (x1 <= x2) ? 1 : -1;
		for (x = x1; x != x2; x += inc)
		{
			frameBuffer.WriteBuffer(x, y1, color);
		}
		frameBuffer.WriteBuffer(x2, y2, color);
	}
	else {
		int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
		int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
		if (dx >= dy) {
			if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; x <= x2; x++) {
				frameBuffer.WriteBuffer(x, y, color);
				rem += dy;
				if (rem >= dx) {
					rem -= dx;
					y += (y2 >= y1) ? 1 : -1;
					frameBuffer.WriteBuffer(x, y, color);
				}
			}
			frameBuffer.WriteBuffer(x2, y2, color);
		}
		else {
			if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; y <= y2; y++) {
				frameBuffer.WriteBuffer(x, y, color);
				rem += dx;
				if (rem >= dy) {
					rem -= dy;
					x += (x2 >= x1) ? 1 : -1;
					frameBuffer.WriteBuffer(x, y, color);
				}
			}
			frameBuffer.WriteBuffer(x2, y2, color);
		}
	}

	/*
	int dx = (int)v2.x - (int)v1.x;
	int dy = (int)v2.y - (int)v1.y;
	int d = dx - 2 * dy;
	int incrE = -2 * dy;
	int incrNE = 2 * (dx - dy);
	int x = v1.x;
	int y = v1.y;
	frameBuffer.WriteBuffer(x, y, color);
	while (x < v2.x)
	{
		if (d > 0)
		{
			d += incrE;
		}
		else
		{
			d += incrNE;
			y++;
			x++;
		}
		frameBuffer.WriteBuffer(x, y, color);
	}

	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	float m = dy / dx;
	float y = v1.y;
	for (int x = v1.x; x <= v2.x; ++x)
	{
		frameBuffer.WriteBuffer(x, (int)(y + 0.5), color);
		y += m;
	}
	*/
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