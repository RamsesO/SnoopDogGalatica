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

class Missile : public Shape, public Entity{

private:
	//update by target location and current position
	//
	const float UTL = 2000.0; //2000 updates to live
	const float UTA = 200.0;  //200 updates to activate
	const int detectionRange = 3000; 
	float step;
	int ttl, activate;
	int target;
	bool fired;
	int hostId;

public:
	bool reloading() {
		return fired;
	}
	//missile's id should be used as following
	//8 for from ship
	//9 for from unum missilesite
	//10 for from duo missilesite
	Missile(int id, int hostId, int numOfVert, char * fileName, float size) :
		Shape(id, numOfVert, fileName, size), 
		Entity(0, 1){ //dummy values to use entity's relation to collision
		this->hostId = hostId;
		ttl = UTL;
		activate = UTA;
		fired = false;
		step = 50;
		if (fromMissileSites())
			target = 0;
	}

	int update(glm::mat4 ship, float shipSize, glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize,
		glm::mat4 primusOM, float primusSize, glm::mat4 secundusOM, float secundusSize) {
		int result = 0;
		if (fired) { //if not fired, no action needed
			if (ttl > 0) { //translate all the time if there are time to live remaining
				if (activate > 0) {
					translateForward();
					activate--;//since not activated no rotation 
					if (activate == 0 && fromWarbird())//identify target
						target = identify(unumOM, duoOM);
					else if(activate == 0 && fromMissileSites())
						target = 0;
				}
				else { //activated
					glm::vec3 misPos = getPosition(this->translationMatrix);
					planetCollision(id, misPos, this->size, sunOM, sunSize * 2, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize);
					shipCollision(id, misPos, this->size, ship, shipSize);
					bool justDied = onPlanetHit();
					bool hit;
					if(fromWarbird())
						hit = onMissileHit();
					else{
						hit = onShipHit();
						result = 2;
					}
					if(hit){
						printf("target destroyed\n");
						resetCollisions();
						sendToCenter();
						ttl = UTL;
						activate = UTA;
						fired = false;
					}
					else if (justDied) {
						printf("destroyed by planet\n");
						resetCollisions();
						sendToCenter();
						ttl = UTL;
						activate = UTA;
						fired = false;
					}
					else{
						if(target != -1)
							rotateTowards(ship, unumOM, duoOM);
						translateForward();
						ttl--;
					}
				}
				
			}
			else //if it's reached its max distance, then reset counters and position
			{
				printf("exploded on its own. \n");
				sendToCenter();
				ttl = UTL;
				activate = UTA;
				fired = false;
			}
		}else{
			if(fromMissileSites()){ //detect 
				if(hostId == 1){
					if (detect(ship, unumOM)){
						printf("unum detected the ship\n");
						fire(unumOM);
						return 1;
					}
				}else{
					if (detect(ship, duoOM)){
						printf("secundus detected the ship\n");
						fire(secundusOM);
						return 1;
					}
				}
			}
		}
		return result;
	}

	 bool detect(glm::mat4 shipOM, glm::mat4 myOM){
	 	float distanceBetween = distance(getPosition(shipOM), getPosition(myOM));
	 	return (distanceBetween <= 3000);
	 }

	float identify(glm::mat4 unum, glm::mat4 duo) {
		//here calculate distance
		glm::vec3 missilePos = getPosition(getOrientationMatrix());
		float distanceBetweenUnum = distance(missilePos, getPosition(unum));
		float distanceBetweenDuo = distance(missilePos, getPosition(duo));
		if(distanceBetweenUnum <= detectionRange || distanceBetweenDuo <= detectionRange){
			if(distanceBetweenUnum > distanceBetweenDuo){
				printf("chose duo\n");
				return 2;
			}
			else{
				printf("chose unum\n");
				return 1;
			}
		}
		else//all out of detection range
			return -1;
	}

	void translateForward(){
		this->translationMatrix = glm::translate(this->translationMatrix, -step * getOut(this->rotationMatrix));

	}
	void rotateTowards(glm::mat4 shipOM, glm::mat4 unumOM, glm::mat4 duoOM){
		glm::vec3 targetPos; //this will be your at
		glm::vec3 missilePos = getPosition(getOrientationMatrix());

		if(target == 0){
			targetPos = getPosition(shipOM);
		}
		else if(target == 1){
			targetPos = getPosition(unumOM);
		}
		else{
			targetPos = getPosition(duoOM);
		}

		//our up vector here might need to be changed
		glm::mat4 tempRM = glm::inverse(glm::lookAt(missilePos, targetPos, glm::vec3(0, 1, 0)));
		float * tempRMValues = (float*)glm::value_ptr(tempRM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);


	}

	//at the point of fire, change RM to match the ship's rotation matrix
	//or match it to the angle of missilesite to warbird
	void fire(glm::mat4 objOM) {
		printf("enter fire function\n");
		if (fromWarbird()){
			printf("enter ship fire \n");
			spawn(objOM);
		}else{
			printf("missile site fire!!!\n");
			spawn(objOM);
		}

		fired = true;
	}

	void spawn(glm::mat4 objOM){
		this->translationMatrix = glm::translate(glm::mat4(), getPosition(objOM));

		float * tempRMValues = (float*)glm::value_ptr(objOM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);

	}

	bool fromWarbird(){
		return hostId == 0;
	}

	bool fromMissileSites(){
		return (hostId == 1 || hostId == 2);
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

};