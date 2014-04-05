#include "world.hpp"
#include "config.hpp"
#include "utils.hpp"

#define RANDOM_HEIGHT (OBSTACLE_MIN_HEIGHT + \
	rand() % (SCREEN_HEIGHT - OBSTACLE_VGAP - 2*OBSTACLE_MIN_HEIGHT))

bool check_collision( SDL_Rect A, SDL_Rect B );

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
		if (DEBUG) printf("***collided!\tposY: %d\n", player.getPosY());
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
		result = detectCollisionWithObstacle(&obstacles[i]);
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
	return check_collision(player.getPlayerRect(), rect);

}

// make sure the members appear in the initializer list in the same order as they appear in the class
// resources taken from http://lanica.co/flappy-clone/
World::World(SDL_Renderer *renderer, SDL_Window *window)
	: background("../assets/night_bg.png", renderer),
	  player("../assets/black-bubble.png", renderer, 140, 140)
{
	for (int i = 0; i < OBSTACLE_COUNT; i++){
		obstacles[i].setTexture("../assets/top_pipe.png", "../assets/bottom_pipe.png", renderer);
		obstacles[i].setPositions(800+i*OBSTACLE_HGAP,0,100,200);
		obstacles[i].setHeight(RANDOM_HEIGHT);
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

void World::updateBackground()
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
			obstacles[i].render(worldRenderer);
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
			obstacles[i].render(worldRenderer);
			obstacles[i].setPosX(obstacles[i].getPosX()-OBSTACLE_VELOCITY);
			if (obstacles[i].getPosX() <= -obstacles[i].getWidth()){
				obstacles[i].setHasBeenPassed(false);
				obstacles[i].setPosX(300+((OBSTACLE_COUNT-1)*OBSTACLE_HGAP));
				obstacles[i].setHeight(RANDOM_HEIGHT);
			}
		}
	}
}

void World::updatePlayerScoreIfNeeded()
{
 	for (auto &obstacle : obstacles)
	{
		if (obstacle.getHasBeenPassed())
		{
			continue;
		}
		else 
		{
			if (player.getPosX() > obstacle.getPosX())
			{
				obstacle.setHasBeenPassed(true);
				player.incrementScore();
			}
		}
	}
}

bool check_collision( SDL_Rect A, SDL_Rect B )
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

