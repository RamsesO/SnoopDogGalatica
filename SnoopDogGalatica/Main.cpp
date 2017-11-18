/*
	Snoop Dogg Galatica
	The Dankest Solar System

	Dizon, Lemuel
	Ordonez, Ramses
	Kim, Kelly
*/

# define __Mac__
# include "../includes465/include465.hpp"
# include "Shape.hpp"
# include "Collision.hpp"
# include "Entity.hpp"
# include "Gravity.hpp"
# include "Sun.hpp"
# include "Planet.hpp"
# include "Moon.hpp"
# include "PlanetCam.hpp"
# include "WarBird.hpp"
# include "Missile.hpp"
# include "WarBirdCam.hpp"
# include "MissileSite.hpp"

// Model Files (0 = Ruber, 1 = Unum, 2 = Duo, 3 = Primus, 4 = Secundus, 5 = WarBird 6 = Missle
const int nModels = 11;
Sun * ruber = new Sun(0, 1740 * 3, "assets/Ruber.tri", 2000.0f, glm::vec3(0),
	glm::vec3(0, 1, 0), 1.0f);
Planet * unum = new Planet(1, 1740 * 3, "assets/Unum.tri", 200.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 9.0f, glm::vec3(0, 1, 0), 0.004f, glm::vec3(0, 0, 1), 0.5f);
Planet * duo = new Planet(2, 16020 * 3, "assets/Duo.tri", 400.0f, glm::vec3(9000, 0, 0),
	glm::vec3(0, 1, 0), 5.0f, glm::vec3(0, 1, 0), 0.002f, glm::vec3(0, 0, 1), -0.3f);
Moon * primus = new Moon(3, 1740 * 3, "assets/Primus.tri", 100.0f, glm::vec3(2000, 0, 0),
	glm::vec3(0, 1, 0), 22.0f, glm::vec3(0, -1, 0), 0.025f, glm::vec3(0, 0, 1), -0.4f);
Moon * secundus = new Moon(4, 1740 * 3, "assets/Secundus.tri", 150.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 12.0f, glm::vec3(0, 1, 0), 0.012f, glm::vec3(0, 0, 1), 0.5f);
WarBird * warbird = new WarBird(5, 4852 * 3, "assets/WarBird.tri", 100.0f, glm::vec3(15000, 0, 0), 9, 1);
MissileSite * unumSite = new MissileSite(6, 2048 * 3, "assets/MissileSite.tri", 100.0f, 5, 1, true);
MissileSite * secundusSite = new MissileSite(7, 2048 * 3, "assets/MissileSite.tri", 75.5f, 5, 1, true);
Missile * wbMissile = new Missile(8, 0, 918 * 3, "assets/Missle.tri", 25.0f * 20);
Missile * usMissile = new Missile(9, 1, 918 * 3, "assets/Missle.tri", 25.0f);
Missile * ssMissile = new Missile(10, 2, 918 * 3, "assets/Missle.tri", 25.0f);

//Planetary Cameras
PlanetCam * unumCam = new PlanetCam(glm::vec3(4000 - 4000, 0, -4000), glm::vec3(0, 1, 0), 0.004f);
PlanetCam * duoCam = new PlanetCam(glm::vec3(9000 - 4000, 0, -4000), glm::vec3(0, 1, 0), 0.002f);

//Warbird Camera
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
char unumStr[15] = "UnumSite";
char usMissileStr[15];
char secStr[15] = "SecundusSite";
char ssMissileStr[15];
char upsStr[15];
char fpsStr[15];
char viewStr[15] = " Front View, ";
char sTypeStr[15] = " Ace ";
char speedStr[15] = "Speed";

char * vertexShaderFile = "simpleVertex.glsl";
char * fragmentShaderFile = "simpleFragment.glsl";
GLuint shaderProgram;
GLuint VAO[nModels];      // Vertex Array Objects
GLuint buffer[nModels];   // Vertex Buffer Objects

GLuint MVP;
glm::vec3 eye, at, up;
glm::mat4 viewMatrix;                // set in init()
glm::mat4 modelMatrix;
glm::mat4 projectionMatrix;          // set in reshape()
glm::mat4 ModelViewProjectionMatrix; // set in display();
GLfloat aspectRatio;

//Time Keepers
int timeQuantum[] = { 5, 40, 100, 500 };
int timeQuantumIndex = 0;
int frameCount = 0;

int flag = 0;
int currCam = 0;

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

	modelMatrix = ruber->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[ruber->id]);
	glDrawArrays(GL_TRIANGLES, 0, ruber->numOfVert);

	modelMatrix = unum->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[unum->id]);
	glDrawArrays(GL_TRIANGLES, 0, unum->numOfVert);

	modelMatrix = duo->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[duo->id]);
	glDrawArrays(GL_TRIANGLES, 0, duo->numOfVert);

	modelMatrix = primus->getModelMatrix(duo->getPlanetMatrix());
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[primus->id]);
	glDrawArrays(GL_TRIANGLES, 0, primus->numOfVert);

	modelMatrix = secundus->getModelMatrix(duo->getPlanetMatrix());
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[secundus->id]);
	glDrawArrays(GL_TRIANGLES, 0, secundus->numOfVert);

	modelMatrix = warbird->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[warbird->id]);
	glDrawArrays(GL_TRIANGLES, 0, warbird->numOfVert);

	modelMatrix = unumSite->getModelMatrix(unum->getHubMatrix());
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[unumSite->id]);
	glDrawArrays(GL_TRIANGLES, 0, unumSite->numOfVert);

	modelMatrix = secundusSite->getModelMatrix(secundus->getHubMatrix(duo->getPlanetMatrix()));
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[secundusSite->id]);
	glDrawArrays(GL_TRIANGLES, 0, secundusSite->numOfVert);

	modelMatrix = wbMissile->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[wbMissile->id]);
	glDrawArrays(GL_TRIANGLES, 0, wbMissile->numOfVert);

	modelMatrix = usMissile->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[usMissile->id]);
	glDrawArrays(GL_TRIANGLES, 0, usMissile->numOfVert);

	modelMatrix = ssMissile->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[ssMissile->id]);
	glDrawArrays(GL_TRIANGLES, 0, ssMissile->numOfVert);

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
		updateTitle();
	}
}

