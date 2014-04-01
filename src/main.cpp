
#include "utils.hpp"
#include "player.hpp"
#include "background.hpp"
#include "obstacle.hpp"
#include "world.hpp"

#include <cstdio>

int main( int argc, char* args[] )
{
	(void) argc; (void) args; // hack to get rid of warning messages..

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	// http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer
	SDL_Renderer* renderer = NULL;

	//Start up SDL and create window
	if( !init(window, renderer) )
	{
		fprintf( stderr, "Failed to initialize!\n" );
		close(window, renderer); // we dont need to fre resources
		return 1;
	}
	World world(renderer, window);
	return world.start();
	
}

