/*
	Snoop Dogg Galatica
	The Dankest Solar System

	Dizon, Lemuel
	Ordonez, Ramses
	Kim, Kelly
*/

# define __Mac__
# include "../../includes465/include465.hpp"
# include "../../includes465/texture465.hpp"
# include "Shape.hpp"
# include "Signal.hpp"
# include "Collision.hpp"
# include "Entity.hpp"
# include "Gravity.hpp"
# include "MissileSite.hpp"
# include "WarBird.hpp"
# include "Missile.hpp"
# include "Sun.hpp"
# include "Planet.hpp"
# include "Moon.hpp"
# include "PlanetCam.hpp"
# include "WarBirdCam.hpp"
# include "Models.hpp"
# include "Skybox.hpp"


// Models
const int nModels = Shape::nModels + 1;
Models *models = new Models();
Sun *ruber = new Sun(0, 1740 * 3, "assets/Ruber.tri", 2000.0f, glm::vec3(0),
	glm::vec3(0, 1, 0), 1.0f);
Planet *unum = new Planet(1, 1740 * 3, "assets/Unum.tri", 200.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 9.0f, glm::vec3(0, 1, 0), 0.004f, glm::vec3(0, 0, 1), 0.5f);
Planet *duo = new Planet(2, 16020 * 3, "assets/Duo.tri", 400.0f, glm::vec3(9000, 0, 0),
	glm::vec3(0, 1, 0), 5.0f, glm::vec3(0, 1, 0), 0.002f, glm::vec3(0, 0, 1), -0.3f);
Moon *primus = new Moon(3, 1740 * 3, "assets/Primus.tri", 100.0f, glm::vec3(2000, 0, 0),
	glm::vec3(0, 1, 0), 22.0f, glm::vec3(0, -1, 0), 0.012f, glm::vec3(0, 0, 1), -0.4f);
Moon *secundus = new Moon(4, 1740 * 3, "assets/Secundus.tri", 150.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 12.0f, glm::vec3(0, 1, 0), 0.006f, glm::vec3(0, 0, 1), 0.5f);
WarBird *warbird = new WarBird(5, 4852 * 3, "assets/WarBird.tri", 100.0f, glm::vec3(15000, 0, 0), 7, 1);
MissileSite *unumSite = new MissileSite(6, 2048 * 3, "assets/MissileSite.tri", 100.0f, 5, 1, true);
MissileSite *secundusSite = new MissileSite(7, 2048 * 3, "assets/MissileSite.tri", 75.5f, 5, 1, true);
Missile *wbMissile = new Missile(8, 0, 918 * 3, "assets/Missle.tri", 100.0f);
Missile *usMissile = new Missile(9, 1, 918 * 3, "assets/Missle.tri", 100.0f);
Missile *ssMissile = new Missile(10, 2, 918 * 3, "assets/Missle.tri", 100.0f);
Skybox * skybox;

//Cameras
int camMode = 0;
PlanetCam * unumCam = new PlanetCam(glm::vec3(4000 - 4000, 0, -4000), glm::vec3(0, 1, 0), 0.004f);
PlanetCam * duoCam = new PlanetCam(glm::vec3(9000 - 4000, 0, -4000), glm::vec3(0, 1, 0), 0.002f);
WarBirdCam * warbirdCam = new WarBirdCam(glm::vec3(0, 300, 1000));

//Warp Variables
int warp = -1;
glm::mat4 planetCamOM;
glm::mat4 planetOM;

//gravity variables
float gravityConstant = 1000;

//Title Information
char titleStr[300];
char baseStr[75] = "Snoop Dogg Galatica:  ";
char warbirdStr[15] = "Warbird";
char wbMissileStr[15];
char unumStr[15] = "Unum Site";
char usMissileStr[15];
char secStr[15] = "Secundus Site";
char ssMissileStr[15];
char upsStr[15];
char fpsStr[15];
char viewStr[15] = " Front View, ";
char sTypeStr[15] = " Ace ";
char speedStr[15] = "Speed";
char winStr[15] = "You Have Won!";
char loseStr[15] = "You Have Lost!";
bool win = false;
bool lose = false;

