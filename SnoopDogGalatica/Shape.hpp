/*
    Shape.hpp

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

protected:

    int id;
    int numOfVert;
    char * fileName;
    float size;
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

    Shape(int id, int numOfVert, char * fileName, float size, float modelSize) {
        this->id = id;
        this->numOfVert = numOfVert;
        this->fileName = fileName;
        this->boundRad = boundRad;
        this->modelSize = modelSize;

        scaleMatrix = glm::scale(glm::mat4(), glm::vec3(size * 1.0f / modelSize));
        translationMatrix = glm::translate(glm::mat4(), glm::vec3(0));
        rotationAxis = glm::vec3(0);
        radians = glm::radians(1.0f);
    }

    Shape(int id, int numOfVert, char * fileName, float size, float modelSize, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians) {
        this->id = id;
        this->numOfVert = numOfVert;
        this->fileName = fileName;
        this->boundRad = boundRad;
        this->modelSize = modelSize;

        this->scaleMatrix = glm::scale(glm::mat4(), glm::vec3(size * 1.0f / modelSize));
        this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
        this->rotationAxis = rotationAxis;
        this->radians = glm::radians(radians);
    }

    glm::mat4 getModelMatrix() {
        return (translationMatrix * scaleMatrix);
    }

}