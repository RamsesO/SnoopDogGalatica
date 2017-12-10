
# define __Mac__ // define your target operating system
# include "../../includes465/include465.hpp"
# include "../../includes465/texture465.hpp"  // freeTexture(...), loadRawTexture(...)
# include "Skybox.hpp"

#define nModels 1
char * fileName = "../assets/stars.raw";
int rawWidth = 512;
int rawHeight = 512;

Skybox * skybox;


GLuint NormalMatrix, MVP;  // ModelViewProjection handle
glm::mat4 projectionMatrix;     // set in display
glm::mat4 modelViewMatrix;      // set in display()
glm::mat3 normalMatrix;         // set in display()
glm::mat4 modelViewProjectionMatrix;  // set in display()
glm::mat4 rotationMatrix;       // set in init() and spin()
glm::mat4 viewMatrix;
glm::mat4 modelMatrix;

// vectors and values for lookAt
glm::vec3 eye, at, up;

int width = 800, height =600;

GLuint vao[nModels];
GLuint vbo[nModels];

void init (void) {
  glGenVertexArrays(nModels, vao);
  glGenBuffers(nModels, vbo);

  skybox = new Skybox(0, vao[0], vbo[0], fileName, rawWidth, rawHeight);

// initially use a front view
  eye = glm::vec3(50.0f, 50.0f, 50.0f);   // eye is 300 "out of screen" from origin
  at  = glm::vec3(  0.0f,   0.0f,   0.0f);   // looking at origin
  up  = glm::vec3(  0.0f,   1.0f,   0.0f);   // camera'a up vector

}

void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  projectionMatrix = glm::perspective(glm::radians(60.0f), (GLfloat) width /  (GLfloat) height, 1.0f, 5000.0f); 
  }

void display(void) {
  viewMatrix = glm::lookAt(eye,at,up);
  projectionMatrix = glm::perspective(glm::radians(60.0f), (GLfloat) width /  (GLfloat) height, 1.0f, 1000.0f); 
  skybox -> update(viewMatrix, projectionMatrix);


  glutSwapBuffers();
  }


void keyboard (unsigned char key, int x, int y) {
   switch (key) {
   case 033: case 'q':  case 'Q': exit(EXIT_SUCCESS); break;
   
    case 'b' : case 'B' :  // bottom view
        eye = glm::vec3( 0.0f,-1000.0f, 0.0f);   
        at  = glm::vec3( 0.0f,    0.0f, 0.0f);   
        up  = glm::vec3( 0.0f,    0.0f, 1.0f);  
        break;
    case 'f' : case 'F' :  // front view
        eye = glm::vec3( 0.0f, 300.0f, 700.0f);   
        at  = glm::vec3( 0.0f,   0.0f,   0.0f);   
        up  = glm::vec3( 0.0f,   1.0f,   0.0f);  
        break;
    case 't' : case 'T' :  // top view
        eye = glm::vec3(0.0f, 700.0f,  0.0f);   
        at  = glm::vec3(0.0f,   0.0f,  0.0f);   
        up  = glm::vec3(0.0f,   0.0f, -1.0f);   
        break;
    }
  glutPostRedisplay();
  }
    
// for use with Idle and intervalTimer functions 
// to set rotation
void spin (int i) { 
  glutTimerFunc(40, spin, 1);
  glutPostRedisplay();
  }


int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  // glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  // glutInitWindowSize(800, 600);
  // // Uncomment the following line to force OpenGL & GLSL 3.3
  // // glutInitContextVersion(3, 3);
  // glutInitContextProfile(GLUT_CORE_PROFILE);
  // glutCreateWindow("Starter source file for 465L");
  // // initialize and verify glew
  # ifdef __Mac__
  // Can't change the version in the GLUT_3_2_CORE_PROFILE
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
# endif
# ifndef __Mac__
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
# endif
  glutInitWindowSize(width, height);
  // set OpenGL and GLSL versions to 3.3 for Comp 465/L, comment to see highest versions
# ifndef __Mac__
  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE);
# endif
  glutCreateWindow("465 Texture Model {b, f, t, l} : front view front light");
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
  glutTimerFunc(40, spin, 1);
  glutMainLoop();
  printf("exit main() \n");
  return 0;
  }