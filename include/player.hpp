// This class represents a player
#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

class Player
{
	public:
		void jump();
		void die();
		void left();
		Player(){ h = v = a = 0; };
	private:
		double h; // height
		double v; // velocity
		double a; // acceleration

};

#endif

