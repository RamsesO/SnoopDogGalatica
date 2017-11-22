/*
	Missile.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim
	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Missile__

class Missile : public Shape, public Collision {

private:

	const float UTL = 2000.0; //2000 updates to live
	const float UTA = 50.0;  //200 updates to activate
	const int detectionRange = 3000;
	float step;
	float offset;
	float rStep;
	int ttl, activate;
	int target;
	int hostId;
	bool launched;
	char * hostName;

public:
	Missile(int id, int hostId, int numOfVert, char * fileName, float size) :
		Shape(id, numOfVert, fileName, size) {
		this->hostId = hostId;
		ttl = UTL;
		activate = UTA;
		launched = false;
		step = 10;
		offset = 250;

		if (fromMissileSites()) {
			this->target = 0;
		}

		if (hostId == 1) {
			hostName = "Unum Site";
		}
		else if (hostId == 2) {
			hostName = "Secundus Site";
		}
		else {
			hostName = "Warbird";
		}
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

	bool fromWarbird() {
		return hostId == 0;
	}

	bool fromMissileSites() {
		return (hostId == 1 || hostId == 2);
	}

	bool fromUnumSite() {
		return hostId == 1;
	}

	bool fromSecundusSite() {
		return hostId == 2;
	}

	bool hasLaunched() {
		return launched;
	}

	void launch(glm::mat4 objOM) {
		printf("Launching missile... \n");
		printf("Launching missile from %s.\n", hostName);
		spawn(objOM);
		launched = true;
	}

	void spawn(glm::mat4 objOM) {
		float * tempRMValues = (float*)glm::value_ptr(objOM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);

		this->translationMatrix = glm::translate(glm::mat4(), getPosition(objOM));
		offsetForward();
	}

	void detectShip(glm::mat4 warbirdOM, glm::mat4 unumSiteOM, glm::mat4 secundusSiteOM) {
		float distanceBetween = distance(getPosition(warbirdOM), getPosition(unumSiteOM));
		if ((distanceBetween <= detectionRange) && fromUnumSite()) {
			launch(unumSiteOM);
		}

		distanceBetween = distance(getPosition(warbirdOM), getPosition(secundusSiteOM));
		if ((distanceBetween <= detectionRange) && fromSecundusSite()) {
			launch(secundusSiteOM);
		}
	}

	int identifyTarget(glm::mat4 unumSiteOM, glm::mat4 secundusSiteOM) {
		//here calculate distance

		glm::vec3 missilePos = getPosition(getOrientationMatrix());
		float disBetweenUSOM = distance(missilePos, getPosition(unumSiteOM));
		float disBetweenSSOM = distance(missilePos, getPosition(secundusSiteOM));

		//needs to be in detection range to be able to choose
		if (disBetweenUSOM <= detectionRange || disBetweenSSOM <= detectionRange) {
			if (disBetweenUSOM > disBetweenSSOM) {
				printf("Chose secundus.\n");
				return 2;
			}
			else {
				printf("Chose unum.\n");
				return 1;
			}
		}
		return -1;
	}

	void translateForward() {
		this->translationMatrix = glm::translate(this->translationMatrix, -step * getOut(this->rotationMatrix));
	}

	void offsetForward() {
		this->translationMatrix = glm::translate(this->translationMatrix, -offset * getOut(this->rotationMatrix));
	}

	void rotateTowards(glm::mat4 shipOM, glm::mat4 unumSiteOM, glm::mat4 secundusSiteOM) {
		glm::vec3 targetPos; //this will be your at
		glm::vec3 missilePos = getPosition(getOrientationMatrix());

		if (target == 0) {
			targetPos = getPosition(shipOM);
		}
		else if (target == 1) {
			targetPos = getPosition(unumSiteOM);
		}
		else {
			targetPos = getPosition(secundusSiteOM);
		}

		//our up vector here might need to be changed
		glm::mat4 tempRM = glm::inverse(glm::lookAt(missilePos, targetPos, glm::vec3(0, 1, 0)));
		float * tempRMValues = (float*)glm::value_ptr(tempRM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);
	}

	void resetMissile() {
		sendToCenter();
		ttl = UTL;
		activate = UTA;
		launched = false;
	}

	void update(glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize, glm::mat4 primusOM,
		float primusSize, glm::mat4 secundusOM, float secundusSize, glm::mat4 unumSiteOM, float unumSiteSize, glm::mat4 secundusSiteOM, 
		float secundusSiteSize, glm::mat4 shipOM, float shipSize) {

		bool diedViaPlanet = false;
		bool diedViaSite = false;
		bool diedViaShip = false;

		if (launched == true) { //if not fired, no action needed

			if (ttl > 0) { //translate all the time if there are time to live remaining
				translateForward();
				if (activate > 0) {
					activate--;//since not activated no rotation 
					if (activate == 0) {//identify target
						step = 100;
						if (fromWarbird()) {
							target = identifyTarget(unumSiteOM, secundusSiteOM);
						}
						else if (fromMissileSites()) {
							target = 0;
						}
					}
				}
				else { //activated
					rotateTowards(shipOM, unumSiteOM, secundusSiteOM);
					ttl--;
				}

				glm::vec3 missilePos = getPosition(this->translationMatrix);
				float missileSize = this->size;

				/*planetCollision(missilePos, missileSize, sunOM, sunSize * 2, unumOM, unumSize - 50, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize - 50);
				diedViaPlanet = isInPContact();
				siteCollision(missilePos, missileSize, unumSiteOM, unumSiteSize, secundusSiteOM, secundusSiteSize);
				diedViaSite = isInSContact();
				warbirdCollision(missilePos, missileSize, shipOM, shipSize - 50);
				diedViaShip = isInWContact();*/
	
				if (diedViaPlanet) {
					printf("missile from %s died via planet hit\n", hostName);
					resetMissile();
				}
				else if (diedViaShip) {
					printf("missile from %s died via hitting warbird\n", hostName);
					resetMissile();
				}
				else if (diedViaSite) {
					printf("missile from %s died via site destruction\n", hostName);
					resetMissile();
				}
			}
			else {
				printf("missile from %s died via distance\n", hostName);
				resetMissile();
			}
		}
		else { //hasnt been fired yet. must check if the ship is detection 
			step = 10;
		}
	}

};