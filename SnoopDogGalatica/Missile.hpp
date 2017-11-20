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

class Missile : public Shape, public Collision {

private:
	//update by target location and current position
	//
	const float UTL = 2000.0; //2000 updates to live
	const float UTA = 200.0;  //200 updates to activate
	const int detectionRange = 3000;
	float step;
	float rStep; 
	int ttl, activate;
	int target;
	int hostId;
	bool fired;
	bool exitedPlanet; //for the initial spawn for missile sites
	char * hostName;

public:
	//missile's id should be used as following
	//6 for from ship
	//7 for from unum missilesite
	//8 for from secundus missilesite
	Missile(int id, int hostId, int numOfVert, char * fileName, float size) :
		Shape(id, numOfVert, fileName, size){
		this->hostId = hostId;
		ttl = UTL;
		activate = UTA;
		fired = false;
		exitedPlanet = false;
		step = 50;

		if (fromMissileSites()){
			this->target = 0;
		}

		if(hostId == 1){
			hostName = "Unum Site";
		}
		else if(hostId == 2){
			hostName = "Secundus Site";
		}
		else{
			hostName = "Warbird";
		}
	}

	void update(glm::mat4 shipOM, float shipSize, glm::mat4 unumSiteOM, float unumSiteSize, glm::mat4 secundusSiteOM, float secundusSiteSize,
		glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize, glm::mat4 primusOM, 
		float primusSize, glm::mat4 secundusOM, float secundusSize, bool shipIsDead, bool unumSiteIsDead, bool secundusSiteIsDead) {

		bool diedViaPlanet = false;
		bool diedViaSite = false;
		bool diedViaShip = false;
		int hit = -1;

		if (fired) { //if not fired, no action needed

			if (ttl > 0) { //translate all the time if there are time to live remaining
				if(UTL - ttl > 0)
					exitedPlanet = true;

				if (activate > 0) {
					translateForward();
					activate--;//since not activated no rotation 
					if (activate == 0) {//identify target
						if(fromWarbird())
							target = identify(unumSiteOM, secundusSiteOM, unumSiteIsDead, secundusSiteIsDead);
						else if(fromMissileSites()){
							target = 0;
						}
					}
				}
				else { //activated
					if(target != -1){
						if(fromMissileSites() && !shipIsDead)
							rotateTowards(shipOM, unumSiteOM, secundusSiteOM);
						else if(fromWarbird())
							rotateTowards(shipOM, unumSiteOM, secundusSiteOM);	
					}
					translateForward();
					ttl--;
				}

				glm::vec3 missilePos = getPosition(getOrientationMatrix());
				float missileSize = getSize();

				//general missiles
				//should check if you hit the target/obstacles whether or not smart aspect is activated
				//int to check the initial spawning of missiles (which are being spawned inside the planet)
				planetCollision(missilePos, missileSize, sunOM, sunSize * 2, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize);
				if(fromUnumSite() && !exitedPlanet)
					diedViaPlanet = false;
				else if(fromSecundusSite() && !exitedPlanet)
					diedViaPlanet = false;
				else
					diedViaPlanet = isInPContact();

				//specifically for WARBIRD MISSILE hitting missile sites
				//returns -1 if no, 0 if unumsite, 1 if secundussite
				if(fromWarbird()){
					int hit = missileSiteCollision(missilePos, missileSize, unumSiteOM, unumSiteSize, secundusSiteOM, secundusSiteSize);
					diedViaSite = isInSContact();
				}

				//specifically for MISSILE SITES hitting the ship
				if(fromMissileSites()){
					warbirdCollision(missilePos, missileSize, shipOM, shipSize);
					diedViaShip = isInWContact();
				}

				if(diedViaSite){
					printf("missile from %s died via site destruction\n", hostName);
					resetMissile();
				}
				else if(diedViaShip){
					printf("missile from %s died via hitting warbird\n", hostName);
					resetMissile();
				}
				else if(diedViaPlanet){
					printf("missile from %s died via planet hit\n", hostName);
					resetMissile();
				}

			}
			else //if it's reached its max distance, then reset counters and position
			{
				printf("missile from %s died via distance\n", hostName);
				resetMissile();
				
			}
			
		}
		else{ //hasnt been fired yet. must check if the ship is detection 
			if(fromMissileSites()){
				detectShip(shipOM, unumSiteOM, secundusSiteOM);
			}
		}
	}

