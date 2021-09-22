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
			m->modelTransform.rotation += rot * 10;
		}
		render_queue.pop();
		break;
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
	m_MainCamera->SetAspect(width, height);
	viewportMatrix(0, 0) = width / 2;
	viewportMatrix(0, 3) = width / 2;
	viewportMatrix(1, 1) = height / 2;
	viewportMatrix(1, 3) = height / 2;
}

//#define DRAW_LINE 1

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

	shader.V = m_MainCamera->viewMatrix;
	shader.P = m_MainCamera->projectionMatrix;
	int count = 0;
	Color pcolor(255, 255, 255, 255);
	Color tcolor(125, 125, 125, 255);
	frameBuffer.ClearBuffer(tcolor);

	std::queue<Model*> render_queue = model_queue;
	int model_count = render_queue.size();
	for (int i = 0; i < model_count; ++i)
	{
		pcolor.g -= i * 100;
		if (pcolor.g < 0)
		{
			pcolor.g = 0;
		}
		Model* m = render_queue.front();
		if (m)
		{
			shader.M = m->GetModelTransform();
			shader.MV = shader.V * shader.M;
			shader.MVP = shader.P * shader.MV;
			for (int j = 0; j < m->vertexVector.size(); ++j)
			{
				std::vector<Vertex> vlist = m->vertexVector[j];
				Vertex v[3];
				for (int k = 0; k < 3; ++k)
				{
					v[k] = shader.VertexShader(vlist[k]);
				}

				if (FaceCulling(v[0].vertex, v[1].vertex, v[2].vertex))
				{
					++count;
					continue;
				}

				for (int m = 0; m < 3; ++m)
				{
					PerspectiveDivision(v[m].vertex);
					ViewPortMapping(v[m].vertex);
				}

				Vector3f v0 = v[0].vertex;
				Vector3f v1 = v[1].vertex;
				Vector3f v2 = v[2].vertex;
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

void RenderManager::PerspectiveDivision(Vector3f& v)
{
	float d = 1 / v.w;
	v = v * d;
	v.w = 1;
}

void RenderManager::ViewPortMapping(Vector3f& v)
{
	v = viewportMatrix * v;
}

//面剔除
bool RenderManager::FaceCulling(Vector3f v0, Vector3f v1, Vector3f v2)
{
	Vector3f v01 = v1 - v0;
	Vector3f v02 = v2 - v0;
	Vector3f f = v01.Cross(v02);
	float t = f.Dot(m_MainCamera->dir);
	return t <= 0;
}

// 绘制三角形
void RenderManager::DrawTriangle(Vector3f v0, Vector3f v1, Vector3f v2, Color color) {
	int x1 = v1.x;
	int y1 = v1.y;
	int x2 = v2.x;
	int y2 = v2.y;
	int dxOld = x2 - x1;
	int dyOld = y2 - y1;
	int dxNew = x2 - x1;
	int dyNew = y2 - y1;
	float m = 1;

	int z1 = v1.z;
	int z2 = v2.z;
	int dzOld = z2 - z1;
	float mz = 1;

	if (dxOld > 0 && dyOld > 0)
	{
		m = (float)dyOld / (float)dxOld;
		if (m > 0 && m <= 1)
		{
		}
		else if (m > 1)
		{
			x1 = v1.y;
			y1 = v1.x;
			x2 = v2.y;
			y2 = v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld > 0 && dyOld < 0)
	{
		m = (float)(-dyOld) / (float)dxOld;
		if ((m > 0 && m <= 1))
		{
			x1 = v1.x;
			y1 = -v1.y;
			x2 = v2.x;
			y2 = -v2.y;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
		else if (m > 1)
		{
			x1 = -v1.y;
			y1 = v1.x;
			x2 = -v2.y;
			y2 = v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld < 0 && dyOld > 0)
	{
		m = (float)dyOld / (float)(-dxOld);
		if ((m > 0 && m <= 1))
		{
			x1 = -v1.x;
			y1 = v1.y;
			x2 = -v2.x;
			y2 = v2.y;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
		else if (m > 1)
		{
			x1 = v1.y;
			y1 = -v1.x;
			x2 = v2.y;
			y2 = -v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld < 0 && dyOld < 0)
	{
		m = (float)(-dyOld) / (float)(-dxOld);
		if (m > 0 && m <= 1)
		{
			x1 = -v1.x;
			y1 = -v1.y;
			x2 = -v2.x;
			y2 = -v2.y;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
		else if (m > 1)
		{
			x1 = -v1.y;
			y1 = -v1.x;
			x2 = -v2.y;
			y2 = -v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld == 0 && dyOld == 0)
	{
		float z = v1.z;
		if (v2.z < v1.z)
		{
			z = v2.z;
		}
		DrawLine(v0, Vector3f(x1, y1, z), color);
		return;
	}
	else if (dxOld == 0 && dyOld != 0)
	{
		mz = (float)dzOld / (float)dyOld;
		if (mz < 0)
		{
			mz = -mz;
		}
		if (dyOld > 0)
		{
			x1 = v1.x;
			y1 = v1.y;
			x2 = v2.x;
			y2 = v2.y;
		}
		else
		{
			x1 = v2.x;
			y1 = v2.y;
			x2 = v1.x;
			y2 = v1.y;
		}
		int xi = x1;
		int yi = y1;
		while (yi < y2)
		{
			float z = mz * yi;
			DrawLine(v0, Vector3f(xi, yi, z), color);
			++yi;
		}
		return;
	}
	else if (dxOld != 0 && dyOld == 0)
	{
		mz = (float)dzOld / (float)dxOld;
		if (mz < 0)
		{
			mz = -mz;
		}
		if (dxOld > 0)
		{
			x1 = v1.x;
			y1 = v1.y;
			x2 = v2.x;
			y2 = v2.y;
		}
		else
		{
			x1 = v2.x;
			y1 = v2.y;
			x2 = v1.x;
			y2 = v1.y;
		}
		int xi = x1;
		int yi = y1;
		while (xi < x2)
		{
			float z = mz * xi;
			DrawLine(v0, Vector3f(xi, yi, z), color);
			++xi;
		}
		return;
	}

	int ddx = 2 * dxNew;
	int ddy = 2 * dyNew;
	int xi = x1;
	int yi = y1;
	int pi = ddy - dxNew;

	mz = (float)dzOld / (float)dxOld;
	if (mz < 0)
	{
		mz = -mz;
	}

	while (xi != x2 + 1)
	{
		if (pi < 0)
		{
			pi = pi + ddy;
			yi = yi;
		}
		else
		{
			pi = pi + ddy - ddx;
			++yi;
		}
		//将素(x, y)涂色
		if (dxOld > 0 && dyOld > 0)
		{
			if (m > 0 && m <= 1)
			{
				float z = mz * xi;
				DrawLine(v0, Vector3f(xi, yi, z), color);
			}
			else if (m > 1)
			{
				float z = mz * yi;
				DrawLine(v0, Vector3f(yi, xi, z), color);
			}
		}
		else if (dxOld > 0 && dyOld < 0)
		{
			if ((m > 0 && m <= 1))
			{
				float z = mz * xi;
				DrawLine(v0, Vector3f(xi, -yi, z), color);
			}
			else if (m > 1)
			{
				float z = mz * yi;
				DrawLine(v0, Vector3f(yi, -xi, z), color);
			}
		}
		else if (dxOld < 0 && dyOld > 0)
		{
			if ((m > 0 && m <= 1))
			{
				float z = mz * -xi;
				DrawLine(v0, Vector3f(-xi, yi, z), color);
			}
			else if (m > 1)
			{
				float z = mz * -yi;
				DrawLine(v0, Vector3f(-yi, xi, z), color);
			}
		}
		else if (dxOld < 0 && dyOld < 0)
		{
			if (m > 0 && m <= 1)
			{
				float z = mz * -xi;
				DrawLine(v0, Vector3f(-xi, -yi, z), color);
			}
			else if (m > 1)
			{
				float z = mz * -yi;
				DrawLine(v0, Vector3f(-yi, -xi, z), color);
			}
		}
		++xi;
	}
}

// Bresenham算法绘制线段
void RenderManager::DrawLine(Vector3f v1,Vector3f v2, Color color) {
	int x1 = v1.x;
	int y1 = v1.y;
	int x2 = v2.x;
	int y2 = v2.y;

	int dxOld = x2 - x1;
	int dyOld = y2 - y1;
	int dxNew = x2 - x1;
	int dyNew = y2 - y1;
	float m = 1;

	int z1 = v1.z;
	int z2 = v2.z;
	int dzOld = z2 - z1;
	float mz = 1;

	if (dxOld > 0 && dyOld > 0)
	{
		m = (float)dyOld / (float)dxOld;
		if (m > 0 && m <= 1)
		{
		}
		else if (m > 1)
		{
			x1 = v1.y;
			y1 = v1.x;
			x2 = v2.y;
			y2 = v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld > 0 && dyOld < 0)
	{
		m = (float)(-dyOld) / (float)dxOld;
		if ((m > 0 && m <= 1))
		{
			x1 = v1.x;
			y1 = -v1.y;
			x2 = v2.x;
			y2 = -v2.y;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
		else if (m > 1)
		{
			x1 = -v1.y;
			y1 = v1.x;
			x2 = -v2.y;
			y2 = v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld < 0 && dyOld > 0)
	{
		m = (float)dyOld / (float)(-dxOld);
		if ((m > 0 && m <= 1))
		{
			x1 = -v1.x;
			y1 = v1.y;
			x2 = -v2.x;
			y2 = v2.y;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
		else if (m > 1)
		{
			x1 = v1.y;
			y1 = -v1.x;
			x2 = v2.y;
			y2 = -v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld < 0 && dyOld < 0)
	{
		m = (float)(-dyOld) / (float)(-dxOld);
		if (m > 0 && m <= 1)
		{
			x1 = -v1.x;
			y1 = -v1.y;
			x2 = -v2.x;
			y2 = -v2.y;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
		else if (m > 1)
		{
			x1 = -v1.y;
			y1 = -v1.x;
			x2 = -v2.y;
			y2 = -v2.x;
			dxNew = x2 - x1;
			dyNew = y2 - y1;
		}
	}
	else if (dxOld == 0 && dyOld == 0)
	{
		float z = v1.z;
		if (v2.z < v1.z)
		{
			z = v2.z;
		}
		DrawPixel(x1, y1, z, color, false);
		return;
	}
	else if (dxOld == 0 && dyOld != 0)
	{
		mz = (float)dzOld / (float)dyOld;
		if (mz < 0)
		{
			mz = -mz;
		}
		if (dyOld > 0)
		{
			x1 = v1.x;
			y1 = v1.y;
			x2 = v2.x;
			y2 = v2.y;
		}
		else
		{
			x1 = v2.x;
			y1 = v2.y;
			x2 = v1.x;
			y2 = v1.y;
		}
		int xi = x1;
		int yi = y1;
		while (yi < y2)
		{
			float z = mz * yi;
			DrawPixel(xi, yi, mz, color, false);
			++yi;
		}
		return;
	}
	else if (dxOld != 0 && dyOld == 0)
	{
		mz = (float)dzOld / (float)dxOld;
		if (mz < 0)
		{
			mz = -mz;
		}
		if (dxOld > 0)
		{
			x1 = v1.x;
			y1 = v1.y;
			x2 = v2.x;
			y2 = v2.y;
		}
		else
		{
			x1 = v2.x;
			y1 = v2.y;
			x2 = v1.x;
			y2 = v1.y;
		}
		int xi = x1;
		int yi = y1;
		while (xi < x2)
		{
			DrawPixel(xi, yi, mz, color);
			++xi;
		}
		return;
	}

	int ddx = 2 * dxNew;
	int ddy = 2 * dyNew;
	int xi = x1;
	int yi = y1;
	int pi = ddy - dxNew;

	mz = (float)dzOld / (float)dxOld;
	if (mz < 0)
	{
		mz = -mz;
	}

	while (xi != x2 + 1)
	{
		if (pi < 0)
		{
			pi = pi + ddy;
			yi = yi;
		}
		else
		{
			pi = pi + ddy - ddx;
			++yi;
		}
		//将素(x, y)涂色
		if (dxOld > 0 && dyOld > 0)
		{
			if (m > 0 && m <= 1)
			{
				DrawPixel(xi, yi, mz, color);
			}
			else if (m > 1)
			{
				DrawPixel(yi, xi, mz, color);
			}
		}
		else if (dxOld > 0 && dyOld < 0)
		{
			if ((m > 0 && m <= 1))
			{
				DrawPixel(xi, -yi, mz, color);
			}
			else if (m > 1)
			{
				DrawPixel(yi, -xi, mz, color);
			}
		}
		else if (dxOld < 0 && dyOld > 0)
		{
			if ((m > 0 && m <= 1))
			{
				DrawPixel(-xi, yi, mz, color);
			}
			else if (m > 1)
			{
				DrawPixel(-yi, xi, mz, color);
			}
		}
		else if (dxOld < 0 && dyOld < 0)
		{
			if (m > 0 && m <= 1)
			{
				DrawPixel(-xi, -yi, mz, color);
			}
			else if (m > 1)
			{
				DrawPixel(-yi, -xi, mz, color);
			}
		}
		++xi;
	}
}

void RenderManager::DrawPixel(int x, int y, float mz, Color color, bool recomputez)
{
	float z = mz;
	if (recomputez)
	{
		z = mz* x;
	}
	float zb = frameBuffer.GetZBuffer(x, y);
	if (zb > z)
	{
		frameBuffer.WriteZBuffer(x, y, z);
		frameBuffer.WriteBuffer(x, y, color);
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