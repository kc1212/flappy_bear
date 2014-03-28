#include "background.hpp"
#include "utils.hpp"

SDL_Texture* Background::getBG()
{
	return bg;
}

void Background::setBG(const char* path, SDL_Renderer* renderer)
{
	SDL_DestroyTexture( bg );
	bg = loadTexture(path, renderer);
}

// overloaded constructor
Background::Background()
{
	bg = NULL;
}

Background::Background(const char* path, SDL_Renderer* renderer)
{
	bg = loadTexture(path, renderer);
}

Background::~Background()
{
	SDL_DestroyTexture(bg);
}
