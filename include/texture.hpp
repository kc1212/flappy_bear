#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "config.hpp"

class Texture {

	public:
		// Getters
		int getWidth() const { return mWidth; }
		int getHeight() const { return mHeight; }
		SDL_Texture* getTexture() const;

		// Setters
		void setWidth(int w) { mWidth = w; }
		void setHeight(int h) { mHeight = h; }
		void resetTexture(const char* path, SDL_Renderer* const renderer);
		void resetFontText(const char* text, SDL_Renderer* const renderer);

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
		bool loadTextureFromFile(const char* path, SDL_Renderer* const renderer);
		bool loadFromRenderedText(const char* string, SDL_Renderer* const renderer);
		void zeroAll();

};

#endif
