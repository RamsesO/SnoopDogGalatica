/*
  Snoop Dogg Galatica
  The Dankest Solar System
  Dizon, Lemuel
  Ordonez, Ramses
*/

# define __Mac__ 
# include "../../../includes465/include465.hpp"

// constants for models:  file names, vertex count, model display size
const int nModels = 7;  // number of models in this scene
char * modelFile [nModels] = {"../assets/Ruber.tri", "../assets/Primus.tri", "../assets/Duo.tri", "../assets/Secundus.tri", "../assets/Unum.tri", "../assets/WarBird.tri", "../assets/Missle.tri"};

float modelBR[nModels];       // model's bounding radius
float scaleValue[nModels];    // model's scaling "size" value
const int nVertices[nModels] = { 1740 * 3, 1740 * 3, 1740 * 3, 1740*3, 16020*3, 4852*3, 918*3 };
char * vertexShaderFile   = "../simpleVertex.glsl";     
char * fragmentShaderFile = "../simpleFragment.glsl";    
GLuint shaderProgram; 
GLuint VAO[nModels];      // Vertex Array Objects
GLuint buffer[nModels];   // Vertex Buffer Objects

// Shader handles, matrices, etc
GLuint MVP ;  // Model View Projection matrix's handle
GLuint vPosition[nModels], vColor[nModels], vNormal[nModels];   // vPosition, vColor, vNormal handles for models
// model, view, projection matrices and values to create modelMatrix.
float modelSize[nModels] = { 2000.0f, 100.0f, 400.0f, 150.0f, 200.0f, 100.0f, 25.0f };   // size of model
glm::vec3 scale[nModels];       // set in init()
glm::vec3 translate[nModels] = {glm::vec3(0,0,0), glm::vec3(11000, 0, 0), glm::vec3(9000,0,0), glm::vec3(13000,0,0), glm::vec3(4000,0,0), glm::vec3(15000,0,0), glm::vec3(14500,0,0)};
glm::mat4 modelMatrix;          // set in display()
glm::mat4 viewMatrix;           // set in init()
glm::mat4 projectionMatrix;     // set in reshape()
glm::mat4 ModelViewProjectionMatrix; // set in display();

//int timerDelay = 40;

// window title string
char titleStr [50]= "465 manyModelsStatic Example ";

void reshape(int width, int height) {
  float aspectRatio = (float) width / (float) height;
  float FOVY = glm::radians(60.0f);
  glViewport(0, 0, width, height);
  printf("reshape: FOVY = %5.2f, width = %4d height = %4d aspect = %5.2f \n", 
    FOVY, width, height, aspectRatio);
  projectionMatrix = glm::perspective(FOVY, aspectRatio, 1.0f, 100000.0f); 
  }

void keyboard(unsigned char key, int x, int y) {
	  switch(key) {
    case 033 : case 'q' :  case 'Q' : exit(EXIT_SUCCESS); break;
    case 'd':
      viewMatrix = glm::lookAt(
        glm::vec3(-4000.0f, 0.0f,  -4000.0f),   // eye is 3000 up from origin
        translate[2],   // looking at origin  
        glm::vec3(0.0f,    1.0f, 0.0f));   // camera's up is looking towards -Z vector
        //strcpy(viewStr, " top view"); 
        break;
    case 'f' : case 'F' :  // front view
      printf("front view \n");
      viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 10000.0f, 20000.0f),  // eye position
        glm::vec3(0),                  // look at position
        glm::vec3(0.0f, 1.0f, 0.0f)); // up vect0r
        //strcpy(viewStr, " front view"); 
        break;
    case 'b' : case 'B' :  // bottom view
        viewMatrix = glm::lookAt(
          glm::vec3(0.0f, -20000.0f, 0.0f),  // eye is 1000 right from origin
          glm::vec3(   0.0f, 0.0f, 0.0f),   // looking at origin
          glm::vec3(   0.0f, 0.0f, 1.0f));   // camera'a up vector
        //strcpy(viewStr, " right view"); 
        break;
    case 't' : case 'T' :  // top view
      viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 20000.0f,  0.0f),  // eye is 3000 up from origin
        glm::vec3(0.0f,    0.0f,  0.0f),  // looking at origin  
        glm::vec3(0.0f,    0.0f, -1.0f));   // camera's up is looking towards -Z vector
        //strcpy(viewStr, " top view"); 
        printf("top view \n");
      break;
    case 'u':
      viewMatrix = glm::lookAt(
        glm::vec3(-4000.0f, 0.0f,  -4000.0f),   // eye is 3000 up from origin
        translate[4],   // looking at origin  
        glm::vec3(0.0f,    1.0f, 0.0f));   // camera's up is looking towards -Z vector
        //strcpy(viewStr, " top view"); 
        break;
  }

	}

// void update(int i){
//   glutTimerFunc(timerDelay, update, 1);
//   for(int  i = 0; i<nModels; i++){
    
//   }
// }

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // update model matrix, bind model and draw
  for(int m = 0; m < nModels; m++) {
    modelMatrix = glm::translate(glm::mat4(), translate[m]) * 
      glm::scale(glm::mat4(), glm::vec3(scale[m]));
    ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix; 
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		glBindVertexArray(VAO[m]);
    glDrawArrays(GL_TRIANGLES, 0, nVertices[m] ); 
    }
  glutSwapBuffers();
  }

// load the shader programs, vertex data from model files, create the solids, set initial view
void init() {
  // load the shader programs
  shaderProgram = loadShaders(vertexShaderFile,fragmentShaderFile);
  glUseProgram(shaderProgram);
  
  // generate VAOs and VBOs
  glGenVertexArrays( nModels, VAO );
  glGenBuffers( nModels, buffer );
  // load the buffers from the model files
  for (int i = 0; i < nModels; i++) {
    modelBR[i] = loadModelBuffer(modelFile[i], nVertices[i], VAO[i], buffer[i], shaderProgram,
      vPosition[i], vColor[i], vNormal[i], "vPosition", "vColor", "vNormal"); 
    // set scale for models given bounding radius  
    scale[i] = glm::vec3( modelSize[i] * 1.0f/modelBR[i]);
    }
  
  MVP = glGetUniformLocation(shaderProgram, "ModelViewProjection");

 /*
  printf("Shader program variable locations:\n");
  printf("  vPosition = %d  vColor = %d  vNormal = %d MVP = %d\n",
    glGetAttribLocation( shaderProgram, "vPosition" ),
    glGetAttribLocation( shaderProgram, "vColor" ),
    glGetAttribLocation( shaderProgram, "vNormal" ), MVP);
 */

 viewMatrix = glm::lookAt(
        glm::vec3(0.0f, 10000.0f,  20000.0f),  // eye is 3000 up from origin
        glm::vec3(0.0f,    0.0f,  0.0f),  // looking at origin  
        glm::vec3(0.0f,    0.0f, -1.0f));   // camera's up is looking towards -Z vector

  // set render state values
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
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
  // initialize scene
  init();
  // set glut callback functions
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
  //glutTimerFunc(timerDelay, update, 1);
  glutIdleFunc(display);
  glutMainLoop();
  printf("done\n");
  return 0;
  }
  
