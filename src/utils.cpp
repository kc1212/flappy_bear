#include "utils.hpp"
// ultility functions

SDL_Surface* loadSurface(const char* path, SDL_Surface* screenSurface){
	// load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	SDL_Surface* optimizedSurface = NULL;
	if (loadedSurface == NULL)
	{
		fprintf(stderr, "unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to load optimized surface for %s, error: %s", path, SDL_GetError() );
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer){

	// apparently it's better to use SDL_Texture, coz it's stored "closer"
	// to gpu memory, so things like resizing, alpha blending, anti-aliasing
	// is quicker, http://stackoverflow.com/questions/12506979/what-is-the-point-of-an-sdl2-texture
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = NULL;

	loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void showRenderDriver(){

	// might need packages such as mesa-common-dev and libgl1-mesa-dev to work
	int numDrivers = SDL_GetNumRenderDrivers();
	printf("Render driver count: %d\n", numDrivers);

	for (int i=0; i<numDrivers; i++) {
		SDL_RendererInfo drinfo;
		SDL_GetRenderDriverInfo (i, &drinfo);
		printf("driver name: %d: %s\n", i, drinfo.name);

		if (drinfo.flags & SDL_RENDERER_SOFTWARE)
			printf("the renderer is a software fallback\n");

		if (drinfo.flags & SDL_RENDERER_ACCELERATED)
			printf("the renderer uses hardware acceleration\n");

		if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC)
			printf("present is synchronized with the refresh rate\n");

		if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE)
			printf("the renderer supports rendering to texture\n");
	}
}
