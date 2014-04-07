#ifndef _TEXT_VIEW_HPP_
#define _TEXT_VIEW_HPP_

#include "game_entity.hpp"
#include "texture.hpp"

class TextView : public GameEntity {
	public:
		TextView();
		TextView(const char*, SDL_Renderer*);
		~TextView();
		void render() const;
	private:
		Texture mTexture;
};

#endif