	void detectShip(glm::mat4 warbirdOM, glm::mat4 unumSiteOM, glm::mat4 secundusSiteOM){
		float distanceBetween = distance(getPosition(warbirdOM), getPosition(unumSiteOM));
		if((distanceBetween <= detectionRange) && fromUnumSite())
			fire(unumSiteOM);

		distanceBetween = distance(getPosition(warbirdOM), getPosition(secundusSiteOM));
		if((distanceBetween <= detectionRange) && fromSecundusSite())
			fire(secundusSiteOM);		

	}

	void resetMissile(){
		sendToCenter();
		ttl = UTL;
		activate = UTA;
		fired = false;
		exitedPlanet = false;
	}

	int identify(glm::mat4 unum, glm::mat4 secundus, bool unumSiteIsDead, bool secundusSiteIsDead) {
		//here calculate distance

		//no sites alive. no targets available
		if(unumSiteIsDead && secundusSiteIsDead)
			return -1;

		glm::vec3 missilePos = getPosition(getOrientationMatrix());
		float distanceBetweenUnum = distance(missilePos, getPosition(unum));
		float distanceBetweenSecundus = distance(missilePos, getPosition(secundus));

		printf("%f \t %f \n", distanceBetweenUnum, distanceBetweenSecundus);

		//needs to be in detection range to be able to choose
		if(distanceBetweenUnum <= detectionRange && distanceBetweenSecundus <= detectionRange){
			if((distanceBetweenUnum > distanceBetweenSecundus) && !secundusSiteIsDead ){
				printf("chose secundus\n");
				return 1;
			}
			
			if((distanceBetweenUnum < distanceBetweenSecundus) && !unumSiteIsDead){
				printf("chose unum\n");
				return 1;
			}
		}
		
		if(distanceBetweenUnum <= detectionRange){
			if(!unumSiteIsDead){
				printf("chose unum\n");
				return 1;
			}
		}
		
		if(distanceBetweenSecundus <= detectionRange){
			if(!secundusSiteIsDead){
				printf("chose secundus\n");
				return 2;
			}
		}
		
		return -1;
	}
	bool isFired() {
		return fired;
	}

	void translateForward(){
		this->translationMatrix = glm::translate(this->translationMatrix, -step * getOut(this->rotationMatrix));

	}
	void rotateTowards(glm::mat4 shipOM, glm::mat4 unumOM, glm::mat4 secundusOM){
		glm::vec3 targetPos; //this will be your at
		glm::vec3 missilePos = getPosition(getOrientationMatrix());

		if(target == 0){
			targetPos = getPosition(shipOM);
		}
		else if(target == 1){
			targetPos = getPosition(unumOM);
		}
		else if(target == 2){
			targetPos = getPosition(secundusOM);
		}

		//now calculate the rotation matrix


		//our up vector here might need to be changed
		glm::mat4 tempRM = glm::inverse(glm::lookAt(missilePos, targetPos, glm::vec3(0, 1, 0)));
		float * tempRMValues = (float*)glm::value_ptr(tempRM);

		this->rotationMatrix = glm::mat4(tempRMValues[0], tempRMValues[1], tempRMValues[2], 0, tempRMValues[4],
			tempRMValues[5], tempRMValues[6], 0, tempRMValues[8], tempRMValues[9], tempRMValues[10], 0, 0, 0, 0, 1);


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
	void fire(glm::mat4 objOM) {
		if (fromWarbird()){
			printf("firing missile from %s \n", hostName);
			spawn(objOM);
		}
		else{
			printf("firing missile from %s \n", hostName);
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
		return (hostId ==  1 || hostId == 2);
	}

	bool fromUnumSite(){
		return hostId == 1;
	}

	bool fromSecundusSite(){
		return hostId == 2;
	}

	glm::mat4 getModelMatrix() {
		return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
	}

};