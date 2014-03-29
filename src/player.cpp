
#include "player.hpp"

#include <cstdio>

Player::Player() : Texture()
{
	positionX = positionY = v = a = 0;
}

Player::Player(const char* path, SDL_Renderer* renderer) : Texture(path, renderer)
{
	positionX = positionY = v = a = 0;
}

Player::~Player(){}

void Player::jump(){
	positionY--;
	printf("jumped!, new x:%d, new y:%d\n", positionX,positionY);
}

void Player::die(){
	printf("died!\n");
}

void Player::left()
{
	positionX--;
	printf("go left!, new x:%d, new y:%d\n", positionX,positionY);
}

void Player::right()
{
	positionX++;
	printf("go right!, new x:%d, new y:%d\n", positionX,positionY);
}



