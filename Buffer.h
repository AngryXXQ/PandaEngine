#pragma once
#include "IncludeManager.h"

class Buffer
{
public:
	Buffer();
	Buffer(float w,float h);
	~Buffer();

	void ResizeBuffer(float w, float h);
	void ClearBuffer(Color color);
	void WriteBuffer(const int& x, const int& y, const Color& color);
	float GetZBuffer(const int& x, const int& y);
	void WriteZBuffer(const int& x, const int& y, float zval);

	std::vector<unsigned char> buffer;
	std::vector<float> zbuffer;
private:
	float width;
	float height;
};

