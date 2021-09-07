#include "Buffer.h"

Buffer::Buffer()
{

}

Buffer::Buffer(float w, float h)
{
	width = w;
	height = h;
	buffer.resize(w * h * 4, 0);
}

Buffer::~Buffer()
{

}

void Buffer::ResizeBuffer(float w, float h)
{
	width = w;
	height = h;
	buffer.resize(w * h * 4, 0);
}

void Buffer::ClearBuffer(Color color)
{
	for (int i = 0; i < width * height * 4; i += 4)
	{
		unsigned char* buf = buffer.data();
		*(buf + i) = color.r;
		*(buf + i + 1) = color.g;
		*(buf + i + 2) = color.g;
		*(buf + i + 3) = color.a;
	}
}

void Buffer::WriteBuffer(const int& x, const int& y, const Color& color)
{
	if (x<0 || x>=width || y<0 || y>=height)
	{
		return;
	}
	int xy = y * width + x;
	buffer[xy * 4] = color.r;
	buffer[xy * 4 + 1] = color.g;
	buffer[xy * 4 + 2] = color.b;
	buffer[xy * 4 + 3] = color.a;
}