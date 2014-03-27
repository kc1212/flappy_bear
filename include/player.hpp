// This class represents a player
class player {
	public:
		void jump();
		void die();
		player(){ h = v = a = 0; };
	private:
		double h; // height
		double v; // velocity
		double a; // acceleration
};

