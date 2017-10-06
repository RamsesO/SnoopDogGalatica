/*
	Moon.hpp

	Lemuel Dizon
	Ramses Ordonez
	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __MOON__

class Moon : public Planet {

public:

	glm::mat4 lunarTranslation;

	Moon(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians,
		glm::vec3 orbitalAxis, float orbitalRadians, glm::vec3 tiltAxis, float tiltAngle, glm::vec3 lunarTranslation)
		: Planet(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians, orbitalAxis, orbitalRadians, tiltAxis, tiltAngle) {
		this->lunarTranslation = glm::translate(glm::mat4(), lunarTranslation);;
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->orbitalMatrix * this->lunarTranslation * glm::inverse(this->orbitalMatrix) *
			this->axialTilt * this->rotationMatrix * this->scaleMatrix);
	}

};