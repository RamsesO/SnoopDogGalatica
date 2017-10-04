/*
    Shape3D.hpp

    Lemuel Dizon
    Ramses Ordonez
    10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SHAPE__

class Shape {

private:

    int id;
    int numOfVert;
    char * fileName;
    float boundRad;
    float modelSize; 

    GLuint vPosition;
    GLuint vColor;
    GLuint vNormal;

    glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
    glm::vec3 rotationAxis;
	glm::mat4 rotationMatrix;    
    float radians;
    
public:

    Shape(int id, int numOfVert, char * fileName, float boundRad, float modelSize) {
        this->id = id;
        this->numOfVert = numOfVert;
        this->fileName = fileName;
        this->boundRad = boundRad;
        this->modelSize = modelSize;

        scaleMatrix = glm::scale(glm::mat4(), glm::vec3(modelSize * 1.0f / boundRad));
        translationMatrix = glm::translate(glm::mat4(), glm::vec3(0));
        rotationAxis = glm::vec3(1);
        radians = glm::radians(1.0f);
    }

    glm::mat4 getModelMatrix() {
        return (translationMatrix * scaleMatrix);
    }

    void update() {
        rotationMatrix = glm::rotate(rotationMatrix, radians, rotationAxis);
    }

}