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

public:

	WarBirdCam(glm::vec3 translationMatrix) {
		this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::mat4 getCamMatrix(glm::mat4 warbirdOrientationMatrix) {
		float * warbirdPos = (float*)glm::value_ptr(warbirdOrientationMatrix);

		glm::mat4 cameraTranslationMatrix = glm::translate(glm::mat4(), glm::vec3(0,300,1000));
		glm::mat4 cameraOrientationMatrix = warbirdOrientationMatrix * cameraTranslationMatrix ;

		this->eye = getPosition(cameraOrientationMatrix) ;
		this->at = glm::vec3(warbirdPos[12], warbirdPos[13] + 300, warbirdPos[14]);
		
		this->up = getUp(cameraOrientationMatrix);

		this->viewMatrix = glm::lookAt(this->eye, this->at, this->up);
		return viewMatrix;
	}

	// +/-
	// void updateRadians(float modifiedRadians){
	// 	this->radians += modifiedRadians;
	// }


};