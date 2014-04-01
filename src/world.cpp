#include "world.hpp"
#include "config.hpp"

int World::start()
{
	bool quit = false;

	while (!quit)
	{
		quit = World::processGameLoop();
	}
	World::stop();
	return 0;
}

bool World::processGameLoop()
{
	SDL_Event e;
	bool quit = false;
	while (SDL_PollEvent (&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_SPACE:
					player->jump();
					break;
				case SDLK_r:
					player->restartGame();
					break;
				case SDLK_q:
					quit = true;
					break;
				default:
					break;
			}

		}
	}

	SDL_RenderClear(worldRenderer);
	World::scrollBackground();

	player->updatePosition();	
	player->render(worldRenderer);

	SDL_RenderPresent(worldRenderer);
	SDL_Delay( LOOP_DELAY );
	return quit;
}

bool World::detectCollision()
{
	return false;
}

World::World(SDL_Renderer *renderer, SDL_Window *window) 
{
	worldRenderer = renderer;
	worldWindow = window;
	player = new Player("../assets/foo.png", worldRenderer, 240, 140);
	background = new Background("../assets/background.png", worldRenderer); 
}

void World::stop()
{
	close(worldWindow, worldRenderer); 	
	delete(player);
	delete(background);
	for (int i=0; i<obstacles.size(); i++)
	{
		delete(obstacles[i]);		
	}
}

World::~World()
{
	World::stop();
}

void World::scrollBackground()
{
	if (abs(background->getPosX()) > background->getWidth())
		{
			background->setPosX(0);
		}

		background->setPosX(background->getPosX()-10);

		// Draw the position of bg1 and p1
		background->render(worldRenderer, background->getPosX(), background->getPosY());
		background->render(worldRenderer, background->getPosX()+SCREEN_WIDTH, background->getPosY());
}