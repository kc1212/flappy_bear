/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cstdio>

#include "player.hpp"
#include "utils.hpp"
#include "background.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer
SDL_Renderer* gRenderer = NULL;

bool init(){

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}
	//Create window
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	// display info on render driver
	showRenderDriver();

	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialise renderer colour
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	// initialise png and jpg loading
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ( !(IMG_Init(imgFlags) & imgFlags) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	return true;
}

void close()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	(void) argc; (void) args; // hack to get rid of warning messages..

	//Start up SDL and create window
	if( !init() )
	{
		fprintf( stderr, "Failed to initialize!\n" );
		close(); // we dont need to fre resources
		return 1;
	}

	bool quit = false;
	SDL_Event e;
	Player p1("../assets/foo.png", gRenderer);
	p1.setPosX(240);
	p1.setPosY(140);
	Background bg1("../assets/background.png", gRenderer);

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
						p1.jump();
						break;
					case SDLK_LEFT:
						p1.left();
						break;
					case SDLK_RIGHT:
						p1.right();
						break;
					case SDLK_q:
						p1.die();
						quit = true;
						break;
					default:
						break;
				}
			}
		}

		SDL_RenderClear( gRenderer );

		bg1.render(gRenderer);
		p1.render(gRenderer);

		SDL_RenderPresent( gRenderer );

		SDL_Delay(80);
	}

	//Free resources and close SDL
	close();
	return 0;
}
