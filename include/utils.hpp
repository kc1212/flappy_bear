// ultility functions

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/*
 * show information about renderer driver
 */
void showRenderDriver();

/*
 * starts up SDL, SDL_Image, and creates window
 */
bool init(SDL_Window* &window, SDL_Renderer* &renderer);

/*
 * frees media and shuts down SDL
 */
void close(SDL_Window* &window, SDL_Renderer* &renderer);

#endif
