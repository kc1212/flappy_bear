// This class represents a player
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "texture.hpp"

class Player : public Texture
{
	public:
		void jump();
		void updatePosition();
		void render(SDL_Renderer *renderer);
		void restartGame();
		void die();
        bool isDead();
   		bool hasJumped();
		double getV();
		SDL_Rect getPlayerRect();
		int getScore(){return score;}
		void setScore(int s){score = s;}
		void incrementScore(){score++;}

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
		const int startX;
		const int startY;
		int score;
};

#endif