/*--------------------- SKYBOX STUFF ----------------------*/
int windowWidth = 800;
int windowHeight = 600;
int rawWidth = 256;
int rawHeight = 256;
char * file1 = "assets/1.raw";
char * file2 = "assets/2.raw";
char * file3 = "assets/pepe.raw";
char * file4 = "assets/4.raw";
char * file5 = "assets/5.raw";
char * file6 = "assets/6.raw";

/*--------------------- SHADERS ----------------------*/
char * vertexShaderFile = "simpleVertex.glsl";
char * fragmentShaderFile = "simpleFragment.glsl";
GLuint shaderProgram;
GLuint VAO[nModels];      // Vertex Array Objects
GLuint buffer[nModels];   // Vertex Buffer Objects

GLuint MVP;
GLuint MV;
//point light
GLuint lightPos;
GLuint lightCol;
GLuint eyeDir;
//ambient light
GLuint AMBI;
//spot lgiht
GLuint ConeDirection;
GLuint SpotCosCutoff;
GLuint SpotExponent;
GLuint SLightPosition;

//light strengths
GLuint SStrength;
GLuint PStrength;
GLuint DStrength;


glm::vec3 eye, at, up;
glm::mat4 viewMatrix;                // set in init()
glm::mat4 modelMatrix;
glm::mat4 projectionMatrix;          // set in reshape()
glm::mat4 ModelViewMatrix;
glm::mat4 ModelViewProjectionMatrix; // set in display();
GLfloat aspectRatio;

//pointlight position
glm::vec3 pointLightPos = glm::vec3(0.0f, 0.0f, 0.0f);
const static glm::vec3 pointLightCol = glm::vec3(0.5f, 0.2f, 0.2f);

//ambient
glm::vec3 Ambient = glm::vec3(0.0f, 0.0f, 0.0f);
bool isAmbiOn = false;

//spot
glm::vec3 spotDir = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 spotPos =    glm::vec3(0.0f, 0.0f, 0.0f);
GLfloat spotcos = 0.2f;
GLfloat spotexp = 1.0f;
GLfloat pointStrength = 0.7f;
GLfloat direcStrength = 0.3f;
GLfloat spotStrength = 1.0f;

/*--------------------------------------------------------*/

//Time Keepers
int timeQuantum[] = { 5, 40, 100, 500 };
int timeQuantumIndex = 0;
int frameCount = 0;
double currentTime;
double lastTime;
double timeInterval;

