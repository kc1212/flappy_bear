
#include "texture.hpp"
#include "utils.hpp"
#include <cstring>

Texture::Texture()
{
	zeroAll();
}

Texture::Texture(const char* path, SDL_Renderer* renderer)
{
	zeroAll();
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
	posX = 0;
	posY = 0;
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}

void Texture::zeroAll()
{
	for (int i = 0; i < MAX_PATH_LEN; i++)
	{
		filename[i] = '\0';
	}
	texture = NULL;
	width = 0;
	height = 0;
	posX = 0;
	posY = 0;
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
	return posX;
}

int Texture::getPosY()
{
	return posY;
}

void Texture::setPosX(int x)
{
	posX = x;
}

void Texture::setPosY(int y)
{
	posY = y;
}

void Texture::renderCopy(SDL_Renderer *renderer)
{
	SDL_Rect renderQuad = { posX, posY, width, height };
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
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
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




