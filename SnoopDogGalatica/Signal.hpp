/*
	Flag.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Flag__

class Signal {

private:
	int hit; //0 = no hit, 1 = damage hit, 2 = KO hit

public:
	Signal() {
		this->hit = 0;
	}

	void signalKOHit() {
		this->hit = 2;
	}

	void signalDamageHit() {
		if (this->hit < 2) {
			this->hit = 1;
		}
	}

	bool isDestroyed() {
		return (this->hit == 2);
	}

	bool isDamaged() {
		return (this->hit == 1);
	}

	void resetHitSignal() {
		this->hit = 0;
	}

	void recieveSignals() {}

};