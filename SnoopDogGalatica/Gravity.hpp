/*
	Gravity.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Gravity__

class Gravity {

public:
	glm::vec3 tempGravity;
	glm::vec3 gravityVec;
	bool gravity;
	float gravityConstant;

	Gravity() {
		this->tempGravity = glm::vec3(0, 0, 0);
		this->gravityVec = glm::vec3(0, 0, 0);
		this->gravity = false;
		this->gravityConstant = 0;
	}

	void resetGravityVec() {
		this->gravityVec = glm::vec3(0, 0, 0);
	}

	void resetTempGravityVec() {
		this->tempGravity = glm::vec3(0, 0, 0);
	}

	void setGravityConst(float constant) {
		this->gravityConstant = constant;
	}

	void toggleGravity() {
		resetTempGravityVec();
		this->gravity = !this->gravity;
		if (!this->gravity) {
			resetGravityVec();
		}
	}

	glm::vec3 calculateGrav(glm::vec3 objPos, float objSize, glm::vec3 targetPos, float targetSize) {
		float distanceBetween = distance(objPos, targetPos);
		glm::mat4 gravRM = glm::inverse(glm::lookAt(objPos, targetPos, glm::vec3(0, 1, 0)));
		float gravityResult = (-this->gravityConstant * targetSize * objSize) / (distanceBetween * distanceBetween);
		return (gravityResult * getOut(gravRM));
	}

	void appendGravVec(glm::vec3 objPos, float objSize, glm::vec3 targetPos, float targetSize) {
		this->tempGravity += calculateGrav(objPos, objSize, targetPos, targetSize);
	}

	void setGravDirection() {
		resetGravityVec();
		this->gravityVec = tempGravity;
		//showVec3("GV", this->gravityVec);
		resetTempGravityVec();
	}

};