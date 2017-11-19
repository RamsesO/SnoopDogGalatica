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
		return this->pContact; // indicates death by planet
	}

	bool isInSContact() {
		return this->sContact; // indicates death of ship
	}

	bool isInMContact() {
		return this->mContact; // indicates death by missile (unum miss site, sec miss site and warbird will check)
	}

	void resetCollisions() {
		this->pContact = false; 
		this->sContact = false;
		this->mContact = false;
	}
	//this function will be called by missile class causing ship to die.
	void shipCollision(int objId, glm::vec3 objPos, float objSize, glm::mat4 shipOM, float shipSize){
		float distanceBetween = distance(objPos, getPosition(shipOM));
		if(distanceBetween < (shipSize + objSize + 50))
			this->sContact = true;
		return;
	}

	//test of entities' death caused by planet; warbird and missiles,
	//but if warbird missile hits  unum or sec, it will call  mContact = true  indicating missile site's death
	void planetCollision(int objId, glm::vec3 objPos, float objSize, glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {
		/* id
			5 	= warbird
			8	= missile from warbird
			9	= missile from unum site
			10	= missile from secundus site
		*/

		//sun
		float distanceBetween = distance(objPos, getPosition(sunOM));
		if (distanceBetween < (sunSize + objSize + 50)) {
			this->pContact = true;
			return;
		}
		//printf("distance between sun and obj: %f . sun + obj distance: %f \n", distanceBetween, (sunSize + objSize + 50));

		//unum
		distanceBetween = distance(objPos, getPosition(unumOM));
		if (distanceBetween < (unumSize + objSize + 50)) {
			this->pContact = true;
			if(objId == 8)
				this->mContact = true;
			return;
		}
		//printf("distance between unum and obj: %f . unum + obj distance: %f \n", distanceBetween, (unumSize + objSize + 50));

		//duo
		distanceBetween = distance(objPos, getPosition(duoOM));
		if (distanceBetween < (duoSize + objSize + 50)) {
			this->pContact = true;
			return;
		}
		//printf("distance between duo and obj: %f . duo + obj distance: %f \n", distanceBetween, (duoSize + objSize + 50));

		//primus
		distanceBetween = distance(objPos, getPosition(primusOM));
		if (distanceBetween < (primusSize + objSize + 50)) {
			this->pContact = true;
			return;
		}
		//printf("distance between primus and obj: %f . primus + obj distance: %f \n", distanceBetween, (primusSize + objSize + 50));

		//secundus
		distanceBetween = distance(objPos, getPosition(secundusOM));
		if (distanceBetween < (secundusSize + objSize + 50)) {
			this->pContact = true;
			if(objId == 8)
				this->mContact = true;
			return;
		}
		//printf("distance between secundus and obj: %f . secundus + obj distance: %f \n", distanceBetween, (secundusSize + objSize + 50));
	}

};