#include "geometry.hpp"

Geometry::Geometry(){}

Geometry::Geometry(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	mRenderer = renderer;
	mRect.x = x;
	mRect.y = y;
	mRect.w = w;
	mRect.h = h;
	mRed = 0x00;
	mGreen = 0x00;
	mBlue = 0x00;
	mAlpha = 0x20;
}

Geometry::~Geometry(){}

void Geometry::render() const
{
	SDL_SetRenderDrawColor( mRenderer, mRed, mGreen, mBlue, mAlpha );
	SDL_RenderFillRect( mRenderer, &mRect );
}




