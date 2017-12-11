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
	glm::mat4 ruberOM;
	glm::mat4 unumOM;
	glm::mat4 duoOM;
	glm::mat4 primusOM;
	glm::mat4 secundusOM;
	glm::mat4 warbirdOM;
	glm::mat4 unumSiteOM;
	glm::mat4 secundusSiteOM;
	glm::mat4 wbMissileOM;
	glm::mat4 usMissileOM;
	glm::mat4 ssMissileOM;

public:
	Models() {}

	void setPositions(Sun *ruber, Planet *unum, Planet *duo, Moon *primus, Moon *secundus, WarBird *warbird, MissileSite *unumSite,
		MissileSite *secundusSite, Missile *wbMissile, Missile *usMissile, Missile *ssMissile) {
		this->ruberOM = ruber->getOrientationMatrix();
		this->unumOM = unum->getHubMatrix();
		this->duoOM = duo->getHubMatrix();
		this->primusOM = primus->getHubMatrix(duo->getPlanetMatrix());
		this->secundusOM = secundus->getHubMatrix(duo->getPlanetMatrix());
		this->warbirdOM = warbird->getOrientationMatrix();
		this->unumSiteOM = unumSite->getSiteMatrix(unumOM);
		this->secundusSiteOM = secundusSite->getSiteMatrix(secundusOM);
		this->wbMissileOM = wbMissile->getOrientationMatrix();
		this->usMissileOM = usMissile->getOrientationMatrix();
		this->ssMissileOM = ssMissile->getOrientationMatrix();
	}

	void update(Sun *ruber, Planet *unum, Planet *duo, Moon *primus, Moon *secundus, WarBird *warbird, MissileSite *unumSite,
		MissileSite *secundusSite, Missile *wbMissile, Missile *usMissile, Missile *ssMissile) {

		ruber->update(warbird, wbMissile, usMissile, ssMissile);
		unum->update(warbird, wbMissile, usMissile, ssMissile);
		duo->update(warbird, wbMissile, usMissile, ssMissile);
		primus->update(duo, warbird, wbMissile, usMissile, ssMissile);
		secundus->update(duo, warbird, wbMissile, usMissile, ssMissile);
		warbird->update(unumSite, getPosition(unumSiteOM), secundusSite, getPosition(secundusSiteOM));
		unumSite->update();
		secundusSite->update();
		wbMissile->update(warbird, unumSite, unumSiteOM, secundusSite, secundusSiteOM, usMissile, ssMissile);
		usMissile->update(warbird, unumSite, unumSiteOM, secundusSite, secundusSiteOM, wbMissile, ssMissile);
		ssMissile->update(warbird, unumSite, unumSiteOM, secundusSite, secundusSiteOM, wbMissile, usMissile);

		warbird->recieveSignals();
		unumSite->recieveSignals();
		secundusSite->recieveSignals();
		wbMissile->recieveSignals(unumSite, unumSiteOM, secundusSite, secundusSiteOM);
		usMissile->recieveSignals(unumSite, unumSiteOM, secundusSite, secundusSiteOM);
		ssMissile->recieveSignals(unumSite, unumSiteOM, secundusSite, secundusSiteOM);
	}


};