void init(void) {
	shaderProgram = loadShaders(vertexShaderFile, fragmentShaderFile);
	glUseProgram(shaderProgram);

	glGenVertexArrays(nModels, VAO);
	glGenBuffers(nModels, buffer);

	float modelSize = loadModelBuffer(ruber->fileName, ruber->numOfVert, VAO[ruber->id], buffer[ruber->id], shaderProgram,
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

	MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");

	eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 1000 "out of screen" from origin
	at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
	up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
	viewMatrix = glm::lookAt(eye, at, up);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	lastTime = glutGet(GLUT_ELAPSED_TIME);

	warbird->setGravityConst(gravityConstant);
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
	ruber->update();
	unum->update();
	duo->update();
	primus->update();
	secundus->update();
	warbird->update(ruber->getOrientationMatrix(), ruber->getSize()/2, unum->getPlanetMatrix(), unum->getSize(), duo->getPlanetMatrix(), duo->getSize(),
		primus->getHubMatrix(duo->getPlanetMatrix()), primus->getSize(), secundus->getHubMatrix(duo->getPlanetMatrix()), secundus->getSize());
	wbMissile->update(warbird->getOrientationMatrix(), ruber->getOrientationMatrix(), ruber->getSize()/2, unum->getPlanetMatrix(), unum->getSize(), duo->getPlanetMatrix(), duo->getSize(),
		primus->getHubMatrix(duo->getPlanetMatrix()), primus->getSize(), secundus->getHubMatrix(duo->getPlanetMatrix()), secundus->getSize());
	usMissile->update(warbird->getOrientationMatrix(), ruber->getOrientationMatrix(), ruber->getSize()/2, unum->getPlanetMatrix(), unum->getSize(), duo->getPlanetMatrix(), duo->getSize(),
		primus->getHubMatrix(duo->getPlanetMatrix()), primus->getSize(), secundus->getHubMatrix(duo->getPlanetMatrix()), secundus->getSize());
	ssMissile->update(warbird->getOrientationMatrix(), ruber->getOrientationMatrix(), ruber->getSize()/2, unum->getPlanetMatrix(), unum->getSize(), duo->getPlanetMatrix(), duo->getSize(),
		primus->getHubMatrix(duo->getPlanetMatrix()), primus->getSize(), secundus->getHubMatrix(duo->getPlanetMatrix()), secundus->getSize());
	unumCam->update();
	duoCam->update();

	//camera updates
	switch (flag) {
		case 1:
			viewMatrix = unumCam->getCamMatrix(unum->getModelMatrix());
			break;
		case 2:
			viewMatrix = duoCam->getCamMatrix(duo->getModelMatrix());
			break;
		case 3:
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

			break;
		case 'f': case 'F': // fire missile only if its not fired yet.
			if(!wbMissile->reloading()){
				wbMissile->fire(warbird->getOrientationMatrix());
				warbird->fire(false); // sending false since it is tested above
			}
			break;
		case 'g': case 'G': // toggle gravity for ship
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
		case 'v': case 'V': // next camera
			currCam++;
			break;
		case 'x': case 'X':// prev camera
			currCam--;
			if (currCam == -1)
				currCam = 4;
			break;
		case 033: case 'q': case 'Q':
			exit(EXIT_SUCCESS);
	}

	switch (currCam % 5) {
		case 0:  // front view
			flag = 0;
			eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 2000 "out of screen" from origin
			at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
			up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
			strcpy(viewStr, " Front View,");
			viewMatrix = glm::lookAt(eye, at, up);
			break;
		case 1:  // top view
			flag = 0;
			eye = glm::vec3(0.0f, 20000.0f, 0.0f);
			at = glm::vec3(0.0f, 0.0f, 0.0f);
			up = glm::vec3(0.0f, 0.0f, -1.0f);
			strcpy(viewStr, " Top View,");
			viewMatrix = glm::lookAt(eye, at, up);
			break;
		case 2: // unum view
			flag = 1;
			strcpy(viewStr, " Unum view,");
			viewMatrix = unumCam->getCamMatrix(unum->getModelMatrix());
			break;
		case 3: // duo view 
			flag = 2;
			strcpy(viewStr, " Duo View,");
			viewMatrix = duoCam->getCamMatrix(duo->getModelMatrix());
			break;
		case 4:  // warbird view
			flag = 3;
			strcpy(viewStr, " WarBird View,");
			viewMatrix = warbirdCam->getCamMatrix(warbird->getOrientationMatrix());
			break;
		default:
			break;
	}

	updateTitle();
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