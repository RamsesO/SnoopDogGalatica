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

	void setGravDirection(glm::vec3 objPos, float objSize, glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {
		resetGravity();

		//sun
		float distanceBetween = distance(objPos, getPosition(sunOM));
		glm::mat4 gravRM = glm::inverse(glm::lookAt(objPos, getPosition(sunOM), glm::vec3(0, 1, 0)));
		float gravityResult = (-this->gravityConstant * sunSize * objSize) / (distanceBetween * distanceBetween);
		this->gravityVec += gravityResult * getOut(gravRM);

		//unum
		distanceBetween = distance(objPos, getPosition(unumOM));
		gravRM = glm::inverse(glm::lookAt(objPos, getPosition(unumOM), glm::vec3(0, 1, 0)));
		gravityResult = (-this->gravityConstant * unumSize * objSize) / (distanceBetween * distanceBetween);
		this->gravityVec += gravityResult * getOut(gravRM);

		//duo
		distanceBetween = distance(objPos, getPosition(duoOM));
		gravRM = glm::inverse(glm::lookAt(objPos, getPosition(duoOM), glm::vec3(0, 1, 0)));
		gravityResult = (-this->gravityConstant * duoSize * objSize) / (distanceBetween * distanceBetween);
		this->gravityVec += gravityResult * getOut(gravRM);

		//primus
		distanceBetween = distance(objPos, getPosition(primusOM));
		gravRM = glm::inverse(glm::lookAt(objPos, getPosition(primusOM), glm::vec3(0, 1, 0)));
		gravityResult = (-this->gravityConstant * primusSize * objSize) / (distanceBetween * distanceBetween);
		this->gravityVec += gravityResult * getOut(gravRM);

		//secundus
		distanceBetween = distance(objPos, getPosition(secundusOM));
		gravRM = glm::inverse(glm::lookAt(objPos, getPosition(secundusOM), glm::vec3(0, 1, 0)));
		gravityResult = (-this->gravityConstant * secundusSize * objSize) / (distanceBetween * distanceBetween);
		this->gravityVec += gravityResult * getOut(gravRM);

		showVec3("GV", this->gravityVec);
	}

	

};