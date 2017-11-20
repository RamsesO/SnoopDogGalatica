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

class Entity : public Collision {

private:
	int missile;
	int health;
	bool isEnemy;
	bool isDead;

public:
	Entity(int missile, int health) {
		this->missile = missile;
		this->health = health;
		this->isEnemy = false;
		this->isDead = false;
	}

	Entity(int missile, int health, bool isEnemy) {
		this->missile = missile;
		this->health = health;
		this->isEnemy = isEnemy;
		this->isDead = false;
	}

	int getMissileCount() {
		return missile;
	}

	bool fire(bool launched) { //returns true if fired
		if (this->missile > 0) {
			if (launched == false) {
				this->missile--;
				return true;
			}
			else {
				printf("Still Reloading, Please Wait.\n");
				return false;
			}
		}
		else {
			printf("Out of Ammo!\n");
			return false;
		}
	}

	bool onMissileHit() {
		if (this->isDead == false) {
			printf("Hit by missile.");
			this->health--;
			if (this->health == 0) {
				this->isDead == true;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	bool oneHitKO() {
		if (this->isDead == false) {
			this->health = 0;
			this->isDead = true;
			return true;
		}
		else {
			return false;
		}
	}

	bool onPlanetHit() {
		if (isInPContact()) {
			return oneHitKO();
		}
		return false;
	}

	bool onSiteHit() {
		if (isInSContact()) {
			return oneHitKO();
		}
		return false;
	}

	bool onWarbirdHit() {
		if (isInWContact()) {
			return oneHitKO();
		}
		return false;
	}

	bool isItDead() {
		return this->isDead;
	}


};