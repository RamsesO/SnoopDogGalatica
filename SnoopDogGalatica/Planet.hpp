/*
	Planet.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __PLANET__

class Planet : public Shape {

public:

	glm::vec3 orbitalAxis;
	float orbitalRadians;
	glm::mat4 orbitalMatrix;

	glm::mat4 axialTilt;
	float tiltAngle;

	Planet(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians, 
		glm::vec3 orbitalAxis, float orbitalRadians, glm::vec3 tiltAxis, float tiltAngle) 
		: Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians) {
		this->orbitalAxis = orbitalAxis;
		this->orbitalRadians = orbitalRadians;

		this->tiltAngle = tiltAngle;
		this->axialTilt = glm::rotate(glm::mat4(), tiltAngle, tiltAxis);
	}
	
	glm::mat4 getModelMatrix() {
		return (this->orbitalMatrix * this->translationMatrix * glm::inverse(this->orbitalMatrix) * 
			this->axialTilt * this->rotationMatrix * this->scaleMatrix);
	}

	glm::mat4 getPlanetMatrix() {
		return (this->orbitalMatrix * this->translationMatrix * glm::inverse(this->orbitalMatrix));
	}

	glm::mat4 getHubMatrix() {
		return (this->orbitalMatrix * this->translationMatrix * glm::inverse(this->orbitalMatrix) * this->axialTilt * this->rotationMatrix);
	}

	void setMissileInteraction(Missile *m, glm::vec3 planetPos, float planetSize) {
		if (m->hasLaunched() == true) {
			m->appendGravVec(planetPos, planetSize);
			if (m->isColliding(planetPos, planetSize)) {
				printf("%s missile crashed into the Planet.\n", m->getHostName());
				m->signalKOHit();
			}
		}
	}

	void update(WarBird *warbird, Missile *wbMissile, Missile *usMissile, Missile *ssMissile) {
		glm::vec3 planetPos = getPosition(getHubMatrix());
		float planetSize = this->size;

		//Warbird Interactions
		if (warbird->isDead() == false) {
			warbird->appendGravVec(planetPos, planetSize);
			if (warbird->isColliding(planetPos, planetSize)) {
				printf("Warbird crashed into the Planet.\n");
				warbird->signalKOHit();
			}
		}

		//Missile Interactions
		setMissileInteraction(wbMissile, planetPos, planetSize);
		setMissileInteraction(usMissile, planetPos, planetSize);
		setMissileInteraction(ssMissile, planetPos, planetSize);


		this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
		this->orbitalMatrix = glm::rotate(this->orbitalMatrix, this->orbitalRadians, this->orbitalAxis);
	}

};