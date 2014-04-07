#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "config.hpp"

class Texture {

	public:
		// Getters
		int getWidth();
		int getHeight();
		SDL_Texture* getTexture() const;

		// Setters
		void setWidth(int w);
		void setHeight(int h);
		void resetTexture(const char*, SDL_Renderer*);
		
		/**
		 * Default constructor.
		 */
		Texture();

		/**
		 * Construct a texture with an asset.
		 * @param path The file path to the asset or the text to be rendered.
		 * @param renderer The renderer to render the asset.
		 * @param True if the texture it rendering an image asset, false if rendering text.
		 */
		Texture(const char* path, SDL_Renderer* renderer, bool isImage);

		/**
		 * Deallocates the object
		 */
		~Texture();

	protected:
		SDL_Texture* mTexture;
		char mFilename[MAX_PATH_LEN];
		int mWidth, mHeight;
		TTF_Font* mFont;
		// Height and width for the texture.

	private:
		const bool mIsImage;
		bool loadTextureFromFile(const char* path, SDL_Renderer* renderer);
		bool loadFromRenderedText(const char* string, SDL_Renderer* renderer);
		void zeroAll();

};

#endif
