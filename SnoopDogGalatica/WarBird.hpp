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
	float step;
	int key; // 1-8 designates the kind of movement


	WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, int missile, int health) :
		Shape(id, numOfVert, fileName, size, translationMatrix), Entity(missile, health), Gravity() {
		this->step = 10;
		this->rotateBy = 0;
		this->key = -1;
	}

	void changeStep() {
		if (step == 10) {
			step = 50;
		}
		else if (step == 50) {
			step = 100;
		}
		else {
			step = 10;
		}
	}

	void movement(int i) {
		key = i;
	}

	void moveForward() {
		if (gravity) {
			this->translationMatrix = glm::translate(this->translationMatrix, (-step * getOut(this->rotationMatrix)) + this->gravityVec);
		}
		else
			this->translationMatrix = glm::translate(this->translationMatrix, (-step * getOut(this->rotationMatrix)));
	}

	void moveBackward() {
		if (gravity)
			this->translationMatrix = glm::translate(this->translationMatrix, (step * getOut(this->rotationMatrix)) + this->gravityVec);
		else
			this->translationMatrix = glm::translate(this->translationMatrix, (step * getOut(this->rotationMatrix)));
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
		this->translationMatrix = glm::translate(glm::mat4(), getPosition(planetCamOM));
		glm::vec3 pos = getPosition(this->translationMatrix);
		glm::vec3 at = getPosition(planetOM);

		glm::mat4 tempRM = glm::inverse(glm::lookAt(getPosition(planetCamOM), at, glm::vec3(0, 1, 0)));
		float * tempRMValues = (float*)glm::value_ptr(tempRM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);

	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

	void update(glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {

		if(isItDead()){
			printf("ship is dead \n");
			return;
		}

		glm::vec3 shipPos = getPosition(this->translationMatrix);
		if (gravity) {
			setGravDirection(shipPos, this->size, sunOM, sunSize, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize);
		}
		
		planetCollision(shipPos, this->size, sunOM, sunSize * 2, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize);
		bool justDied = onPlanetHit();
		if (justDied) sendToCenter();

		switch (key) {
			case 0:
				moveForward();
				break;
			case 1:
				moveBackward();
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

};