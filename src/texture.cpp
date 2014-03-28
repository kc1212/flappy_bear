
#include "texture.hpp"
#include "utils.hpp"
#include <cstring>

SDL_Texture* Texture::getTexture()
{
	return texture;
}

void Texture::setTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_DestroyTexture( texture );
	strcpy(filename, path);
	texture = loadTexture(path, renderer);
}

Texture::Texture()
{
	filename[0] = '\0';
	texture = NULL;
}

Texture::Texture(const char* path, SDL_Renderer* renderer)
{
	// need to check for filename max length
	strcpy(filename, path);
	texture = loadTexture(path, renderer);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}
