#include "world.hpp"
#include "config.hpp"
#include "utils.hpp"

#define RANDOM_HEIGHT (OBSTACLE_MIN_HEIGHT + \
	rand() % (SCREEN_HEIGHT - OBSTACLE_VGAP - 2*OBSTACLE_MIN_HEIGHT))


// make sure the members appear in the initializer list in the same order as they appear in the class
// resources taken from http://lanica.co/flappy-clone/
World::World(SDL_Renderer *renderer, SDL_Window *window)
	: background("../assets/night_bg.png", renderer),
	  player("../assets/black-bubble.png", renderer, 140, 140),
	  scoreView("../assets/CourierNew.ttf", renderer, 175,15)
{
	for (int i = 0; i < OBSTACLE_COUNT; i++){
		obstacles[i] = new Obstacle(800+i*OBSTACLE_HGAP, 0, 100, RANDOM_HEIGHT,
				"../assets/top_pipe.png", "../assets/bottom_pipe.png", renderer);
	}
	worldRenderer = renderer;
	worldWindow = window;
}

World::~World()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++){
		delete obstacles[i];
	}
	World::stop();
}

int World::start()
{
	bool quit = false;
	player.setScore(0);

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
					for (int i = 0; i < OBSTACLE_COUNT; i++){
						obstacles[i]->resetPositions();						
					}
					player.setScore(0);
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

	if (detectCollision())
	{
		player.die();
	}

	updateBackground();
	updateObstacles();
	updatePlayer();

	SDL_RenderPresent(worldRenderer);
	SDL_Delay( LOOP_DELAY ); // TODO need better delay

	return quit;
}

bool World::detectCollision()
{
	return World::detectBoundaryCollision() || World::detectCollisionWithObstacles();
}

bool World::detectBoundaryCollision()
{
	bool result = false;
	// TODO only checking bountry at the moment, need to collision detection for other objects
	if (player.getPosY() <= -5 || player.getPosY() >= SCREEN_HEIGHT - player.getHeight() + 5)
	{
		if (DEBUG) debug("world collided! [posY:%d]", player.getPosY());
		result = true;
	}
	return result;
}

bool World::detectCollisionWithObstacles()
{
	// Just detect if player is in the gap of the current obstacle or not.
	bool result = false;
	for (int i=0; i<OBSTACLE_COUNT; i++)
	{
		result = detectCollisionWithObstacle(obstacles[i]);
		if (result)
		{
			break;
		}	
	}
	return result;
}

bool World::detectCollisionWithObstacle(Obstacle *obstacle)
{
	bool result = false;
	SDL_Rect collisionRects[2] = {obstacle->getTopRect(), obstacle->getBotRect()};
	int numberOfRects = sizeof(collisionRects)/sizeof(SDL_Rect);
	for (int i=0; i<numberOfRects; i++)
	{
		SDL_Rect rect = collisionRects[i];
		result = detectCollisionWithRect(rect);
		if (result)
		{
			break;
		}
	}
	return result;
}

bool World::detectCollisionWithRect(SDL_Rect rect)
{
	return check_collision(player.getRect(), rect);

}

void World::stop()
{
	close(worldWindow, worldRenderer);
}

void World::updateBackground()
{
	if (!player.isDead()) {
		if (background.getPosX() <= -background.getWidth())
		{
			if (DEBUG) debug("resetting background posX [x:%d,w:%d]", background.getPosX(), background.getWidth());
			background.setPosX(0);
		}

		background.setPosX(background.getPosX()-BACKGROUND_VELOCITY);
	}

	// Draw the position of bg1 and p1
	int old_x = background.getPosX();
	background.render();
	background.setPosX(background.getPosX() + background.getWidth());
	background.render();
	background.setPosX(background.getPosX()+2*background.getWidth());
	background.render();
	background.setPosX(old_x);

}

void World::updatePlayer()
{
	player.updatePosition();
	player.render();
	updatePlayerScoreIfNeeded();
}

void World::updateObstacles()
{
	if (player.isDead() && player.hasJumped())
	{
		for (int i = 0; i < OBSTACLE_COUNT; i++){
			obstacles[i]->render();
		}
	}
	else if (!player.hasJumped())
	{
		// If game has not yet started, no need to do anything with obstacles as we are not showing them on screen.
		return;
	}
	else
	{
		for (int i = 0; i < OBSTACLE_COUNT; i++){
			obstacles[i]->render();
			obstacles[i]->setPosX(obstacles[i]->getPosX()-OBSTACLE_VELOCITY);
			if (obstacles[i]->getPosX() <= -obstacles[i]->getWidth()){
				obstacles[i]->setHasBeenPassed(false);
				obstacles[i]->setPosX(300+((OBSTACLE_COUNT-1)*OBSTACLE_HGAP));
				obstacles[i]->setHeight(RANDOM_HEIGHT);
			}
		}
	}
}

void World::updatePlayerScoreIfNeeded()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		if (obstacles[i]->getHasBeenPassed())
		{
			continue;
		}
		else
		{
			if (player.getPosX() > obstacles[i]->getPosX())
			{
				obstacles[i]->setHasBeenPassed(true);
				player.incrementScore();
			}
		}
	}

	// TODO can do better, just hacking it coz i need sleep
	char buffer[16];
	sprintf(buffer, "%d", player.getScore());
	scoreView.setText(buffer);
	scoreView.render();	
}

bool World::check_collision( SDL_Rect A, SDL_Rect B )
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	 //If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

