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
	glm::vec3 rotationAxis;

public:

	WarBirdCam(glm::vec3 translationMatrix, glm::vec3 rotationAxis) {
		this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
		this->rotationAxis = rotationAxis;
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::mat4 getCamMatrix(glm::mat4 warbirdMatrix, glm::mat4 warbirdRotationMatrix) {
		float * warbirdPos = (float*)glm::value_ptr(warbirdMatrix);
		
		//glm::mat4 eyeMatrix = glm::translate(glm::translate(glm::mat4(), getIn(warbirdMatrix)), glm::vec3(0,300,1000));
		//glm::mat4 eyeMatrix = glm::translate(glm::mat4(), glm::vec3(warbirdPos[12],warbirdPos[13],warbirdPos[14]));
		//eyeMatrix = glm::translate(eyeMatrix, glm::vec3(50,300,1000));
		//float * eyePos = (float*)glm::value_ptr(eyeMatrix);

		this->eye = glm::vec3(warbirdPos[12], warbirdPos[13] + 300, warbirdPos[14] + 1000) ;
		this->at = glm::vec3(warbirdPos[12], warbirdPos[13] + 300, warbirdPos[14]);
		
		//this->up = glm::vec3(warbirdPos[4], warbirdPos[5], warbirdPos[6]);

		this->viewMatrix = glm::lookAt(this->eye, this->at, this->up) * warbirdRotationMatrix;
		return viewMatrix;
	}

	// +/-
	// void updateRadians(float modifiedRadians){
	// 	this->radians += modifiedRadians;
	// }


};