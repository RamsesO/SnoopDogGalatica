/*
	Snoop Dogg Galatica
	The Dankest Solar System
	Dizon, Lemuel
	Ordonez, Ramses
*/

# define __Windows__ // define your target operating system
# include "../includes465/include465.hpp"
# include "Shape.hpp"
# include "Sun.hpp"
# include "Planet.hpp"
# include "Moon.hpp"

// Model Files (0 = Ruber, 1 = Unum, 2 = Duo, 3 = Primus, 4 = Secundus, 5 = WarBird 6 = Missle
const int nModels = 7;
Sun * ruber = new Sun(0, 1740 * 3, "assets/Ruber.tri", 2000.0f, glm::vec3(0), 
	glm::vec3(0, 1, 0), 1.0f);
Planet * unum = new Planet(1, 1740 * 3, "assets/Unum.tri", 200.0f, glm::vec3(4000, 0, 0), 
	glm::vec3(0, 1, 0), 9.0f, glm::vec3(0, 1, 0), 0.004f, glm::vec3(0, 0, 1), 0.5f);
Planet * duo = new Planet(2, 16020 * 3, "assets/Duo.tri", 400.0f, glm::vec3(9000, 0, 0),
	glm::vec3(0, 1, 0), 5.0f, glm::vec3(0, 1, 0), 0.002f, glm::vec3(0, 0, 1), -0.3f);
Moon * primus = new Moon(3, 1740 * 3, "assets/Primus.tri", 100.0f, glm::vec3(2000, 0, 0),
	glm::vec3(0, 1, 0), 22.0f, glm::vec3(0, 1, 0), 0.05f, glm::vec3(0, 0, 1), 0.4f);
Moon * secundus = new Moon(4, 1740 * 3, "assets/Secundus.tri", 150.0f, glm::vec3(4000, 0, 0),
	glm::vec3(0, 1, 0), 12.0f, glm::vec3(0, 1, 0), 0.025f, glm::vec3(0, 0, 1), -0.5f);
Sun * warbird = new Sun(5, 4852 * 3, "assets/WarBird.tri", 100.0f, glm::vec3(15000, 0, 0),
	glm::vec3(0, 1, 0), 1.0f);
Sun * missle = new Sun(6, 918 * 3, "assets/Missle.tri", 25.0f, glm::vec3(14500, 0, 0),
	glm::vec3(0, 1, 0), 1.0f);

//Title Information
char baseStr[75] = "Snoop Dogg Galatica (keys: f, t, w, m, u, d)";
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

double currentTime;
double lastTime;
double timeInterval;

//special camera modes
int flag = 0;
glm::mat4 unumModelMatrix;
float * unumPos;
glm::mat4 duoModelMatrix;
float * duoPos;

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
		unum->vPosition, unum->vColor, unum->vNormal,"vPosition", "vColor", "vNormal");
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
	at  = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
	up  = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
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

	//camera updates
	switch (flag) {
		case 1:
			unumModelMatrix = unum->getModelMatrix();
			unumPos = (float*)glm::value_ptr(unumModelMatrix);

			eye = glm::vec3(unumPos[12]-4000.0f, 0.0f, unumPos[14]-4000.0f);
			at = glm::vec3(unumPos[12], unumPos[13], unumPos[14]);
			up = glm::vec3(0.0f, 1.0f, 0.0f);

			viewMatrix = glm::lookAt(eye, at, up);
			break;
		case 2:
			duoModelMatrix = duo->getModelMatrix();
			duoPos = (float*)glm::value_ptr(duoModelMatrix);

			eye = glm::vec3(duoPos[12]-4000.0f, 0.0f, duoPos[14]-4000.0f);
			at = glm::vec3(duoPos[12], duoPos[13], duoPos[14]);
			up = glm::vec3(0.0f, 1.0f, 0.0f);

			viewMatrix = glm::lookAt(eye, at, up);
			break;
		default:
			break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	duoModelMatrix = duo->getModelMatrix();
	duoPos = (float*)glm::value_ptr(duoModelMatrix);

	unumModelMatrix = unum->getModelMatrix();
	unumPos = (float*)glm::value_ptr(unumModelMatrix);

	switch (key) {
		case 033: case 'q':  case 'Q': 
			exit(EXIT_SUCCESS); 
			break;
		case 'f': case 'F':  // front view
			flag = 0;
			eye = glm::vec3(0.0f, 10000.0f, 20000.0f);   // eye is 2000 "out of screen" from origin
			at = glm::vec3(0.0f, 0.0f, 0.0f);   // looking at origin
			up = glm::vec3(0.0f, 1.0f, 0.0f);   // camera'a up vector
			strcpy(viewStr, " Front View,"); 
			break;
		case 't': case 'T':  // top view
			flag = 0;
			eye = glm::vec3(0.0f, 20000.0f, 0.0f);   
			at = glm::vec3(0.0f, 0.0f, 0.0f);   
			up = glm::vec3(0.0f, 0.0f, -1.0f);   
			strcpy(viewStr, " Top View,"); 
			break;
		case 'w': case 'W':  // warbird view
			flag = 0;
			eye = glm::vec3(15000.0f, 250.0f, 250.0f);
			at = glm::vec3(15000.0f, 0.0f, 0.0f);
			up = glm::vec3(0.0f, 1.0f, 0.0f);
			strcpy(viewStr, " WarBird View,");
			break;
		case 'm': case 'M':  // missle view
			flag = 0;
			eye = glm::vec3(14500.0f, 250.0f, 250.0f);
			at = glm::vec3(14500.0f, 0.0f, 0.0f);
			up = glm::vec3(0.0f, 1.0f, 0.0f);
			strcpy(viewStr, " Missle View,");
			break;
		case 'u': case 'U': // unum view
			flag = 1;
			eye = glm::vec3(unumPos[12] - 4000.0f, 0.0f, unumPos[14] - 4000.0f);
			at = glm::vec3(unumPos[12], unumPos[13], unumPos[14]);
			up = glm::vec3(0.0f, 1.0f, 0.0f);
			strcpy(viewStr, " Unum view,"); 
			break;
		case 'd': case 'D': // duo view 
			flag = 2;
			eye = glm::vec3(duoPos[12] - 4000.0f, 0.0f, duoPos[14] - 4000.0f);
			at = glm::vec3(duoPos[12], duoPos[13], duoPos[14]);
			up = glm::vec3(0.0f, 1.0f, 0.0f);
			strcpy(viewStr, " Duo View,");
			break;
	}
	viewMatrix = glm::lookAt(eye, at, up);
	updateTitle();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	// Uncomment the following line to force OpenGL & GLSL 3.3
	// glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("Starter source file for 465L");
	// initialize and verify glew
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
	glutTimerFunc(timerDelay, update, 1);  // keep the window up
	glutIdleFunc(display);
	glutMainLoop();
	printf("done\n");
	return 0;
}