void updateTitle() {
	strcpy(titleStr, baseStr);
	strcat(titleStr, warbirdStr);
	strcat(titleStr, wbMissileStr);
	strcat(titleStr, unumStr);
	strcat(titleStr, usMissileStr);
	strcat(titleStr, secStr);
	strcat(titleStr, ssMissileStr);
	strcat(titleStr, upsStr);
	strcat(titleStr, fpsStr);
	strcat(titleStr, viewStr);
	strcat(titleStr, sTypeStr);
	strcat(titleStr, speedStr);
	// printf("title string = %s \n", titleStr);
	glutSetWindowTitle(titleStr);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skybox->update(viewMatrix, projectionMatrix);

//    ruber->displayShape(projectionMatrix, viewMatrix, ruber->getModelMatrix(), MVP, MV, VAO);
//    unum->displayShape(projectionMatrix, viewMatrix, unum->getModelMatrix(), MVP, MV, VAO);
//    duo->displayShape(projectionMatrix, viewMatrix, duo->getModelMatrix(), MVP, MV, VAO);
//    primus->displayShape(projectionMatrix, viewMatrix, primus->getModelMatrix(duo->getPlanetMatrix()), MVP, MV, VAO);
//    secundus->displayShape(projectionMatrix, viewMatrix, secundus->getModelMatrix(duo->getPlanetMatrix()), MVP, MV, VAO);
//    warbird->displayShape(projectionMatrix, viewMatrix, warbird->getModelMatrix(), MVP, MV, VAO);
//    unumSite->displayShape(projectionMatrix, viewMatrix, unumSite->getModelMatrix(unum->getHubMatrix()), MVP, MV, VAO);
//    secundusSite->displayShape(projectionMatrix, viewMatrix, secundusSite->getModelMatrix(secundus->getHubMatrix(duo->getPlanetMatrix())), MVP, MV, VAO);
//    wbMissile->displayShape(projectionMatrix, viewMatrix, wbMissile->getModelMatrix(), MVP, MV, VAO);
//    usMissile->displayShape(projectionMatrix, viewMatrix, usMissile->getModelMatrix(), MVP, MV, VAO);
//    ssMissile->displayShape(projectionMatrix, viewMatrix, ssMissile->getModelMatrix(), MVP, MV, VAO);
    glUseProgram(shaderProgram);
    
    modelMatrix = ruber->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    pointLightPos = getPosition(ModelViewMatrix);
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[ruber->id]);
    glDrawArrays(GL_TRIANGLES, 0, ruber->numOfVert);
    
    modelMatrix = unum->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[unum->id]);
    glDrawArrays(GL_TRIANGLES, 0, unum->numOfVert);
    
    modelMatrix = duo->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[duo->id]);
    glDrawArrays(GL_TRIANGLES, 0, duo->numOfVert);
    
    modelMatrix = primus->getModelMatrix(duo->getPlanetMatrix());
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[primus->id]);
    glDrawArrays(GL_TRIANGLES, 0, primus->numOfVert);
    
    modelMatrix = secundus->getModelMatrix(duo->getPlanetMatrix());
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[secundus->id]);
    glDrawArrays(GL_TRIANGLES, 0, secundus->numOfVert);
    
    modelMatrix = warbird->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    spotPos = getPosition(warbird->getOrientationMatrix()); //light position matches warbird position
    spotDir = getPosition(warbird->getTranslationMatrix()); // direction matches where the war bird is facing
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[warbird->id]);
    glDrawArrays(GL_TRIANGLES, 0, warbird->numOfVert);
    
    modelMatrix = unumSite->getModelMatrix(unum->getHubMatrix());
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[unumSite->id]);
    glDrawArrays(GL_TRIANGLES, 0, unumSite->numOfVert);
    
    modelMatrix = secundusSite->getModelMatrix(secundus->getHubMatrix(duo->getPlanetMatrix()));
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[secundusSite->id]);
    glDrawArrays(GL_TRIANGLES, 0, secundusSite->numOfVert);
    
    modelMatrix = wbMissile->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[wbMissile->id]);
    glDrawArrays(GL_TRIANGLES, 0, wbMissile->numOfVert);
    
    modelMatrix = usMissile->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[usMissile->id]);
    glDrawArrays(GL_TRIANGLES, 0, usMissile->numOfVert);
    
    modelMatrix = ssMissile->getModelMatrix();
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    ModelViewMatrix = viewMatrix * modelMatrix;
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    glBindVertexArray(VAO[ssMissile->id]);
    glDrawArrays(GL_TRIANGLES, 0, ssMissile->numOfVert);
    
    /*--------------------------- SHADER light ---------------------------*/
    
    glUniform3fv(lightPos, 1, glm::value_ptr(glm::vec3(pointLightPos)));
    glUniform3fv(lightCol, 1, glm::value_ptr(glm::vec3(pointLightCol)));
    glUniform3fv(eyeDir, 1, glm::value_ptr(glm::vec3(at)));
    
    glUniform3fv(AMBI, 1, glm::value_ptr(glm::vec3(Ambient)));
    
    glUniform1f(SpotCosCutoff, spotcos);
    glUniform1f(SpotExponent, SpotExponent);
    glUniform3fv(ConeDirection, 1, glm::value_ptr(glm::vec3(spotDir)));
    glUniform3fv(SLightPosition, 1, glm::value_ptr(glm::vec3(spotPos)));
    
    glUniform1f(PStrength, pointStrength);
    glUniform1f(DStrength, direcStrength);
    glUniform1f(SStrength, spotStrength);
    
    //showVec3("Ambient : ", Ambient);
    
    /*-------------------------------------------------------------------*/

	glutSwapBuffers();
	frameCount++;

	// see if a second has passed to set estimated fps information
	currentTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
	timeInterval = currentTime - lastTime;
	if (timeInterval >= 1000) {
		sprintf(fpsStr, " F/S: %4d, ", (int)(frameCount / (timeInterval / 1000.0f)));
		sprintf(upsStr, " U/S: %4d, ", (int)((1000 / timeQuantum[timeQuantumIndex])));

		lastTime = currentTime;
		frameCount = 0;
		if (win == false && lose == false) updateTitle();
	}
}

