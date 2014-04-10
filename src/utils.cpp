#include "utils.hpp"
#include "config.hpp"

bool init(SDL_Window* &window, SDL_Renderer* &renderer)
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}
	//Create window // TODO resizable window not working correctly, consider stretching
	window = SDL_CreateWindow( "flappy_bear", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	// display info on render driver
	showRenderDriver();

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if( renderer == NULL )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialise renderer colour
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	// initialise png and jpg loading
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ( !(IMG_Init(imgFlags) & imgFlags) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

		// Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}


	return true;
}


void close(SDL_Window* &window, SDL_Renderer* &renderer)
{
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
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


