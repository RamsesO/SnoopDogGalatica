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

class Missile : public Shape, public Collision, public Signal, public Gravity {

private:

	//Timers
	const float ACTIVATE_TIME = 200.0;
	const float LIFE_TIME = 2000.0;
	const float ON_TIME = 10.0;
	int time;

	//Movement
	float step;
	float offset;
	float rStep;

	//Other
	const float DETECT_RANGE = 3000;
	char *hostName;
	bool launched;
	int target;
	int hostId;

public:
	Missile(int id, int hostId, int numOfVert, char * fileName, float size) :
		Shape(id, numOfVert, fileName, size), Collision(), Signal(), Gravity() {
		this->hostId = hostId;
		this->time = 0;
		this->launched = false;
		this->step = 10;
		this->offset = 250;

		if (fromMissileSites()) {
			this->target = 0;
		}

		if (hostId == 1) 
			this->hostName = "Unum Site";
		else if (hostId == 2) 
			this->hostName = "Secundus Site";
		else 
			this->hostName = "Warbird";
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

	char *getHostName() {
		return hostName;
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

	void offsetForward() {
		this->translationMatrix = glm::translate(this->translationMatrix, -offset * getOut(this->rotationMatrix));
	}

	void spawn(glm::mat4 objOM) {
		float * tempRMValues = (float*)glm::value_ptr(objOM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);

		this->translationMatrix = glm::translate(glm::mat4(), getPosition(objOM));
		offsetForward();
	}

	void launch(glm::mat4 objOM) {
		printf("Launching missile... \n");
		printf("Launching missile from %s.\n", hostName);
		spawn(objOM);
		launched = true;
	}

	int identifyTarget(MissileSite *unumSite, glm::mat4 unumSiteOM, MissileSite *secundusSite, glm::mat4 secundusSiteOM) {
		//here calculate distance
		glm::vec3 missilePos = getPosition(getOrientationMatrix());
		float disUnumSiteOM = distance(missilePos, getPosition(unumSiteOM));
		float disSecundusSiteOM = distance(missilePos, getPosition(secundusSiteOM));

		//needs to be in detection range to be able to choose
		if (disUnumSiteOM <= DETECT_RANGE || disSecundusSiteOM <= DETECT_RANGE) {
			if ((disUnumSiteOM < disSecundusSiteOM) && unumSite->isDead() == false) {
				printf("Chose Unum Site.\n");
				return 1;
			}
			else if ((disSecundusSiteOM < disUnumSiteOM) && secundusSite->isDead() == false) {
				printf("Chose Secundus Site.\n");
				return 2;
			}
		}
		printf("No targets in range, %s missile tracking turned off.\n", hostName);
		return -1;
	}

	void translateForward() {
		if (gravity && (this->time > ACTIVATE_TIME)) {
			this->translationMatrix = glm::translate(this->translationMatrix, (-step * getOut(this->rotationMatrix)) + this->gravityVec);
		}
		else {
			this->translationMatrix = glm::translate(this->translationMatrix, (-step * getOut(this->rotationMatrix)) );
		}
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
		else if (target == 2) {
			targetPos = getPosition(secundusSiteOM);
		}
		else {
			return;
		}

		//our up vector here might need to be changed
		glm::mat4 tempRM = glm::inverse(glm::lookAt(missilePos, targetPos, glm::vec3(0, 1, 0)));
		float * tempRMValues = (float*)glm::value_ptr(tempRM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);
	}

	void resetMissile() {
		sendToCenter();
		this->time = 0;
		this->launched = false;
	}

	void appendGravVec(glm::vec3 targetPos, float targetSize) {
		this->tempGravity += calculateGrav(getPosition(getOrientationMatrix()), this->size, targetPos, targetSize);
	}

	bool isColliding(glm::vec3 targetPos, float targetSize) {
		float distanceBetween = distance(getPosition(getOrientationMatrix()), targetPos);
		if (distanceBetween < (targetSize + this->size + 50)) {
			return true;
		}
		return false;
	}

	void recieveSignals(MissileSite *unumSite, glm::mat4 unumSiteOM, MissileSite *secundusSite, glm::mat4 secundusSiteOM) {
		if (this->launched == true) {
			if (isDestroyed() == true) {
				resetMissile();
				printf("%s missile has Died.\n", hostName);
			}
			resetHitSignal();
		}
		else {
			if (fromUnumSite() && unumSite->isDead() == false) {
				if (unumSite->isDetected() == true) {
					bool justFired = unumSite->fire(hasLaunched());
					if (justFired == true) {
						printf("%s missile has fired.\n", hostName);
						launch(unumSiteOM);
					}
					unumSite->resetDetectedSignal();
				}
			}
			else if (fromSecundusSite() && secundusSite->isDead() == false) {
				if (secundusSite->isDetected() == true) {
					bool justFired = secundusSite->fire(hasLaunched());
					if (justFired == true) {
						printf("%s missile has fired.\n", hostName);
						launch(secundusSiteOM);
					}
					secundusSite->resetDetectedSignal();
				}
			}
		}
	}

	void update(WarBird *warbird, MissileSite *unumSite, glm::mat4 unumSiteOM, MissileSite *secundusSite, glm::mat4 secundusSiteOM, Missile *m1, Missile *m2) {

		if (this->launched == true) { //if not fired, no action needed

			if (this->time < LIFE_TIME) { //If missile is alive

				//Missile Movement
				translateForward();
				if (this->time == ACTIVATE_TIME) {
					this->step = 50;
					if (fromWarbird()) {
						this->target = identifyTarget(unumSite, unumSiteOM, secundusSite, secundusSiteOM);
					}
					else if (fromMissileSites()) {
						if (warbird->isDead() == false) {
							this->target = 0;
						}
						else {
							printf("No targets in range, %s missile tracking turned off.\n", hostName);
							this->target = -1;
						}
					}
				}
				else if (this->time > ACTIVATE_TIME) {
					rotateTowards(warbird->getOrientationMatrix(), unumSiteOM, secundusSiteOM);
				}
				this->time++;

				//Set gravity
				if (gravity && (this->time > ACTIVATE_TIME)) {
					setGravDirection();
				}

				//Collision Check
				if (this->time > ON_TIME) {
					glm::vec3 missilePos = getPosition(this->translationMatrix);
					float missileSize = this->size;

					//Warbird
					if (warbird->isDead() == false && warbird->isColliding(missilePos, missileSize)) {
						printf("%s missile hit Warbird.\n", hostName);
						signalKOHit();
						warbird->signalDamageHit();
					}

					//Sites
					if (unumSite->isDead() == false && unumSite->isColliding(getPosition(unumSiteOM), missilePos, missileSize)) {
						printf("%s missile hit Unum Site.\n", hostName);
						signalKOHit();
						unumSite->signalDamageHit();
					}
					if (secundusSite->isDead() == false && secundusSite->isColliding(getPosition(secundusSiteOM), missilePos, missileSize)) {
						printf("%s missile hit Secundus Site.\n", hostName);
						signalKOHit();
						secundusSite->signalDamageHit();
					}

					//Other Missiles
					if (m1->hasLaunched() == true && m1->isColliding(missilePos, missileSize)) {
						printf("%s missile hit %s missile.\n", hostName, m1->hostName);
						signalKOHit();
						m1->signalKOHit();
					}
					if (m2->hasLaunched() == true && m2->isColliding(missilePos, missileSize)) {
						printf("%s missile hit %s missile.\n", hostName, m2->hostName);
						signalKOHit();
						m2->signalKOHit();
					}
				}

			}
			else {
				printf("%s missile ran out of fuel. Died.\n", hostName);
				resetMissile();
			}

		}
		else { //hasnt been fired yet. must check if the ship is detection 
			this->step = 10;
		}
	}

};