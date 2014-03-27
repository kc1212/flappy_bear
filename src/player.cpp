
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
