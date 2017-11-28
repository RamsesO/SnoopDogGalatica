/*
	Models.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Models__

class Models {
private:
	//Positions
	glm::vec3 ruberPos;
	glm::vec3 unumPos;
	glm::vec3 duoPos;
	glm::vec3 primusPos;
	glm::vec3 secundusPos;
	glm::vec3 warbirdPos;
	glm::vec3 unumSitePos;
	glm::vec3 secundusSitePos;
	glm::vec3 wbMissilePos;
	glm::vec3 usMissilePos;
	glm::vec3 ssMissilePos;

	//Sizes
	float ruberSize;
	float unumSize;
	float duoSize;
	float primusSize;
	float secundusSize;
	float unumSiteSize;
	float secundusSiteSize;
	float warbirdSize;
	float missileSize;

public:
	Models() {}

	void setPositions(Sun *ruber, Planet *unum, Planet *duo, Moon *primus, Moon *secundus, WarBird *warbird, MissileSite *unumSite,
		MissileSite *secundusSite, Missile *wbMissile, Missile *usMissile, Missile *ssMissile) {
		glm::mat4 ruberOM = ruber->getOrientationMatrix();
		glm::mat4 unumOM = unum->getHubMatrix();
		glm::mat4 duoOM = duo->getHubMatrix();
		glm::mat4 primusOM = primus->getHubMatrix(duo->getPlanetMatrix());
		glm::mat4 secundusOM = secundus->getHubMatrix(duo->getPlanetMatrix());
		glm::mat4 warbirdOM = warbird->getOrientationMatrix();
		glm::mat4 unumSiteOM = unumSite->getSiteMatrix(unumOM);
		glm::mat4 secundusSiteOM = secundusSite->getSiteMatrix(secundusOM);
		glm::mat4 wbMissileOM = wbMissile->getOrientationMatrix();
		glm::mat4 usMissileOM = usMissile->getOrientationMatrix();
		glm::mat4 ssMissileOM = ssMissile->getOrientationMatrix();

		this->ruberPos = getPosition(ruberOM);
		this->unumPos = getPosition(unumOM);
		this->duoPos = getPosition(duoOM);
		this->primusPos = getPosition(primusOM);
		this->secundusPos = getPosition(secundusOM);
		this->warbirdPos = getPosition(warbirdOM);
		this->unumSitePos = getPosition(unumSiteOM);
		this->secundusSitePos = getPosition(secundusSiteOM);
		this->wbMissilePos = getPosition(wbMissileOM);
		this->usMissilePos = getPosition(usMissileOM);
		this->ssMissilePos = getPosition(ssMissileOM);
	}

	void setSizes(Sun *ruber, Planet *unum, Planet *duo, Moon *primus, Moon *secundus, WarBird *warbird, MissileSite *unumSite,
		MissileSite *secundusSite, Missile *wbMissile) {
		this->ruberSize = ruber->getSize() / 2;
		this->unumSize = unum->getSize();
		this->duoSize = duo->getSize();
		this->primusSize = primus->getSize();
		this->secundusSize = secundus->getSize();
		this->unumSiteSize = unumSite->getSize();
		this->secundusSiteSize = secundusSite->getSize();
		this->warbirdSize = warbird->getSize();
		this->missileSize = wbMissile->getSize() / 4;
	}

	void update(Sun *ruber, Planet *unum, Planet *duo, Moon *primus, Moon *secundus, WarBird *warbird, MissileSite *unumSite,
		MissileSite *secundusSite, Missile *wbMissile, Missile *usMissile, Missile *ssMissile) {
		
		ruber->update(warbird);
		unum->update(warbird);
		duo->update(warbird);
		primus->update(duo, warbird);
		secundus->update(duo, warbird);
		warbird->update();
		//unumSite->update(unumOM, warbirdOM, warbirdSize, wbMissileOM, usMissileOM, ssMissileOM, missileSize);
		//secundusSite->update(secundusOM, warbirdOM, warbirdSize, wbMissileOM, usMissileOM, ssMissileOM, missileSize);
		//wbMissile->update(ruberOM, ruberSize, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize,
		//	unumSiteOM, unumSiteSize, secundusSiteOM, secundusSiteSize, warbirdOM, warbirdSize);
		//usMissile->update(ruberOM, ruberSize, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize,
		//	unumSiteOM, unumSiteSize, secundusSiteOM, secundusSiteSize, warbirdOM, warbirdSize);
		//ssMissile->update(ruberOM, ruberSize, unumOM, unumSize, duoOM, duoSize, primusOM, primusSize, secundusOM, secundusSize,
		//	unumSiteOM, unumSiteSize, secundusSiteOM, secundusSiteSize, warbirdOM, warbirdSize);

		warbird->recieveSignals();
	}


};