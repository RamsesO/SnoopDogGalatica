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

	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
	glm::vec3 rotationAxis;
    float radians;
    
public:

    Shape(int id, int numOfVert, char * fileName, float boundRad, float modelSize) {
        this->id = id;
        this->numOfVert = numOfVert;
        this->fileName = fileName;
        this->boundRad = boundRad;
        this->modelSize = modelSize;
    }
    
}