/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cstdio>

#include "player.hpp"
#include "utils.hpp"
#include "background.hpp"

//The window we'll be rendering to
SDL_Window* window = NULL;

// http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer
SDL_Renderer* renderer = NULL;

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
	Player p1("../assets/foo.png", renderer, 240, 140);
	Background bg1("../assets/background.png", renderer);

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
					case SDLK_q:
						p1.die();
						quit = true;
						break;
					default:
						break;
				}
			}
		}

		SDL_RenderClear( renderer );

		p1.updatePosition();

		bg1.renderCopy(renderer);
		p1.renderCopy(renderer);

		SDL_RenderPresent( renderer );
		SDL_Delay( LOOP_DELAY );
	}

	close();
	return 0;
}