void init(void) {
	shaderProgram = loadShaders(vertexShaderFile, fragmentShaderFile);
	glUseProgram(shaderProgram);

	glGenVertexArrays(nModels, VAO);
	glGenBuffers(nModels, buffer);

	float modelSize = 0.0;
    modelSize = loadModelBuffer(ruber->fileName, ruber->numOfVert, VAO[ruber->id], buffer[ruber->id], shaderProgram,
                                ruber->vPosition, ruber->vColor, ruber->vNormal, "vPosition", "vColor", "vNormal");
    ruber->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(unum->fileName, unum->numOfVert, VAO[unum->id], buffer[unum->id], shaderProgram,
                                unum->vPosition, unum->vColor, unum->vNormal, "vPosition", "vColor", "vNormal");
    unum->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(duo->fileName, duo->numOfVert, VAO[duo->id], buffer[duo->id], shaderProgram,
                                duo->vPosition, duo->vColor, duo->vNormal, "vPosition", "vColor", "vNormal");
    duo->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(primus->fileName, primus->numOfVert, VAO[primus->id], buffer[primus->id], shaderProgram,
                                primus->vPosition, primus->vColor, primus->vNormal, "vPosition", "vColor", "vNormal");
    primus->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(secundus->fileName, secundus->numOfVert, VAO[secundus->id], buffer[secundus->id], shaderProgram,
                                secundus->vPosition, secundus->vColor, secundus->vNormal, "vPosition", "vColor", "vNormal");
    secundus->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(warbird->fileName, warbird->numOfVert, VAO[warbird->id], buffer[warbird->id], shaderProgram,
                                warbird->vPosition, warbird->vColor, warbird->vNormal, "vPosition", "vColor", "vNormal");
    warbird->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(unumSite->fileName, unumSite->numOfVert, VAO[unumSite->id], buffer[unumSite->id], shaderProgram,
                                unumSite->vPosition, unumSite->vColor, unumSite->vNormal, "vPosition", "vColor", "vNormal");
    unumSite->setScaleMatrix(modelSize);
    unumSite->setSitePosition(unum->getModelMatrix(), unum->tiltAngle);
    
    modelSize = loadModelBuffer(secundusSite->fileName, secundusSite->numOfVert, VAO[secundusSite->id], buffer[secundusSite->id], shaderProgram,
                                secundusSite->vPosition, secundusSite->vColor, secundusSite->vNormal, "vPosition", "vColor", "vNormal");
    secundusSite->setScaleMatrix(modelSize);
    secundusSite->setSitePosition(secundus->getModelMatrix(duo->getPlanetMatrix()), secundus->tiltAngle);
    
    modelSize = loadModelBuffer(wbMissile->fileName, wbMissile->numOfVert, VAO[wbMissile->id], buffer[wbMissile->id], shaderProgram,
                                wbMissile->vPosition, wbMissile->vColor, wbMissile->vNormal, "vPosition", "vColor", "vNormal");
    wbMissile->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(usMissile->fileName, usMissile->numOfVert, VAO[usMissile->id], buffer[usMissile->id], shaderProgram,
                                usMissile->vPosition, usMissile->vColor, usMissile->vNormal, "vPosition", "vColor", "vNormal");
    usMissile->setScaleMatrix(modelSize);
    
    modelSize = loadModelBuffer(ssMissile->fileName, ssMissile->numOfVert, VAO[ssMissile->id], buffer[ssMissile->id], shaderProgram,
                                ssMissile->vPosition, ssMissile->vColor, ssMissile->vNormal, "vPosition", "vColor", "vNormal");
    ssMissile->setScaleMatrix(modelSize);
    
    float aspectRatio = (GLfloat)windowWidth / (GLfloat)windowHeight;
    projectionMatrix = glm::perspective(glm::radians(60.0f), aspectRatio, 1.0f, 100000.0f);
    skybox = new Skybox(nModels - 1, VAO[nModels-1], buffer[nModels-1], file1, file2, file3, file4, file5, file6, rawWidth, rawHeight);
//
//    ruber->initializeShape(VAO, buffer, shaderProgram);
//    unum->initializeShape(VAO, buffer, shaderProgram);
//    duo->initializeShape(VAO, buffer, shaderProgram);
//    primus->initializeShape(VAO, buffer, shaderProgram);
//    secundus->initializeShape(VAO, buffer, shaderProgram);
//    warbird->initializeShape(VAO, buffer, shaderProgram);
//    unumSite->initializeShape(VAO, buffer, shaderProgram);
//    secundusSite->initializeShape(VAO, buffer, shaderProgram);
//    wbMissile->initializeShape(VAO, buffer, shaderProgram);
//    usMissile->initializeShape(VAO, buffer, shaderProgram);
//    ssMissile->initializeShape(VAO, buffer, shaderProgram);

	unumSite->setSitePosition(unum->getModelMatrix(), unum->tiltAngle);
	secundusSite->setSitePosition(secundus->getModelMatrix(duo->getPlanetMatrix()), secundus->tiltAngle);

	MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");

	eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 1000 "out of screen" from origin
	at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
	up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
	viewMatrix = glm::lookAt(eye, at, up);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	lastTime = glutGet(GLUT_ELAPSED_TIME);

	warbird->setGravityConst(gravityConstant);
    /*-------------- Shader - Uniforms link -----------------------*/
    MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");
    MV = glGetUniformLocation(shaderProgram, "ModelViewMatrix");
    lightPos = glGetUniformLocation(shaderProgram, "LightPosition");
    lightCol = glGetUniformLocation(shaderProgram, "LightColor");
    eyeDir = glGetUniformLocation(shaderProgram, "EyeDirection");
    
    AMBI = glGetUniformLocation(shaderProgram, "Ambient");
    
    ConeDirection = glGetUniformLocation(shaderProgram, "ConeDirection");
    SpotCosCutoff = glGetUniformLocation(shaderProgram, "SpotCosCutoff");
    SpotExponent = glGetUniformLocation(shaderProgram, "SpotExponent");
    
    PStrength = glGetUniformLocation(shaderProgram, "PStrength");
    DStrength = glGetUniformLocation(shaderProgram, "DStrength");
    SStrength = glGetUniformLocation(shaderProgram, "SStrength");
    /*-------------------------------------------------------------*/
}

