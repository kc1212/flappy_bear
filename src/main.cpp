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

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

enum KeyPressTextures {
	KEY_PRESS_TEXTURE_DEFAULT,
	KEY_PRESS_TEXTURE_SPACE,
	KEY_PRESS_TEXTURE_LEFT,
	KEY_PRESS_TEXTURE_RIGHT,
	KEY_PRESS_TEXTURE_TOTAL
};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gCurrentTexture = NULL;
SDL_Texture* gKeyPressTexture[KEY_PRESS_TEXTURE_TOTAL] = {};

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


bool loadMedia(){

	//Loading success flag
	bool success = true;

	//Load splash image, using renderer
	gKeyPressTexture[KEY_PRESS_TEXTURE_DEFAULT] = loadTexture("../assets/hello_world.bmp", gRenderer);
	if (gKeyPressTexture[KEY_PRESS_TEXTURE_DEFAULT] == NULL)
	{
		fprintf(stderr, "failed to load default image...");
		success = false;
	}

	gKeyPressTexture[KEY_PRESS_TEXTURE_SPACE] = loadTexture("../assets/background.png", gRenderer);
	if (gKeyPressTexture[KEY_PRESS_TEXTURE_SPACE] == NULL)
	{
		fprintf(stderr, "failed to load space image...");
		success = false;
	}

	gKeyPressTexture[KEY_PRESS_TEXTURE_LEFT] = loadTexture("../assets/stretch.bmp", gRenderer);
	if (gKeyPressTexture[KEY_PRESS_TEXTURE_LEFT] == NULL)
	{
		fprintf(stderr, "failed to load left image...");
		success = false;
	}

	gKeyPressTexture[KEY_PRESS_TEXTURE_RIGHT] = loadTexture("../assets/ship.png", gRenderer);
	if (gKeyPressTexture[KEY_PRESS_TEXTURE_RIGHT] == NULL)
	{
		fprintf(stderr, "failed to load right texture...");
		success = false;
	}

	return success;
}


void close()
{
	//Deallocate surface
	for (int i = 0; i < KEY_PRESS_TEXTURE_TOTAL; i++)
	{
		SDL_DestroyTexture( gKeyPressTexture[i] );
		gKeyPressTexture[i] = NULL;
	}

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
	//Load media
    if( !loadMedia() )
    {
        fprintf( stderr, "Failed to load media!\n" );
		close();
		return 1;
    }

	bool quit = false;
	SDL_Event e;
	Player p1;
	Background bg1("../assets/background.png", gRenderer);
	gCurrentTexture = gKeyPressTexture[KEY_PRESS_TEXTURE_DEFAULT];

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
						gCurrentTexture = gKeyPressTexture[KEY_PRESS_TEXTURE_SPACE];
						p1.jump();
						break;
					case SDLK_LEFT:
						p1.left();
						gCurrentTexture = gKeyPressTexture[KEY_PRESS_TEXTURE_LEFT];
						break;
					case SDLK_RIGHT:
						gCurrentTexture = gKeyPressTexture[KEY_PRESS_TEXTURE_RIGHT];
						printf("test renderer...\n");
						break;
					case SDLK_q:
						p1.die();
						quit = true;
						break;
					default:
						printf("default...\n");
						gCurrentTexture = gKeyPressTexture[KEY_PRESS_TEXTURE_DEFAULT];
						break;
				}
			}
		}

		//Apply the image stretched
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;

		SDL_RenderClear( gRenderer );
		SDL_RenderCopy( gRenderer, gCurrentTexture, &stretchRect, NULL );
		SDL_RenderPresent( gRenderer );

		SDL_Delay(80);
	}

	//Free resources and close SDL
	close();
	return 0;
}
