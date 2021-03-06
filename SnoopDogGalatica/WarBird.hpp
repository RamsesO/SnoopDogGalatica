/*
	WarBird.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __WarBird__

class WarBird : public Shape, public Entity, public Gravity {

public:

	const float rotateRadians = 0.05f;
	float rotateBy;
	float velocity;
	float time;
	int accel;
	int key; // 1-8 designates the kind of movement

	bool unumEntered;
	bool secundusEntered;

	WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, int missile, int health) :
		Shape(id, numOfVert, fileName, size, translationMatrix), Entity(missile, health), Gravity() {
		this->accel = 2;
		this->rotateBy = 0;
		this->velocity = 0;
		this->time = 0;
		this->key = -1;

		this->unumEntered = false;
		this->secundusEntered = false;
	}

	void changeStep() {
		switch (accel) {
			case 2:
				this->accel = 4;
				break;
			case 4:
				this->accel = 6;
				break;
			case 6:
				this->accel = 2;
				break;
		}
	}

	void movement(int i) {
		key = i;
	}

	void move() {
		velocity = accel * (time);
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, (velocity * getOut(this->rotationMatrix)) + this->gravityVec);
		else
			this->translationMatrix = glm::translate(this->translationMatrix, (velocity * getOut(this->rotationMatrix)));

		if (time > 0) time -= 0.25;
		else if (time < 0) time += 0.25;
	}

	void accelForward() {
		time--;
	}

	void accelBackward() {
		time++;
	}

	void yawLeft() {
		rotateBy = rotateRadians;
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0, 1, 0));
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, this->gravityVec);
	}

	void yawRight() {
		rotateBy = -rotateRadians;
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0, 1, 0));
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, this->gravityVec);
	}

	void pitchUp() {
		rotateBy = rotateRadians;
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(1, 0, 0));
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, this->gravityVec);
	}

	void pitchDown() {
		rotateBy = -rotateRadians;
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(1, 0, 0));
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, this->gravityVec);
	}

	void rollLeft() {
		rotateBy = rotateRadians;
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0, 0, 1));
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, this->gravityVec);
	}

	void rollRight() {
		rotateBy = -rotateRadians;
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0, 0, 1));
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, this->gravityVec);
	}

	void warpTo(glm::mat4 planetCamOM, glm::mat4 planetOM) {
		this->time = 0;

		this->translationMatrix = glm::translate(glm::mat4(), getPosition(planetCamOM));
		glm::vec3 pos = getPosition(this->translationMatrix);
		glm::vec3 at = getPosition(planetOM);

		glm::mat4 tempRM = glm::inverse(glm::lookAt(getPosition(planetCamOM), at, glm::vec3(0, 1, 0)));
		float *tempRMValues = (float*)glm::value_ptr(tempRM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

	void recieveSignals() {
		if (isDead() == false) {
			bool justDied = onHit();
			if (justDied) {
				sendToCenter();
				printf("Ship has Died.\n");
			}
			resetHitSignal();
		}
	}

	void appendGravVec(glm::vec3 targetPos, float targetSize) {
		this->tempGravity += calculateGrav(getPosition(getOrientationMatrix()), this->size, targetPos, targetSize);
	}

	bool isColliding(glm::vec3 targetPos, float targetSize) {
		float distanceBetween = distance(getPosition(getOrientationMatrix()), targetPos);
		if (distanceBetween < (targetSize + this->size - 50)) {
			return true;
		}
		return false;
	}

	void update(MissileSite *unumSite, glm::vec3 unumSitePos, MissileSite *secundusSite, glm::vec3 secundusSitePos) {
		if (isDead() == false) {
			glm::vec3 warbirdPos = getPosition(getOrientationMatrix());
			float warbirdSize = this->size;

			//UnumSite Interactions
			if (unumSite->isDead() == false) {
				if (unumSite->isColliding(unumSitePos, warbirdPos, warbirdSize)) {
					printf("Warbird crashed into Unum Site.\n");
					signalKOHit();
					unumSite->signalKOHit();
				}
				if (unumSite->isColliding(unumSitePos, warbirdPos, warbirdSize + unumSite->DETECT_RANGE)) {
					if (unumEntered == false) {
						printf("Warbird has entered Unum Site's Detection Range.\n");
						unumEntered = true;
					}
					unumSite->signalDetected();
				}
				else {
					if (unumEntered == true) {
						printf("Warbird has exited Unum Site's Detection Range.\n");
						unumEntered = false;
					}
					unumSite->resetDetectedSignal();
				}
			}

			//SecundusSite Interactions
			if (secundusSite->isDead() == false) {
				if (secundusSite->isColliding(secundusSitePos, warbirdPos, warbirdSize)) {
					printf("Warbird crashed into Secundus Site.\n");
					signalKOHit();
					secundusSite->signalKOHit();
				}
				if (secundusSite->isColliding(secundusSitePos, warbirdPos, warbirdSize + secundusSite->DETECT_RANGE)) {
					if (secundusEntered == false) {
						printf("Warbird has entered Secundus Site's Detection Range.\n");
						secundusEntered = true;
					}
					secundusSite->signalDetected();
				}
				else {
					if (secundusEntered == true) {
						printf("Warbird has exited Secundus Site's Detection Range.\n");
						secundusEntered = false;
					}
					secundusSite->resetDetectedSignal();
				}
			}


			//Set gravity
			if (gravity) {
				setGravDirection();
			}

			//Ship movement
			move();
			switch (key) {
				case 0:
					accelForward();
					break;
				case 1:
					accelBackward();
					break;
				case 2:
					yawLeft();
					break;
				case 3:
					yawRight();
					break;
				case 4:
					pitchDown();
					break;
				case 5:
					pitchUp();
					break;
				case 6:
					rollLeft();
					break;
				case 7:
					rollRight();
					break;
				default:
					this->translationMatrix = glm::translate(this->translationMatrix, gravityVec);
					break;
			}
			key = -1;
		}
	}

};