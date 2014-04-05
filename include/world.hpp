#include "background.hpp"
#include "obstacle.hpp"
#include "player.hpp"
#include "SDL2/SDL.h"

/**
  * This class represents the world
  */
class World {
	public:

		/**
		  * Starts the world.
		  */
		int start();

		/**
		  * Stops the world.
		  */
		void stop();
		/**
		  * Detects whether there has been a collision somewhere in the world.
		  * @return true if there has been a collision, false otherwise.
		  */
        bool detectCollision();
        /**
		 * Constructor
         */
		World(SDL_Renderer*, SDL_Window*);
		/**
		 * Destructor
		 */
		~World();

	private:
		Background background;
		Player player;
		Obstacle* obstacles[OBSTACLE_COUNT];
		SDL_Renderer* worldRenderer;
		SDL_Window* worldWindow;
		bool processGameLoop();
		void updateBackground();
		void updatePlayer();
		void updateObstacles();
		bool detectBoundaryCollision();
		bool detectCollisionWithObstacles();
		bool detectCollisionWithObstacle(Obstacle *obstacle); 
		bool detectCollisionWithRect(SDL_Rect rect);
		void updatePlayerScoreIfNeeded();
		bool check_collision( SDL_Rect A, SDL_Rect B );
};

