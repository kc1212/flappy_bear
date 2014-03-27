// This class represents a player
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

