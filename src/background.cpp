#include "background.hpp"

Background::Background() : Texture()
{
	shaded = false;
}

Background::Background(const char* path, SDL_Renderer* renderer) : Texture(path, renderer)
{
	shaded = false;
}

// destructors are called automatically in the reverse order
Background::~Background() {}

