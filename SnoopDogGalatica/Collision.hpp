/*
	Collision.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Collision__

class Collision {

private:
	bool pContact;
	bool sContact;
	bool wContact;
	bool mContact;

public:
	Collision() {
		this->pContact = false;
		this->sContact = false;
		this->wContact = false;
		this->mContact = false;
	}

	bool isInPContact() {
		return this->pContact;
	}

	bool isInSContact() {
		return this->sContact;
	}

	bool isInWContact() {
		return this->wContact;
	}

	bool isInMContact() {
		return this->mContact;
	}

	void resetCollisions() {
		this->pContact = false;
		this->sContact = false;
		this->wContact = false;
		this->mContact = false;
	}

	bool colliding(glm::vec3 objPos, float objSize, glm::mat4 targetOM, float targetSize) {
		float distanceBetween = distance(objPos, getPosition(targetOM));
		if (distanceBetween < (targetSize + objSize + 50)) {
			printf("Distance Between: %f \n", distanceBetween);
			printf("Target + Obj Size: %f \n", (targetSize + objSize + 50));
			return true;
		}
		return false;
	}

	void planetCollision(glm::vec3 objPos, float objSize, glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {

		if (colliding(objPos, objSize, sunOM, sunSize) == true) {
			this->pContact = true;
		}
		else if (colliding(objPos, objSize, unumOM, unumSize) == true) {
			this->pContact = true;
		}
		else if (colliding(objPos, objSize, duoOM, duoSize) == true) {
			this->pContact = true;
		}
		else if (colliding(objPos, objSize, primusOM, primusSize) == true) {
			this->pContact = true;
		}
		else if (colliding(objPos, objSize, secundusOM, secundusSize) == true) {
			this->pContact = true;
		}
		else {
			this->pContact = false;
		}
	}

	void siteCollision(glm::vec3 objPos, float objSize, glm::mat4 usOM, float usSize, glm::mat4 ssOM, float ssSize) {
		if (colliding(objPos, objSize, usOM, usSize) == true) {
			this->sContact = true;
		}
		else if (colliding(objPos, objSize, ssOM, ssSize) == true) {
			this->sContact = true;
		}
		else {
			this->sContact = false;
		}
	}

	void warbirdCollision(glm::vec3 objPos, float objSize, glm::mat4 warbirdOM, float warbirdSize) {
		if (colliding(objPos, objSize, warbirdOM, warbirdSize) == true) {
			this->wContact = true;
		}
		else {
			this->wContact = false;
		}
	}

	void missileCollision(glm::vec3 objPos, float objSize, glm::mat4 wbmOM, glm::mat4 usmOM, glm::mat4 ssmOM, float mSize) {
		if (colliding(objPos, objSize, wbmOM, mSize) == true) {
			this->mContact = true;
		}
		else if (colliding(objPos, objSize, usmOM, mSize) == true) {
			this->mContact = true;
		}
		else if (colliding(objPos, objSize, ssmOM, mSize) == true) {
			this->mContact = true;
		}
		else {
			this->mContact = false;
		}
	}

};