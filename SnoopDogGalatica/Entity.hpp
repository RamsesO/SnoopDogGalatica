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

class Entity : public Signal, public Collision {

private:
	int missile;
	int health;
	bool enemy;
	bool dead;

public:
	Entity(int missile, int health) : Signal(), Collision() {
		this->missile = missile;
		this->health = health;
		this->enemy = false;
		this->dead = false;
	}

	Entity(int missile, int health, bool isEnemy) : Signal(), Collision() {
		this->missile = missile;
		this->health = health;
		this->enemy = isEnemy;
		this->dead = false;
	}

	bool isDead() {
		return this->dead;
	}

	int getMissileCount() {
		return missile;
	}

	bool fire(bool launched) { 
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

	bool onHitDamage() {
		if (this->dead == false) {
			this->health--;
			if (this->health == 0) {
				this->dead = true;
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

	bool onHitKO() {
		if (this->dead == false) {
			this->health = 0;
			this->dead = true;
			return true;
		}
		else {
			return false;
		}
	}

	bool onHit() {
		if (isDamaged() == true) {
			return onHitDamage();
		}
		else if (isDestroyed() == true) {
			return onHitKO();
		}
		else {
			return false;
		}
	}

};