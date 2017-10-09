/*
    Sun.hpp (non-orbiting planet)

    Lemuel Dizon
    Ramses Ordonez
    10/2/2017
*/

# ifndef __INCLUDES465__
# include "../../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SUN__

class Sun : public Shape {

public:

	//using Shape::Shape;
    Sun(): Shape(){}
    Sun(int id, int numOfVert, char * fileName, float size): Shape(id, numOfVert, fileName, size){}
    Sun(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians): Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {}

    glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }

    void update() {
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
    }

};