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

class MissileSite : public Shape {

private:
	int missiles;
	int health;

public:

	MissileSite(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians) :
		Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
		this->missiles = 5;
		this->health = 1;
	}

	glm::mat4 getModelMatrix(glm::mat4 hubMatrix) {
		return (this->translationMatrix * hubMatrix * this->scaleMatrix);
	}

};