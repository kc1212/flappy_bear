// This class represents a player
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "texture.hpp"
#include "game_entity.hpp"

class Player : public GameEntity
{
	public:
		// Constructors
		Player(const char* assetPath, SDL_Renderer* renderer, int startX, int startY);
		~Player();

		// Getters
		int getScore(){return mScore;}
		double getV();

		// Setters
		void incrementScore(){mScore++;}
		void setScore(int s){mScore = s;}

		// Methods
		void jump();
		void deathAnimation();
		void updatePosition();
   	void restartGame();
		void die();
    bool isDead();
   	bool hasJumped();
		void render() const;


	private:
		// Instance vars
		double mVelocity;
		double mAcceleration;
		double mDisplacement;
		bool mJumped;
		bool mDead;
		const int mStartX;
		const int mStartY;
		int mScore;
		int mPauseTime;
		Texture mTexture;

		// Methods
		void reset();

};

#endif

