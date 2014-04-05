#ifndef _BACKGROUND_HPP_
#define _BACKGROUND_HPP_

#include "game_entity.hpp"
#include "texture.hpp"

class Background : public GameEntity {
	public:
		Background();
		Background(const char*, SDL_Renderer*);
		~Background();
		void render() const;
	private:
		bool night;
		Texture mTexture;
};

#endif
