/*
	Planet.hpp

	Lemuel Dizon
	Ramses Ordonez
	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __WarBirdCam__

class WarBirdCam {

private:

	glm::vec3 eye, at, up;
	glm::mat4 viewMatrix;

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	float radians;

public:

	WarBirdCam(glm::vec3 eyeMatrix, glm::vec3 AtMatrix, float radians) {
		//this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
		this->radians = radians;

		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::mat4 getCamMatrix(glm::mat4 warbirdMatrix) {
		glm::mat4 eyeMatrix = this->rotationMatrix * this->translationMatrix;
		float * eyePos = (float*)glm::value_ptr(eyeMatrix);
		this->eye = glm::vec3(eyePos[12], 0.0f, eyePos[14]);

		float * atPos = (float*)glm::value_ptr(warbirdMatrix);
		this->at = glm::vec3(atPos[12], atPos[13], atPos[14]);

		this->viewMatrix = glm::lookAt(this->eye, this->at, this->up);
		return viewMatrix;
	}

	// +/-
	void updateRadians(float modifiedRadians){
		this->radians += modifiedRadians;
	}


};