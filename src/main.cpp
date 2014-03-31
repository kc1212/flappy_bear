
#include "utils.hpp"
#include "player.hpp"
#include "background.hpp"

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


		if (abs(bg1.getPosX()) > bg1.getWidth())
		{
			bg1.setPosX(0);
		}

		bg1.setPosX(bg1.getPosX()-10);

		// Draw the position of bg1 and p1
		bg1.render(renderer, bg1.getPosX(), bg1.getPosY());
		bg1.render(renderer, bg1.getPosX()+SCREEN_WIDTH, bg1.getPosY());
		p1.render(renderer);

		SDL_RenderPresent( renderer );
		SDL_Delay( LOOP_DELAY );
	}

	close(window, renderer);
	return 0;
}

