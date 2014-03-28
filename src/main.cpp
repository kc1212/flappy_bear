/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cstdio>

#include "player.hpp"
#include "utils.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_SPACE,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gCurrentSurface = NULL;

SDL_Surface* gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL] = {};

// http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init(){

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;

	}
	else {
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;

		}
		else {
			showRenderDriver();

			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialise renderer colour
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				// initialise png and jpg loading
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if ( !(IMG_Init(imgFlags) & imgFlags) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				else
				{
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface( gWindow );
				}
			}
		}
	}

	return success;
}


bool loadMedia(){

	//Loading success flag
	bool success = true;

	//Load splash image, using renderer
	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../assets/hello_world.bmp", gScreenSurface);
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		fprintf(stderr, "failed to load default image...");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_SPACE] = loadSurface("../assets/background.png", gScreenSurface);
	if (gKeyPressSurface[KEY_PRESS_SURFACE_SPACE] == NULL)
	{
		fprintf(stderr, "failed to load space image...");
		success = false;
	}

	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("../assets/stretch.bmp", gScreenSurface);
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		fprintf(stderr, "failed to load left image...");
		success = false;
	}

	gTexture = loadTexture("../assets/ship.png", gRenderer);
	if (gTexture == NULL)
	{
		fprintf(stderr, "failed to load right texture...");
		success = false;
	}

	return success;
}


void close()
{
	//Deallocate surface
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++)
	{
		SDL_FreeSurface( gKeyPressSurface[i] );
		gKeyPressSurface[i] = NULL;
	}


	SDL_DestroyTexture( gTexture );
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gTexture = NULL;
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	(void) argc; (void) args; // hack to get rid of warning messages..
	int flag = 0; // 0 for surface, 1 for renderer

	//Start up SDL and create window
	if( !init() )
	{
		fprintf( stderr, "Failed to initialize!\n" );
		close(); // we dont need to fre resources
		return 1;
	}
	//Load media
    if( !loadMedia() )
    {
        fprintf( stderr, "Failed to load media!\n" );
		close();
		return 1;
    }

	bool quit = false;
	Player p1;
	SDL_Event e;
	gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

	while (!quit)
	{
		while (SDL_PollEvent( &e ) != 0 )
		{

			if (e.type == SDL_QUIT ){
				quit = true;

			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_SPACE:
						flag = 0;
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_SPACE];
						p1.jump();
						break;
					case SDLK_LEFT:
						flag = 0;
						p1.left();
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
						break;
					case SDLK_RIGHT:
						flag = 1;
						printf("test renderer...\n");
						break;
					case SDLK_q:
						flag = 0;
						p1.die();
						quit = true;
						break;
					default:
						flag = 0;
						gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
						break;
				}
			}
		}

		//Apply the image

		//Apply the image stretched
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;

		if (flag == 0)
		{
			SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
			SDL_UpdateWindowSurface( gWindow );
		}
		else {
			SDL_RenderClear( gRenderer );
			SDL_RenderCopy( gRenderer, gTexture, &stretchRect, NULL );
			SDL_RenderPresent( gRenderer );
		}
		SDL_Delay(80);
	}

	//Free resources and close SDL
	close();
	return 0;
}
