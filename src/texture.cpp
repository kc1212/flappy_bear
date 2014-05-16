
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
	if (DEBUG) debug("texture constructor: [%s, %d, %p]", mFilename, mIsImage, (void*)this);

	// TODO check if file exists

	if (mIsImage)
	{
		// TODO check if loadTextureFromFile failed
		loadTextureFromFile(path, renderer);
	}
	else
	{
		// TODO check if loadFromRenderedText failed
		mFont = TTF_OpenFont( path, 72 );
		loadFromRenderedText("0", renderer);
	}
}

Texture::~Texture()
{
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	if (DEBUG) debug("texture destructor: [%s, %d, %p]", mFilename, mIsImage, (void*)this);
	if (!mIsImage)
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

void Texture::resetTexture(const char* path, SDL_Renderer* const renderer)
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
		log_warn("attribute mIsImage (=%d) is expected to be true in", mIsImage);
	}
}


void Texture::resetFontText(const char* text, SDL_Renderer* const renderer)
{

	SDL_DestroyTexture(mTexture);
	mTexture = NULL;

	if (!mIsImage)
	{
		loadFromRenderedText(text, renderer);
	}
	else
	{
		log_warn("WARNING: attribute mIsImage (=%d) is expected to be false", mIsImage);
	}
}


// Private methods
bool Texture::loadTextureFromFile(const char* path, SDL_Renderer* const renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = NULL;
	if (renderer == NULL)
	{
		log_err("renderer is null in (path: %s)", path);
		return false;
	}

	loadedSurface= IMG_Load(path);
	if (loadedSurface == NULL)
	{
		log_err("unable to load image %s! SDL_image Error: %s", path, IMG_GetError());
		return false;
	}

	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
	newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	if (newTexture == NULL)
	{
		log_err("unable to create texture from %s! SDL Error: %s", path, SDL_GetError());
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);

	mTexture = newTexture;
	return true;
}

bool Texture::loadFromRenderedText(const char* string, SDL_Renderer* const renderer)
{
	//Render text surfacegFont
	SDL_Color textColor = {255,255,255,255};
	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, string, textColor );

	if( textSurface == NULL )
	{
		log_err( "unable to render text surface! SDL_ttf Error: %s", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == NULL )
		{
			log_err( "Unable to create texture from rendered text! SDL Error: %s", SDL_GetError() );
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



