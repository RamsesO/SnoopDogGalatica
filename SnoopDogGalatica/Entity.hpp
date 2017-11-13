/*
	Entity.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Entity__

class Entity {

private:
	int missile;
	int health;
	bool isEnemy;

public:
	Entity(int missile, int health) {
		this->missile = missile;
		this->health = health;
		this->isEnemy = false;
	}

	Entity(int missile, int health, bool isEnemy) {
		this->missile = missile;
		this->health = health;
		this->isEnemy = isEnemy;
	}

	void fire(bool reloading) {
		if (this->missile > 0) {
			if (reloading == false) {
				this->missile--;
				//fire the missile
			}
			else {
				printf("Still Reloading, Please Wait");
			}
		}
		else {
			printf("Out of Ammo!\n");
		}
	}

	void hit() {
		if (this->health > 0) {
			this->health--;
		}
		else {
			printf("Already Dead");
		}
	}

	bool isDead() {
		return (this->health <= 0);
	}

};