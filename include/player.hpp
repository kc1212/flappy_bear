// This class represents a player
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "collidable.hpp"

class Player : public Collidable
{
	public:
		void jump();
		void updatePosition();
		void render(SDL_Renderer *renderer);
		void restartGame();
		double getV();
		bool hasJumped();
		// Player();
		Player(const char*, SDL_Renderer*, int, int);
		~Player();
	private:
		void init();
		bool checkCollision();
		void reset();
		double v; // velocity
		double a; // acceleration
		double s; // displacement
		bool jumped;
		bool dead;
};

#endif

