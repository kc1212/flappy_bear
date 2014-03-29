
#include "texture.hpp"
#include "utils.hpp"
#include <cstring>

Texture::Texture()
{
	for (int i = 0; i < MAX_PATH_LEN; i++)
	{
		filename[i] = '\0';
	}
	texture = NULL;
	width = 0;
	height = 0;
	positionX = 0;
	positionY = 0;
}

Texture::Texture(const char* path, SDL_Renderer* renderer)
{
	// need to check for filename max length
	strcpy(filename, path);
	loadTextureFromFile(path, renderer);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
	width = 0;
	height = 0;
	positionX = 0;
	positionY = 0;
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}

void Texture::setTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_DestroyTexture( texture );
	texture = NULL;
	strcpy(filename, path);
	loadTextureFromFile(path, renderer);
}

void Texture::setHeight(int h)
{
	height = h;
}

void Texture::setWidth(int w)
{
	width = w;
}

int Texture::getHeight()
{
	return height;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getPosX()
{
	return positionX;
}

int Texture::getPosY()
{
	return positionY;
}

void Texture::setPosX(int x)
{
	positionX = x;
}

void Texture::setPosY(int y)
{
	positionY = y;
}

void Texture::render(SDL_Renderer *renderer)
{
	SDL_Rect renderQuad = { positionX, positionY, width, height };
	SDL_RenderCopy (renderer, texture, NULL, &renderQuad);
}

// Private methods
void Texture::loadTextureFromFile(const char* path, SDL_Renderer* renderer)
{

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = NULL;

	loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);

		width = loadedSurface->w;
		height = loadedSurface->h;
		texture = newTexture;
	}

}