// set viewport and projectionMatrix on window resize events
void reshape(int width, int height) {
	float aspectRatio = (GLfloat)width / (GLfloat)height;
	float FOVY = glm::radians(60.0f);
	glViewport(0, 0, width, height);
	printf("reshape: FOVY = %5.2f, width = %4d height = %4d aspect = %5.2f \n",
		FOVY, width, height, aspectRatio);
	projectionMatrix = glm::perspective(FOVY, aspectRatio, 1.0f, 100000.0f);
}

// Use with Idle and intervalTimer functions 
void update(int i) {
	glutTimerFunc(timeQuantum[timeQuantumIndex], update, 1);
	
	//Model updates
	models->setPositions(ruber, unum, duo, primus, secundus, warbird, unumSite, secundusSite, wbMissile, usMissile, ssMissile);
	models->update(ruber, unum, duo, primus, secundus, warbird, unumSite, secundusSite, wbMissile, usMissile, ssMissile);
	
	//Camera updates
	unumCam->update();
	duoCam->update();
	switch (camMode) {
		case 2:
			viewMatrix = unumCam->getCamMatrix(unum->getModelMatrix());
			break;
		case 3:
			viewMatrix = duoCam->getCamMatrix(duo->getModelMatrix());
			break;
		case 4:
			viewMatrix = warbirdCam->getCamMatrix(warbird->getOrientationMatrix());
			break;
		default:
			break;
	}

	//Update Title
	sprintf(wbMissileStr, " %2d, ", warbird->getMissileCount());
	sprintf(usMissileStr, " %2d, ", unumSite->getMissileCount());
	sprintf(ssMissileStr, " %2d, ", secundusSite->getMissileCount());
	switch (timeQuantumIndex) {
		case 0:
			strcpy(sTypeStr, " Ace ");
			break;
		case 1:
			strcpy(sTypeStr, " Pilot ");
			break;
		case 2:
			strcpy(sTypeStr, " Trainee ");
			break;
		case 3:
			strcpy(sTypeStr, " Debug ");
			break;
	}

	//Check if you won
	if (unumSite->isDead() && secundusSite->isDead() && win == false) {
		strcpy(titleStr, winStr);
		glutSetWindowTitle(titleStr);
		printf("You Have Won!");
	}
	if (warbird->isDead() && lose == false) {
		strcpy(titleStr, loseStr);
		glutSetWindowTitle(titleStr);
		printf("You Have Lost!");
	}
}

