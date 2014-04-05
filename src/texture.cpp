
#include "texture.hpp"
#include "utils.hpp"
#include <cstring>

Texture::Texture()
{
	zeroAll();
}

Texture::Texture(const char* path, SDL_Renderer* renderer)
{
	printf("path %s\n", path);
	zeroAll(); // we can delegate constructor in C++11
	// TODO need to check for filename max length
	strcpy(mFilename, path);
	loadTextureFromFile(path, renderer);
}

Texture::~Texture()
{
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
}

SDL_Texture* Texture::getTexture() const
{
	return mTexture;
}

void Texture::zeroAll()
{
	for (int i = 0; i < MAX_PATH_LEN; i++)
	{
		mFilename[i] = '\0';
	}
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void Texture::resetTexture(const char* path, SDL_Renderer* renderer)
{
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	strcpy(mFilename, path);
	loadTextureFromFile(path, renderer);
}

void Texture::setHeight(int h)
{
	mHeight = h;
}

void Texture::setWidth(int w)
{
	mWidth = w;
}

int Texture::getHeight()
{
	return mHeight;
}

int Texture::getWidth()
{
	return mWidth;
}

//// overloaded, we might be able to do better
//void Texture::render(SDL_Renderer *renderer, int x, int y, int w, int h)
//{
//    SDL_Rect renderQuad = { x, y, w, h};
//	SDL_RenderCopy (renderer, texture, NULL, &renderQuad);
//}

//void Texture::render(SDL_Renderer *renderer, int x, int y)
//{
//    SDL_Rect renderQuad = { x, y, width, height};
//    SDL_RenderCopy (renderer, texture, NULL, &renderQuad);
//}

//void Texture::render(SDL_Renderer *renderer)
//{
//	SDL_Rect renderQuad = {posX, posY, width, height};
//	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
//}

// Private methods
bool Texture::loadTextureFromFile(const char* path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = NULL;
	if (renderer == NULL)
	{
		fprintf(stderr, "renderer is null in %s\n", __func__);
		return false;
	}

	loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("unable to load image %s in %s! SDL_image Error: %s\n", path, __func__, IMG_GetError());
		return false;
	}

	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
	newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	if (newTexture == NULL)
	{
		printf("unable to create texture from %s in %s! SDL Error: %s\n", path, __func__, SDL_GetError());
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;
	return true;

}


