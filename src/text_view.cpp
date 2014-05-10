#include "text_view.hpp"
#include "utils.hpp"

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
}

// destructors are called automatically in the reverse order
TextView::~TextView() {}

void TextView::render() const
{	
	SDL_RenderCopy(mRenderer, mTexture.getTexture(), NULL, &mRect);
}

void TextView::setText(const char* text)
{
	// strcpy(mText, text);
	// mTexture.resetTexture(text, mRenderer);
	mTexture.resetFontText(text, mRenderer);
}

void TextView::setText(const int num)
{
	// not that itoa isn't standard function
	char buffer[256];
	sprintf(buffer, "%d", num);
	mTexture.resetFontText(buffer, mRenderer);
}

void TextView::setText(const double num)
{
	// not that itoa isn't standard function
	char buffer[256];
	sprintf(buffer, "%.2f", num);
	mTexture.resetFontText(buffer, mRenderer);
}

