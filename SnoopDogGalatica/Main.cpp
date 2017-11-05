/*
	Snoop Dogg Galatica
	The Dankest Solar System
	Dizon, Lemuel
	Ordonez, Ramses
*/

#define __Windows__
# include "../includes465/include465.hpp"
# include "Shape.hpp"
# include "Sun.hpp"
# include "Planet.hpp"
# include "Moon.hpp"
# include "PlanetCam.hpp"
# include "WarBird.hpp"
# include "WarBirdCam.hpp"

// Model Files (0 = Ruber, 1 = Unum, 2 = Duo, 3 = Primus, 4 = Secundus, 5 = WarBird 6 = Missle
const int nModels = 7;
Sun * ruber = new Sun(0, 1740 * 3, "assets/Ruber.tri", 2000.0f, glm::vec3(0),
	glm::vec3(0, 1, 0), 1.0f);
Planet * unum = new Planet(1, 1740 * 3, "assets/Unum.tri", 200.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 9.0f, glm::vec3(0, 1, 0), 0.004f, glm::vec3(0, 0, 1), 0.5f);
Planet * duo = new Planet(2, 16020 * 3, "assets/Duo.tri", 400.0f, glm::vec3(9000, 0, 0),
	glm::vec3(0, 1, 0), 5.0f, glm::vec3(0, 1, 0), 0.002f, glm::vec3(0, 0, 1), -0.3f);
Moon * primus = new Moon(3, 1740 * 3, "assets/Primus.tri", 100.0f, glm::vec3(2000, 0, 0),
	glm::vec3(0, 1, 0), 22.0f, glm::vec3(0, -1, 0), 0.05f, glm::vec3(0, 0, 1), 0.4f);
Moon * secundus = new Moon(4, 1740 * 3, "assets/Secundus.tri", 150.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 12.0f, glm::vec3(0, 1, 0), 0.025f, glm::vec3(0, 0, 1), -0.5f);
WarBird * warbird = new WarBird(5, 4852 * 3, "assets/WarBird.tri", 100.0f, glm::vec3(15000, 0, 0),
	glm::vec3(0, 1, 0), 0.0f);
Sun * missle = new Sun(6, 918 * 3, "assets/Missle.tri", 25.0f, glm::vec3(14500, 0, 0),
	glm::vec3(0, 1, 0), 1.0f);

//Planetary Cameras
PlanetCam * unumCam = new PlanetCam(glm::vec3(4000 - 4000, 0, -4000), glm::vec3(0, 1, 0), 0.004f);
PlanetCam * duoCam = new PlanetCam(glm::vec3(9000 - 4000, 0, -4000), glm::vec3(0, 1, 0), 0.002f);

//Warbird Camera
WarBirdCam * warbirdCam = new WarBirdCam(glm::vec3(0, 300, 1000));

//Title Information
char baseStr[75] = "Snoop Dogg Galatica (keys: x, v)";
char viewStr[15] = " Front View,";
char fpsStr[15];
char titleStr[150];

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
int timerDelay = 40; // 40 millisecond delay approximates 35 fps
int frameCount = 0;

int flag = 0;
int currCam = 0;

double currentTime;
double lastTime;
double timeInterval;


//ship variables
bool gravity = false;

void updateTitle() {
	strcpy(titleStr, baseStr);
	strcat(titleStr, viewStr);
	strcat(titleStr, fpsStr);
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

	modelMatrix = missle->getModelMatrix();
	ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
	glBindVertexArray(VAO[missle->id]);
	glDrawArrays(GL_TRIANGLES, 0, missle->numOfVert);

	glutSwapBuffers();
	frameCount++;

	// see if a second has passed to set estimated fps information
	currentTime = glutGet(GLUT_ELAPSED_TIME);  // get elapsed system time
	timeInterval = currentTime - lastTime;
	if (timeInterval >= 1000) {
		sprintf(fpsStr, " FPS: %4d", (int)(frameCount / (timeInterval / 1000.0f)));
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

	modelSize = loadModelBuffer(missle->fileName, missle->numOfVert, VAO[missle->id], buffer[missle->id], shaderProgram,
		missle->vPosition, missle->vColor, missle->vNormal, "vPosition", "vColor", "vNormal");
	missle->setScaleMatrix(modelSize);

	MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");

	eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 1000 "out of screen" from origin
	at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
	up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
	viewMatrix = glm::lookAt(eye, at, up);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	lastTime = glutGet(GLUT_ELAPSED_TIME);
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
	glutTimerFunc(timerDelay, update, 1);
	ruber->update();
	unum->update();
	duo->update();
	primus->update();
	secundus->update();
	warbird->update();
	missle->update();
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
		viewMatrix = warbirdCam->getCamMatrix(warbird->getWarbirdMatrix());
	default:
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

		break;
	case 'f': case 'F': // fire missile

		break;
	case 'g': case 'G': // toggle gravity
		gravity = !gravity;
		break;
	case 't': case 'T': // next TQ value

		break;
	case 's': case 'S': // next ship speed
		warbird->changeStep();
		break;
	case 'v': case 'V': // next camera
		currCam++;
		if (currCam == 6)
			currCam = 0;
		break;
	case 'x': case 'X':// prev camera
		currCam--;
		if (currCam == -1)
			currCam = 5;
		break;
	case 033: case 'q': case 'Q':
		exit(EXIT_SUCCESS);
	}


	switch (currCam % 6) {
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
	case 2:  // warbird view
		flag = 3;
		viewMatrix = warbirdCam->getCamMatrix(warbird->getWarbirdMatrix());
		strcpy(viewStr, " WarBird View,");
		break;
	case 3:  // missle view
		flag = 0;
		eye = glm::vec3(14500.0f, 250.0f, 250.0f);
		at = glm::vec3(14500.0f, 0.0f, 0.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		strcpy(viewStr, " Missle View,");
		viewMatrix = glm::lookAt(eye, at, up);
		break;
	case 4: // unum view
		flag = 1;
		strcpy(viewStr, " Unum view,");
		viewMatrix = unumCam->getCamMatrix(unum->getModelMatrix());
		break;
	case 5: // duo view 
		flag = 2;
		strcpy(viewStr, " Duo View,");
		viewMatrix = duoCam->getCamMatrix(duo->getModelMatrix());
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
	glutCreateWindow("lit solar system");
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
	glutTimerFunc(timerDelay, update, 1);  // keep the window up
	glutIdleFunc(display);
	glutMainLoop();
	printf("done\n");
	return 0;
}