/*
	Planet.hpp

	Lemuel Dizon
	Ramses Ordonez
	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __PLANET__

class Planet : public Shape {

public:

	glm::vec3 orbitalAxis;
	float orbitalRadians;
	glm::mat4 orbitalMatrix;

	Planet(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, 
		glm::vec3 rotationAxis, float radians, glm::vec3 orbitalAxis, float orbitalRadians) 
		: Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
		this->orbitalAxis = orbitalAxis;
		this->orbitalRadians = orbitalRadians;
	}
	
	glm::mat4 getModelMatrix() {
		return (this->orbitalMatrix * this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

	void update() {
		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
		this->orbitalMatrix = glm::rotate(this->orbitalMatrix, this->orbitalRadians, this->orbitalAxis);
	}

};