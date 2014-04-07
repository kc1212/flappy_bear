// ultility functions

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <cstdio>
#include <cerrno>
// #include <cstring>

// error macros, taken from zed shaw
#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)


/*
 * show information about renderer driver
 */
void showRenderDriver();

/*
 * starts up SDL, SDL_Image, and creates window
 */
bool init(SDL_Window* &window, SDL_Renderer* &renderer);

/*
 * frees media and shuts down SDL
 */
void close(SDL_Window* &window, SDL_Renderer* &renderer);

#endif
