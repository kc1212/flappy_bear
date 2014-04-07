#include "text_view.hpp"
#include <cstdio>

TextView::TextView() : GameEntity()
{}

TextView::TextView(const char* string, SDL_Renderer* renderer)
	: mTexture(string, renderer, false)
{
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = SCREEN_WIDTH;
	mRect.h = mTexture.getHeight();
	mRenderer = renderer;
}

// destructors are called automatically in the reverse order
TextView::~TextView() {}

void TextView::render() const
{
	SDL_Rect rect = {0,0,100,100};
	SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &rect);
}



