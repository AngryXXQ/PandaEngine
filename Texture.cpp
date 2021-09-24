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
	//GL_REPEAT
	float x = texcoord.x - (float)floor(texcoord.x);
	float y = texcoord.y - (float)floor(texcoord.y);
	return GetColor(x * (width - 1), y * (height - 1));
}

Vector3f Texture::GetColor(int x, int y) {
	if (x <0 || x > width || y < 0 || y> height)
		return Vector3f(0, 0, 0, 0);
	int xy = channels * (y * width + x);
	return Vector3f(*(data + xy), *(data + xy + 1), *(data + xy + 2), *(data + xy + 3));
}