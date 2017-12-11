/*
    Sun.hpp (non-orbiting planet)

    Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

    10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SUN__

class Sun : public Shape {

public:

    Sun(): Shape(){}
    Sun(int id, int numOfVert, char * fileName, float size): Shape(id, numOfVert, fileName, size) {}
    Sun(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians): Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {}

    glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }

    void update(WarBird *warbird) {
		glm::vec3 sunPos = getPosition(this->translationMatrix);
		float sunSize = this->size;

		//Warbird Interactions
		warbird->appendGravVec(sunPos, sunSize);
		if (warbird->isColliding(sunPos, sunSize)) {
			if (warbird->isDead() == false) {
				printf("Warbird crashed into the Sun.\n");
				warbird->signalKOHit();
			}
		}

        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
    }

};