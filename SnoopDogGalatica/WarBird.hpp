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

    const float rotateRadians = 0.05f;
    float rotateBy;
    float step;
	int doRotateThruster; //0 is dont rotate. 1 is rotate left. 2 is rotate right
	glm::vec3 direction;

    WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians): Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
    	this->direction = glm::vec3(0);
    	this->doRotateThruster = false;
        this->step = 10;
        this->rotateBy = 0;
    }

    void changeStep(){
        if(step == 10){
            step = 50;
        }
        else if(step == 50){
            step = 100;
        }
        else{
            step = 10;
        }
    }

	void moveForward(){
        this->translationMatrix =  glm::translate(this->translationMatrix, -step * getOut(this->rotationMatrix));
    }

    void moveBackward(){
        this->translationMatrix =  glm::translate(this->translationMatrix, step * getOut(this->rotationMatrix)); 
    }

    void yawLeft(){
        rotateBy = rotateRadians;
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0,1,0));
    }

    void yawRight(){
        rotateBy = -rotateRadians;
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0,1,0));
    }

    void pitchUp(){
        rotateBy = rotateRadians;
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(1,0,0));
    }

    void pitchDown(){
        rotateBy = -rotateRadians;
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(1,0,0));
    }

    void rollLeft(){
        rotateBy = rotateRadians;
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0,0,1));
    }

    void rollRight(){
        rotateBy = -rotateRadians;
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, glm::vec3(0,0,1));
    }

	glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }

    void update() {
       // this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, this->rotationAxis);
      //  rotateBy = 0;

        /*
        if(pitch != 0)
            this->rotationMatrix = glm::rotate(this->rotationMatrix, pitch, rotateBy, glm::vec3(1,0,0));
        else if(yaw != 0)
            this->rotationMatrix = glm::rotate(this->rotationMatrix, yaw, rotateBy, glm::vec3(0,1,0));
        else if(roll != 0)
            this->rotationMatrix = glm::rotate(this->rotationMatrix, roll, rotateBy, glm::vec3(0,0,1));
        
        forward = glm::getIn(orientationMatrix) * step * stepDistance;
        this->translationMatrix = glm::translate(translationMatrix, forward);

        */

    }

};