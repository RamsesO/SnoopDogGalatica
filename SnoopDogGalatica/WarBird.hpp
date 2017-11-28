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
	float accel;
	float velocity;
	int time;
	int key; // 1-8 designates the kind of movement

	WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, int missile, int health) :
		Shape(id, numOfVert, fileName, size, translationMatrix), Entity(missile, health), Gravity() {
		this->accel = 1;
		this->rotateBy = 0;
		this->velocity = 0;
		this->time = 0;
		this->key = -1;
	}

	void changeStep() {
		if (accel == 1) {
			accel = 2;
		}
		else if (accel == 2) {
			accel = 3;
		}
		else {
			accel = 1;
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
		bool justDied = onHit();
		if (justDied) {
			sendToCenter();
			printf("Ship has Died.\n");
		}
		resetHitSignal();
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

	void update() {
		if (isDead() == false) {

			if (gravity) {
				setGravDirection();
			}

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