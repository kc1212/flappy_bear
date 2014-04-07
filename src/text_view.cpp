#include "text_view.hpp"
#include <cstdio>

TextView::TextView() : GameEntity()
{}

TextView::TextView(const char* string, SDL_Renderer* renderer, int startX, int startY)
	: mTexture(string, renderer, false)
{
	mRect.x = startX;
	mRect.y = startY;
	mRect.w = mTexture.getWidth();
	mRect.h = mTexture.getHeight();
	mRenderer = renderer;
	mText = string;
}

// destructors are called automatically in the reverse order
TextView::~TextView() {}

void TextView::render() const
{	
	SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &mRect);
}

void TextView::setText(const char* text)
{
	mText = text;
	mTexture.resetTexture(mText, mRenderer, false);
}

