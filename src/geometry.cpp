#include "geometry.hpp"

Geometry::Geometry(){}

Geometry::Geometry(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	mRenderer = renderer;
	mRect.x = x;
	mRect.y = y;
	mRect.w = w;
	mRect.h = h;
}

Geometry::~Geometry(){}

bool Geometry::render()
{
	return true;
}
