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
    int key; // 1-8 designates the kind of movement

    WarBird(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians): Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
        this->step = 10;
        this->rotateBy = 0;
        this->key = -1;
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

    void movement(int i){
        key = i;
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

    void warpTo(glm::mat4 planetCamOM, glm::mat4 planetCamRM){
        this->translationMatrix = planetCamOM;
        this->rotationMatrix = planetCamRM;
    }

	glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }


    void update() {
       // this->rotationMatrix = glm::rotate(this->rotationMatrix, this->rotateBy, this->rotationAxis);
      //  rotateBy = 0;

        switch(key){
            case 0:
                moveForward();
            break;
            case 1:
                moveBackward();
            break;
            case 2:
                yawLeft();
            break;
            case 3:
                yawRight();
            break;
            case 4:
                pitchDown();
            break;
            case 5:
                pitchUp();
            break;
            case 6:
                rollLeft();
            break;
            case 7:
                rollRight();
            break;
        }

        key = -1;


    }

};