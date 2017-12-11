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

	void setMissileInteraction(Missile *m, glm::vec3 sunPos, float sunSize) {
		if (m->hasLaunched() == true) {
			m->appendGravVec(sunPos, sunSize);
			if (m->isColliding(sunPos, sunSize)) {
				printf("%s missile crashed into the Sun.\n", m->getHostName());
				m->signalKOHit();
			}
		}
	}

    void update(WarBird *warbird, Missile *wbMissile, Missile *usMissile, Missile *ssMissile) {
		glm::vec3 sunPos = getPosition(this->translationMatrix);
		float sunSize = this->size;

		//Warbird Interactions
		if (warbird->isDead() == false) {
			warbird->appendGravVec(sunPos, sunSize);
			if (warbird->isColliding(sunPos, sunSize)) {
				printf("Warbird crashed into the Sun.\n");
				warbird->signalKOHit();
			}
		}

		//Missile Interactions
		setMissileInteraction(wbMissile, sunPos, sunSize);
		setMissileInteraction(usMissile, sunPos, sunSize);
		setMissileInteraction(ssMissile, sunPos, sunSize);

        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
    }

};