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

# define __WarBird__

class WarBird : public Shape {

public:

	float rotateThruster;
	bool doRotateThruster;
	glm::vec3 direction;

    WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians): Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
    	this->rotateThruster = 0.0;
    	this->direction = glm::vec3(0);
    	this->doRotateThruster = false;
    }

	
	void rotateThrusterPositive(){
		rotateThruster += 0.02;
		doRotateThruster = true;
	}

	void rotateThrusterNegative(){
		rotateThruster -= 0.02;
		doRotateThruster = true;
	}

	glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }

    void update() {
    	if(doRotateThruster){
        	this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateThruster, this->rotationAxis);
        	doRotateThruster = false;
    	}
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
    }

};