void arrowInput(int key, int x, int y) {
	int mod = glutGetModifiers();

	switch (key) {
	case GLUT_KEY_UP: //positive step on "at" vector
		if (mod == GLUT_ACTIVE_SHIFT) {
			warbird->movement(4);
		}
		else {
			warbird->movement(0);
		}
		break;
	case GLUT_KEY_DOWN: //negative step on "at" vector
		if (mod == GLUT_ACTIVE_SHIFT) {
			warbird->movement(5);
		}
		else {
			warbird->movement(1);
		}
		break;
	case GLUT_KEY_LEFT: //yaw +0.02 radians on "up" vector
		if (mod == GLUT_ACTIVE_SHIFT) {
			warbird->movement(6);
		}
		else {
			warbird->movement(2);
		}
		break;
	case GLUT_KEY_RIGHT: //yaw -0.02 radians on "up" vector
		if (mod == GLUT_ACTIVE_SHIFT) {
			warbird->movement(7);
		}
		else {
			warbird->movement(3);
		}
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w': case 'W': // warp ship
			if (warbird->isDead() == false) {
				warp++;
				if (warp % 2 == 0) {
					planetCamOM = unumCam->getOrientationMatrix();
					planetOM = unum->getPlanetMatrix();
				}
				else {
					planetCamOM = duoCam->getOrientationMatrix();
					planetOM = duo->getPlanetMatrix();
				}
				warbird->warpTo(planetCamOM, planetOM);
			}
			else {
				printf("Can't warp, ship is dead.\n");
			}
			break;
		case 'f': case 'F': 
			if (warbird->isDead() == false) {
				bool justFired = warbird->fire(wbMissile->hasLaunched());
				if (justFired == true) {
					wbMissile->launch(warbird->getOrientationMatrix());
				}
				else {
					if (warbird->getMissileCount() <= 0) {
						printf("Out of Ammo!\n");
					}
					else {
						printf("Still reloading, please wait.\n");
					}
				}
			}
			else {
				printf("Can't fire, ship is dead.\n");
			}
			break;
		case 'g': case 'G':
			warbird->toggleGravity();
			break;
		case 't': case 'T': // next TQ value
			timeQuantumIndex++;
			if (timeQuantumIndex > 3)
				timeQuantumIndex = 0;
			break;
		case 's': case 'S': // next ship speed
			warbird->changeStep();
			break;
		case 'r': case 'R':
			warbird->signalKOHit();
			printf("You have given up.\n");
			break;
		case 'v': case 'V': // next camera
			camMode++;
			break;
		case 'x': case 'X':// prev camera
			camMode--;
			if (camMode == -1)
				camMode = 4;
			break;
        case 'a': case 'A'://turn on & off ambient light
            if(isAmbiOn){
                Ambient = glm::vec3(0.0f, 0.0f, 0.0f);
                isAmbiOn = false;
            }
            else{
                Ambient = glm::vec3(0.1f, 0.1f, 0.1f);
                isAmbiOn = true;
            }
            break;
        case 'd': case 'D'://turn on & off  Direction light
            if(direcStrength == 0.0){
                direcStrength = 0.3f;
            }
            else{
                direcStrength = 0.0f;
            }
            break;
        case 'p': case 'P'://turn on & off point light
            if(pointStrength == 0.0){
                pointStrength = 0.7f;
            }
            else{
                pointStrength = 0.0f;
            }
            break;
		case 033: case 'q': case 'Q':
			exit(EXIT_SUCCESS);
	}

	switch (camMode % 5) {
		case 0:  // front view
			eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 2000 "out of screen" from origin
			at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
			up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
			strcpy(viewStr, " Front View,");
			viewMatrix = glm::lookAt(eye, at, up);
			break;
		case 1:  // top view
			eye = glm::vec3(0.0f, 20000.0f, 0.0f);
			at = glm::vec3(0.0f, 0.0f, 0.0f);
			up = glm::vec3(0.0f, 0.0f, -1.0f);
			strcpy(viewStr, " Top View,");
			viewMatrix = glm::lookAt(eye, at, up);
			break;
		case 2: // unum view
			strcpy(viewStr, " Unum view,");
			viewMatrix = unumCam->getCamMatrix(unum->getModelMatrix());
			break;
		case 3: // duo view 
			strcpy(viewStr, " Duo View,");
			viewMatrix = duoCam->getCamMatrix(duo->getModelMatrix());
			break;
		case 4:  // warbird view
			strcpy(viewStr, " WarBird View,");
			viewMatrix = warbirdCam->getCamMatrix(warbird->getOrientationMatrix());
			break;
		default:
			break;
	}

	if (win == false && lose == false) updateTitle();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	# ifdef __Mac__
		// Can't change the version in the GLUT_3_2_CORE_PROFILE
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
	# endif
	# ifndef __Mac__
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	# endif
		glutInitWindowSize(800, 600);
		// set OpenGL and GLSL versions to 3.3 for Comp 465/L, comment to see highest versions
	# ifndef __Mac__
		glutInitContextVersion(3, 3);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	# endif
	glutCreateWindow("The Dankest Universe");
	glewExperimental = GL_TRUE;  // needed my home system 
	GLenum err = glewInit();
	if (GLEW_OK != err)
		printf("GLEW Error: %s \n", glewGetErrorString(err));
	else {
		printf("Using GLEW %s \n", glewGetString(GLEW_VERSION));
		printf("OpenGL %s, GLSL %s\n",
			glGetString(GL_VERSION),
			glGetString(GL_SHADING_LANGUAGE_VERSION));
	}
	// initialize scene here
	init();
	// set glut callback functions here
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowInput);
	glutTimerFunc(timeQuantum[timeQuantumIndex], update, 1);  // keep the window up
	glutIdleFunc(display);
	glutMainLoop();
	printf("done\n");
	return 0;
}
