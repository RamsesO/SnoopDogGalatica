/*
	Missile.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim
	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Missile__

class Missile : public Shape {

private:
	//update by target location and current position
	//
	const float UTL = 2000.0; //2000 updates to live
	const float UTA = 200.0;  //200 updates to activate
	float step;
	float rStep; //rotational step
	float ttl, activate; 
	int target;
	bool fired;

public:
	bool reloading() {
		return fired;
	}
	//missile's id should be used as following
	//6 for from ship
	//7 for from unum missilesite
	//8 for from duo missilesite
	Missile(int id, int numOfVert, char * fileName, float size) :
		Shape(id, numOfVert, fileName, size) {
		ttl = UTL;
		activate = UTA;
		fired = false;
		step = 10;
		if (id == 7 || id == 8)
			target = 6;
	}

	void update(glm::mat4 ship, glm::mat4 unum, glm::mat4 duo) {
		if (fired) { //if not fired, no action needed
			if (ttl > 0) { //translate all the time if there are time to live remaining
				this->translationMatrix = glm::translate(this->translationMatrix, -step * getOut(this->rotationMatrix));
				if (activate > 0) {
					activate--;//since not activated no rotation 
					if (activate == 0 && id == 6)//identify target
						target = identify(ship, unum, duo);
				}
				else { //activated
					this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
					ttl--;
				}
			}
			else //reset counters and position
			{
				this->translationMatrix = glm::translate(this->translationMatrix, glm::vec3(0));
				ttl = UTL;
				activate = UTA;
				fired = false;
			}
		}
	}

	float identify(glm::mat4 ship, glm::mat4 unum, glm::mat4 duo) {
		//here calculate distance
		//return 7 for unum < duo
		//return 8 for otherwise
		return 0;
	}

	//instead of locate we could use "rotate toward identified target" instead.
	void locate(glm::mat4 ship, glm::mat4 unum, glm::mat4 duo) {//locate should receive all positions 
		//find nearest target 
		if (id == 6) { //from ship
			//retrieve distance from ship vs unum and vs duo 
			//find shortest distance 
			//select target
		}
		else {//from missile site so target the ship


		}
	}

	//at the point of fire, change RM to match the ship's rotation matrix
	//or match it to the angle of missilesite to warbird
	void fire(glm::mat4 OM) {
		if (id == 6)
			this->rotationMatrix = OM;
		fired = true;
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

};