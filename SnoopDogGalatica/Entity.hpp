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

	//used by missile class
	bool onMissileHit() { 
		if(isInMContact()){ //death of site caused by missile
			if (this->isDead == false) {
				this->health--;
				if (this->health == 0) {
					this->isDead == true;
				}
				return true;
			}
			else {
				printf("Already Dead: hit by missile");
			}
		}
		return false;
	}

	bool onShipHit(){
		return (isInSContact());
	}


	//used by warbird and missile class
	bool onPlanetHit() {
		if (isInPContact()) {
			if (this->isDead == false) {
				this->health = 0;
				this->isDead = true;
				return true;
			}
			else {
				printf("Already Dead: hit by planet");
				return false;
			}
		}
		return false;
	}

	bool isItDead() {
		return this->isDead;
	}


};