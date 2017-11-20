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
	glm::vec3 gravityVec;
	bool gravity;
	float gravityConstant;

	Gravity() {
		this->gravityVec = glm::vec3(0, 0, 0);
		this->gravity = false;
		this->gravityConstant = 0;
	}

	void resetGravity() {
		this->gravityVec = glm::vec3(0, 0, 0);
	}

	void setGravityConst(float constant) {
		this->gravityConstant = constant;
	}

	void toggleGravity() {
		this->gravity = !this->gravity;
		if (!this->gravity) {
			resetGravity();
		}
	}

	glm::vec3 calculateGrav(glm::vec3 objPos, float objSize, glm::mat4 targetOM, float targetSize) {
		float distanceBetween = distance(objPos, getPosition(targetOM));
		glm::mat4 gravRM = glm::inverse(glm::lookAt(objPos, getPosition(targetOM), glm::vec3(0, 1, 0)));
		float gravityResult = (-this->gravityConstant * targetSize * objSize) / (distanceBetween * distanceBetween);
		return (gravityResult * getOut(gravRM));
	}

	void setGravDirection(glm::vec3 objPos, float objSize, glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {
		resetGravity();

		this->gravityVec += calculateGrav(objPos, objSize, sunOM, sunSize);
		this->gravityVec += calculateGrav(objPos, objSize, unumOM, unumSize);
		this->gravityVec += calculateGrav(objPos, objSize, duoOM, duoSize);
		this->gravityVec += calculateGrav(objPos, objSize, primusOM, primusSize);
		this->gravityVec += calculateGrav(objPos, objSize, secundusOM, secundusSize);

		showVec3("GV", this->gravityVec);
	}

};