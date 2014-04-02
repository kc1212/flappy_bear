#include "texture.hpp"
#include "background.hpp"
#include "obstacle.hpp"
#include "player.hpp"
#include "utils.hpp"
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
		World(SDL_Renderer *, SDL_Window *);
		/**
		 * Destructor
		 */
		~World();

	private:
		Background background;
		Player player;
		Obstacle obstacle;
		SDL_Renderer* worldRenderer;
		SDL_Window* worldWindow;
		void scrollBackground();
		bool processGameLoop();
		void addObstacles();
};

