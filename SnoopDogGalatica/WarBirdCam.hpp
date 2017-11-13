/*
	WarbirdCam.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __WarBirdCam__

class WarBirdCam {

private:

	glm::vec3 eye, at, up;
	glm::mat4 viewMatrix;

	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;

public:

	WarBirdCam(glm::vec3 translationMatrix) {
		this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
	}

	glm::mat4 getCamMatrix(glm::mat4 warbirdOrientationMatrix) {

		glm::mat4 camMatrix = warbirdOrientationMatrix * this->translationMatrix;
		glm::mat4 atMatrix = warbirdOrientationMatrix * glm::translate(glm::mat4(), glm::vec3(0,300,0));


		this->eye = getPosition(camMatrix);
		this->at = getPosition(atMatrix);
		this->up = getUp(camMatrix);

		this->viewMatrix = glm::lookAt(this->eye, this->at, this->up);
		return viewMatrix;
	}

};