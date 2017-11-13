/*
	PlanetCam.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __PLANETCAM__

class PlanetCam {

private:

	glm::vec3 eye, at, up;
	glm::mat4 viewMatrix;

	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
	glm::mat4 rotationMatrix;
	float radians;

public:

	PlanetCam(glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians) {
		this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
		this->rotationAxis = rotationAxis;
		this->radians = radians;

		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::mat4 getCamMatrix(glm::mat4 planetMatrix) {
		glm::mat4 eyeMatrix = this->rotationMatrix * this->translationMatrix;

		float * eyePos = (float*)glm::value_ptr(eyeMatrix);
		this->eye = glm::vec3(eyePos[12], 0.0f, eyePos[14]);

		float * atPos = (float*)glm::value_ptr(planetMatrix);
		this->at = glm::vec3(atPos[12], atPos[13], atPos[14]);

		this->viewMatrix = glm::lookAt(this->eye, this->at, this->up);
		return viewMatrix;
	}

	glm::mat4 getOrientationMatrix(){
		return rotationMatrix * translationMatrix;
	}

	void update() {
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
	}

};