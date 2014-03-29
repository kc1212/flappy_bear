// This class represents a player
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "texture.hpp"

class Player : public Texture
{
	public:
		void jump();
		void die();
		void left();

		Player();
		Player(const char*, SDL_Renderer*);
		~Player();
	private:
		double h; // height
		double v; // velocity
		double a; // acceleration

};

#endif

