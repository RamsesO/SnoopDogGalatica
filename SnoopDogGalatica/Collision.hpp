/*
	Collision.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Collision__

class Collision : public Signal {

private:
	bool contact;

public:
	Collision() {
		this->contact = true;
	}

	bool colliding(glm::vec3 objPos, float objSize, glm::vec3 targetPos, float targetSize) {
		float distanceBetween = distance(objPos, targetPos);
		if (distanceBetween < (targetSize + objSize + 50)) {
			return true;
		}
		return false;
	}

	void collisionCheck(glm::vec3 objPos, float objSize, glm::vec3 targetPos, float targetSize) {
		if (colliding(objPos, objSize, targetPos, targetSize) == true) {
			this->contact = true;
		}
		else {
			this->contact = false;
		}
	}

};