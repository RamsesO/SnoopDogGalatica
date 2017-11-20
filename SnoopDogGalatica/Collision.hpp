/*
	Collision.hpp
	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim
	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Collision__

class Collision {

private:
	bool pContact;
	bool sContact;
	bool mContact;
	bool wContact;
	int planetCollisionConstant = 0;
	int siteCollisionConstant = 30;
	int warbirdCollisionConstant = 0;
	int missileCollisionConstant = 40;

public:
	Collision() {
		this->pContact = false;
		this->sContact = false;
		this->mContact = false;
		this->wContact = false;
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

	bool isInWContact(){
		return this->wContact;
	}

	void resetCollisions() {
		this->pContact = false;
		this->sContact = false;
		this->mContact = false;
		this->wContact = false;
	}

	void planetCollision(glm::vec3 objPos, float objSize, glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {

		//sun
		float distanceBetween = distance(objPos, getPosition(sunOM));
		if (distanceBetween < (sunSize + objSize + planetCollisionConstant)) {
			this->pContact = true;
			return;
		}
		//printf("distance between sun and obj: %f . sun + obj distance: %f \n", distanceBetween, (sunSize + objSize + 50));

		//unum
		distanceBetween = distance(objPos, getPosition(unumOM));
		if (distanceBetween < (unumSize + objSize + planetCollisionConstant)) {
			this->pContact = true;
			return;
		}
		//printf("distance between unum and obj: %f . unum + obj distance: %f \n", distanceBetween, (unumSize + objSize + 50));

		//duo
		distanceBetween = distance(objPos, getPosition(duoOM));
		if (distanceBetween < (duoSize + objSize + planetCollisionConstant)) {
			this->pContact = true;
			return;
		}
		//printf("distance between duo and obj: %f . duo + obj distance: %f \n", distanceBetween, (duoSize + objSize + 50));

		//primus
		distanceBetween = distance(objPos, getPosition(primusOM));
		if (distanceBetween < (primusSize + objSize + planetCollisionConstant)) {
			this->pContact = true;
			return;
		}
		//printf("distance between primus and obj: %f . primus + obj distance: %f \n", distanceBetween, (primusSize + objSize + 50));

		//secundus
		distanceBetween = distance(objPos, getPosition(secundusOM));
		if (distanceBetween < (secundusSize + objSize + planetCollisionConstant)) {
			this->pContact = true;
			return;
		}
		//printf("distance between secundus and obj: %f . secundus + obj distance: %f \n", distanceBetween, (secundusSize + objSize + 50));

		this->pContact = false;
		return;
	}

	int missileSiteCollision(glm::vec3 objPos, float objSize, glm::mat4 unumSiteOM, float unumSiteSize, glm::mat4 secundusSiteOM, float secundusSiteSize){
		//unumSite
		float distanceBetween = distance(objPos, getPosition(unumSiteOM));
		if (distanceBetween < (unumSiteSize + objSize + siteCollisionConstant)) {
			this->sContact = true;
			return 0;
		}

		//secundusSite
		distanceBetween = distance(objPos, getPosition(secundusSiteOM));
		if (distanceBetween < (secundusSiteSize + objSize + siteCollisionConstant)) {
			this->sContact = true;
			return 1;
		}

		this->sContact = false;
		return -1;
	}

	void missileCollision(glm::vec3 objPos, float objSize, glm::mat4 unumMissileOM, float unumMissileSize, 
		glm::mat4 secundusMissileOM, float secundusMissileSize){
		float distanceBetween = distance(objPos, getPosition(unumMissileOM));
		if (distanceBetween < (unumMissileSize + objSize + missileCollisionConstant)) {
			this->mContact = true;
			return;
		}

		distanceBetween = distance(objPos, getPosition(secundusMissileOM));
		if (distanceBetween < (secundusMissileSize + objSize + missileCollisionConstant)) {
			this->mContact = true;
			return;
		}

		this->mContact = false;
		return;

	}
	//did obj hit the warbird?
	void warbirdCollision(glm::vec3 objPos, float objSize, glm::mat4 warbirdOM, float warbirdSize){
		float distanceBetween = distance(objPos, getPosition(warbirdOM));
		if (distanceBetween < (warbirdSize + objSize + warbirdCollisionConstant)) {
			this->wContact = true;
			return;
		}
		
		this->wContact = false;
		return;
	}

};