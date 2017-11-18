/*
	Moon.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __MOON__

class Moon : public Planet {

public:

Moon(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians, 
		glm::vec3 orbitalAxis, float orbitalRadians, glm::vec3 tiltAxis, float tiltAngle):Planet(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians, 
		orbitalAxis, orbitalRadians, tiltAxis, tiltAngle){}
	glm::mat4 getModelMatrix(glm::mat4 planetMatrix) {
		return (planetMatrix * this->orbitalMatrix * this->translationMatrix * glm::inverse(this->orbitalMatrix) *
			this->axialTilt * this->rotationMatrix * this->scaleMatrix);
	}

	glm::mat4 getHubMatrix(glm::mat4 planetMatrix) {
		return (planetMatrix * this->orbitalMatrix * this->translationMatrix * glm::inverse(this->orbitalMatrix) *
			this->axialTilt * this->rotationMatrix);
	}

};