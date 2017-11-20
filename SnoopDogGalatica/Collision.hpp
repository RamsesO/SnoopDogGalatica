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
	bool mContact;

public:
	Collision() {
		this->pContact = false;
		this->sContact = false;
		this->mContact = false;
	}

	bool isInPContact() {
		return this->pContact;
	}

	bool isInSContact() {
		return this->sContact;
	}

	bool isInMContact() {
		return this->mContact;
	}

	void resetCollisions() {
		this->pContact = false;
		this->sContact = false;
		this->mContact = false;
	}

	bool colliding(glm::vec3 objPos, float objSize, glm::mat4 targetOM, float targetSize) {
		float distanceBetween = distance(objPos, getPosition(targetOM));
		if (distanceBetween < (targetSize + objSize + 50)) {
			return true;
		}
		//printf("distance between sun and obj: %f . sun + obj distance: %f \n", distanceBetween, (sunSize + objSize + 50));
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

};