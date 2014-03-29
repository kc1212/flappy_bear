
#include "player.hpp"

#include <cstdio>

void Player::jump(){
	h++;
	printf("jumped!, new height:%.2f\n", h);
}

void Player::die(){
	printf("died!\n");
}

void Player::left()
{
	printf("go left\n");
}

Player::Player() : Texture()
{
	h = v = a = 0;
}

Player::Player(const char* path, SDL_Renderer* renderer) : Texture(path, renderer)
{
	h = v = a = 0;
}

Player::~Player(){}


