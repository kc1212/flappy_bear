// ultility functions

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

SDL_Surface* loadSurface(const char* path, SDL_Surface* screenSurface);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void showRenderDriver();

#endif
