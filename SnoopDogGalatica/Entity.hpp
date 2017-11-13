/*
MissileSite.hpp

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
	bool isDead;

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



};