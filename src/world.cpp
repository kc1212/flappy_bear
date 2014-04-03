#include "world.hpp"
#include "config.hpp"
#include "utils.hpp"

#define RANDOM_HEIGHT (OBSTACLE_MIN_HEIGHT + \
    rand() % (SCREEN_HEIGHT - OBSTACLE_VGAP - 2*OBSTACLE_MIN_HEIGHT))


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
					player.jump();
					break;
				case SDLK_r:
					player.restartGame();
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

    detectCollision();

    scrollBackground();
    updateObstacles();

	player.updatePosition();
	player.render(worldRenderer);

	SDL_RenderPresent(worldRenderer);
	SDL_Delay( LOOP_DELAY ); // TODO need better delay

	return quit;
}

bool World::detectCollision()
{
	// TODO only checking bountry at the moment, need to collision detection for other objects
	if (player.getPosY() <= -5 || player.getPosY() >= SCREEN_HEIGHT - player.getHeight() + 5)
	{
		if (DEBUG) printf("***collided!\tposY: %d\n", player.getPosY());
		player.die();
		return true;
	}
	return false;
}

// make sure the members appear in the initializer list in the same order as they appear in the class
// resources taken from http://lanica.co/flappy-clone/
World::World(SDL_Renderer *renderer, SDL_Window *window)
    : background("../assets/night_bg.png", renderer),
      player("../assets/black-bubble.png", renderer, 140, 140)
{
    for (int i = 0; i < OBSTACLE_COUNT; i++){
        obstacle[i].setAttrs(300+i*OBSTACLE_HGAP,0,100,200);
        obstacle[i].setHeight(RANDOM_HEIGHT);
    }
    worldRenderer = renderer;
	worldWindow = window;
}

void World::stop()
{
	close(worldWindow, worldRenderer);
}

World::~World()
{
	World::stop();
}

void World::scrollBackground()
{
    if (!player.isDead()) {
        if (background.getPosX() <= -background.getWidth())
        {
            background.setPosX(0);
        }

        background.setPosX(background.getPosX()-BACKGROUND_VELOCITY);
        if (DEBUG) printf("bg posX: %d\n", background.getPosX());
    }

	// Draw the position of bg1 and p1
    background.render(worldRenderer, background.getPosX(), background.getPosY(),
                      background.getWidth(), SCREEN_HEIGHT);
    background.render(worldRenderer, background.getPosX()+background.getWidth(), background.getPosY(),
                      background.getWidth(), SCREEN_HEIGHT);
    background.render(worldRenderer, background.getPosX()+2*background.getWidth(), background.getPosY(),
                      background.getWidth(), SCREEN_HEIGHT);
}

void World::updateObstacles()
{
    if (player.isDead())
    {
        for (int i = 0; i < OBSTACLE_COUNT; i++){
            obstacle[i].render(worldRenderer);
        }
    }
    else
    {
        for (int i = 0; i < OBSTACLE_COUNT; i++){
            obstacle[i].render(worldRenderer);
            obstacle[i].setPosX(obstacle[i].getPosX()-OBSTACLE_VELOCITY);
            if (obstacle[i].getPosX() <= -obstacle[i].getWidth()){
                obstacle[i].setPosX(300+((OBSTACLE_COUNT-1)*OBSTACLE_HGAP));
                obstacle[i].setHeight(RANDOM_HEIGHT);
            }
        }
    }
}


