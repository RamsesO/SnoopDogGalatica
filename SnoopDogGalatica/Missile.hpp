/*
	Missile.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim
	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
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

	void update(glm::mat4 shipOM, float shipSize, glm::mat4 unumSiteOM, float unumSiteSize, glm::mat4 secundusSiteOM, float secundusSiteSize,
		glm::mat4 sunOM, float sunSize, glm::mat4 unumOM, float unumSize, glm::mat4 duoOM, float duoSize, glm::mat4 primusOM, 
		float primusSize, glm::mat4 secundusOM, float secundusSize) {

		bool diedViaPlanet = false;
		bool diedViaSite = false;
		bool diedViaShip = false;
		int hit = -1;

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

				if(diedViaPlanet){
					printf("missile from %s died via planet hit\n", hostName);
					resetMissile();
				}
				else if(diedViaShip){
					printf("missile from %s died via hitting warbird\n", hostName);
					resetMissile();
				}
				else if(diedViaSite){
					printf("missile from %s died via site destruction\n", hostName);
					resetMissile();
				}

			}
			else //reset counters and position
			{
				printf("missile from %s died via distance\n", hostName);
				resetMissile();
				
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