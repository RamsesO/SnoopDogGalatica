/*
	MissileSite.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __MissileSite__

class MissileSite : public Shape, public Entity {

public:

	MissileSite(int id, int numOfVert, char * fileName, float size, int missile, int health, bool isEnemy) :
		Shape(id, numOfVert, fileName, size), Entity(missile, health, isEnemy) {
	}

	void setSitePosition(glm::mat4 hubMatrix, float tiltAngle) {
		float vDist = (hubMatrix[1][1]) * 7.5;
		float angle = glm::degrees(tiltAngle);

		float xDist = glm::abs(vDist * glm::sin(angle)) * -1.5;
		float yDist = glm::abs(vDist * glm::cos(angle)) * 1;

		//For debugging
		printf("Angle: %f, vDist: %f, xDist: %f, yDist: %f\n", angle, vDist, xDist, yDist);

		this->translationMatrix = glm::translate(glm::mat4(), glm::vec3(xDist, yDist, 0));
	}

	glm::mat4 getModelMatrix(glm::mat4 hubMatrix) {
		return (this->translationMatrix * hubMatrix * this->scaleMatrix);
	}

	glm::mat4 getSiteMatrix(glm::mat4 hubMatrix) {
		return (this->translationMatrix * hubMatrix);
	}

};