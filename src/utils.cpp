#include "utils.hpp"
// ultility functions

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
