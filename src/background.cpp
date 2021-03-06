#include "background.hpp"
#include "utils.hpp"

Background::Background() : GameEntity()
{
	night = false;
}

Background::Background(const char* path, SDL_Renderer* renderer)
	: mTexture(path, renderer, true)
{
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = mTexture.getHeight();
	night = false;
	mRenderer = renderer;
}

// destructors are called automatically in the reverse order
Background::~Background() {}

void Background::render() const
{
	if ( 0 != SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &mRect))
	{
		log_err("background render copy failed! SDL_Error: %s\n", SDL_GetError());
	}
//	if (DEBUG) printf("background\trenderer: %p, texture: %p, [%d,%d,%d,%d]\n",
//					  (void*)mRenderer, (void*)mTexture.getTexture(), mRect.x, mRect.y, mRect.w, mRect.h);
}



