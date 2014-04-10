#ifndef _OBSTACLES_HPP_
#define _OBSTACLES_HPP_

#include "texture.hpp"
#include "game_entity.hpp"

// TODO this class doesn't subclass from Texture. But it should subclass something in common with player, maybe create a entity class to contain all the posx,posy,w,h in entity and keep the renderering code in Texture.
// and have player multiple inherit from Texture and Entity.

class Obstacle : public GameEntity
{
	public:
		// Initiation
		Obstacle();
		Obstacle(int x, int y, int w, int h, const char* topAssetPath, const char* botAssetPath, SDL_Renderer*);
		virtual ~Obstacle();

		// Getters
		bool getHasBeenPassed() {return mHasBeenPassed;}
		SDL_Rect getTopRect();
		SDL_Rect getBotRect();

		// Setters
		void setPositions(int x, int y, int w, int h);
		void setHasBeenPassed(bool passed){mHasBeenPassed = passed;}
		void setPosX(int x);
		void setPosY(int y);
		void resetPositions();
		void randomisePosY();

		// Methods
		void render() const;

	private:
		bool mHasBeenPassed;
		// mRect is mTopRect
		SDL_Rect mBotRect;
		const SDL_Rect mStartRect;
		Texture mTopTexture;
		Texture mBotTexture;
};

#endif




