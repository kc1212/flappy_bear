#ifndef _TEXT_VIEW_HPP_
#define _TEXT_VIEW_HPP_

#include "game_entity.hpp"
#include "texture.hpp"

class TextView : public GameEntity {
	public:
		TextView();
		TextView(const char*, SDL_Renderer*, int startX, int startY);
		~TextView();
		void render() const;
		void setText(const char* text);
	private:
		Texture mTexture;
		// char mText[16];
};

#endif
