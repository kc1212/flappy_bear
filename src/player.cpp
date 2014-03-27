
#include "player.hpp"

#include <cstdio>

void player::jump(){
	h++;
	printf("jumped!, new height:%.2f\n", h);
}

void player::die(){
	printf("died!\n");
}

