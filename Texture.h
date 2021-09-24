#pragma once
#include "Vector.h"

class Texture
{
public:
	int width;
	int height;
	int channels;
	unsigned char* data;
	Texture();
	Texture(const std::string& Path);
	~Texture();

	void LoadTexture(const std::string& Path);
	Vector3f Sample2D(Vector3f& texcoord);
	Vector3f GetColor(int x, int y);
};

