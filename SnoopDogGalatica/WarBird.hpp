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

	int doRotateThruster; //0 is dont rotate. 1 is rotate left. 2 is rotate right
	glm::vec3 direction;

    WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians): Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
    	this->direction = glm::vec3(0);
    	this->doRotateThruster = false;
    }

	void moveForward(GLfloat step){
        glm::vec3 newAt = glm::vec3(0.0f, 0.0f, -step);
        this->translationMatrix = glm::translate(this->translationMatrix, newAt);
    }

    void moveBackward(GLfloat step){
        glm::vec3 newAt = glm::vec3(0.0f, 0.0f, step);
        this->translationMatrix = glm::translate(this->translationMatrix, newAt);
    }

	void rotateThruster(int rotate){
		if(rotate > 2 || rotate < 0)
			return;
		doRotateThruster = rotate;
	}


	glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }

    void update() {
    	if(doRotateThruster == 1){
    		this->radians -= 0.02;
        	this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
        	printf("%f \n", this->radians);
        	doRotateThruster = 0;
    	}
    	else if(doRotateThruster == 2){
    		this->radians += 0.02;
    		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
        	doRotateThruster = 0;
        	printf("%f \n", this->radians);    	}
    	else{
    		this->radians = 0;
        	this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
    	}
    }

};