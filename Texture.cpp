#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{

}

Texture::Texture(const std::string & Path) {
	data = stbi_load(Path.c_str(), &width, &height, &channels, 0);
}

Texture::~Texture() {
	if (data)
		free(data);
}

void Texture::LoadTexture(const std::string & Path) {
	if (data)
		free(data);
	data = stbi_load(Path.c_str(), &width, &height, &channels, 0);
}

Vector3f Texture::Sample2D(Vector3f & texcoord) {
	int x = (int)(texcoord.x * width - 0.5f) % width;
	int y = (int)(texcoord.y * height - 0.5f) % height;
	x = x < 0 ? width + x : x;
	y = y < 0 ? height + y : y;
	return GetColor(x, y);
}

Vector3f Texture::GetColor(int x, int y) {
	if (x <0 || x > width || y < 0 || y> height)
		return Vector3f(0, 0, 0, 0);
	int xy = channels * (y * width + x);
	return Vector3f(*(data + xy), *(data + xy + 1), *(data + xy + 2), *(data + xy + 3));
}