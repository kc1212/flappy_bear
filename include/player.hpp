// This class represents a player
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "texture.hpp"

class Player : public Texture
{
	public:
		void jump();
		void die();
		void updatePosition();

		// Player();
		Player(const char*, SDL_Renderer*, int, int);
		~Player();
	private:
		void init();
		double v; // velocity
		double a; // acceleration
		double s; // displacement
		bool jumped;
};

#endif

