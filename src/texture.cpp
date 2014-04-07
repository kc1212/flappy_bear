
#include "texture.hpp"
#include "utils.hpp"
#include <cstring>

Texture::Texture()
	: mIsImage(true)
{
	zeroAll();
}

Texture::Texture(const char* path, SDL_Renderer* renderer, bool isImage)
	: mIsImage(isImage)
{
	zeroAll(); // we can delegate constructor in C++11
	// TODO need to check for filename max length
	strcpy(mFilename, path);
	if (mIsImage)
	{
		loadTextureFromFile(path, renderer);
	}
	else 
	{
		mFont = TTF_OpenFont( "../assets/CourierNew.ttf", 72 );
		loadFromRenderedText(path, renderer);
	}
}

Texture::~Texture()
{
	if (mIsImage)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	else
	{
		TTF_CloseFont(mFont);
		mFont = NULL;
	}
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
	if (mIsImage)
	{
		loadTextureFromFile(path, renderer);	
	}
	else 
	{
		loadFromRenderedText(path, renderer);
	}
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

	loadedSurface= IMG_Load(path);
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

bool Texture::loadFromRenderedText(const char* string, SDL_Renderer* renderer)
{
	//Get rid of preexisting texture
	zeroAll();	
	//Render text surfacegFont
	SDL_Color textColor = {255,255,255,255};
	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, string, textColor );

	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
}



