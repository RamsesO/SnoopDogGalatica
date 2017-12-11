/*
	Skybox.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	12/9/2017
*/

# ifndef __INCLUDES465__
# include "../../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SKYBOX__
# include <string>
# include <stdlib.h>

class Skybox {
    
private:

    const int numSides = 6;
    const char * vsFile = "skyboxvs.glsl";
    const char * fsFile = "skyboxfs.glsl";
    const float skyBoxVertices[108] = {
        // positions 
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
        };

    GLuint vao;
    GLuint vbo;

    GLuint textureID;
    GLuint skyboxID;
    GLuint mvpID;

    GLuint shaderProgram;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelMatrix;

    glm::vec3 eye,at,up;

    int rawWidth;
    int rawHeight;

    char * fileArray[6];

    GLuint loadCubeMap()
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        FILE * file;
        int readResult; 

        for (unsigned int i = 0; i < numSides; i++)
        {
            file = fopen(fileArray[i], "rb");
            if ( file == NULL ) {
                printf("File %s can't be opened\n", fileArray[i]);
                return 0;
            }
            unsigned char * data = (unsigned char *) malloc( rawWidth * rawHeight * 3 );
            readResult = fread( data, rawWidth * rawHeight * 3, 1, file );
            if (readResult != 1) {
                printf("File %s was not read correctly\n", fileArray[i]);
                return 0; 
            }
            else
                fclose( file );
            if(data){
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, rawWidth, rawHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                printf("cubemap texture %d loaded correctly\n", i);
            }
            else
                printf("cubemap texture %d failed to load \n", i);
            free(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }

    void init(){
        shaderProgram = loadShaders(vsFile,fsFile);
        glUseProgram(shaderProgram);
        // generate VAOs and VBOs

        printf("ifjaoire\n");
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxVertices), &skyBoxVertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), BUFFER_OFFSET(0));

        textureID = loadCubeMap();

        if (textureID != 0) 
            printf("[Skybox] Texture LOADED  \n");
        else  
            printf("[Skybox] Texture NOT LOADED !!! \n");

        skyboxID = glGetUniformLocation(shaderProgram, "skybox");
        mvpID = glGetUniformLocation(shaderProgram, "MVP");
        glUniform1f(skyboxID, 0);

    }

public:
    int id;

    Skybox(int id, GLuint vao, GLuint vbo, char * file1, char * file2, char * file3, char * file4, char * file5, char * file6,
        int rawWidth, int rawHeight) {

        printf("%d %d \n", vao, vbo);
        this->id = id;
        this->vao = vao;
        this->vbo - vbo;

        this->rawWidth = rawWidth;
        this->rawHeight = rawHeight;

        this->fileArray[0] = (char *) malloc(strlen(file1));
        this->fileArray[1] = (char *) malloc(strlen(file2));
        this->fileArray[2] = (char *) malloc(strlen(file3));
        this->fileArray[3] = (char *) malloc(strlen(file4));
        this->fileArray[4] = (char *) malloc(strlen(file5));
        this->fileArray[5] = (char *) malloc(strlen(file6));
        strcpy(fileArray[0], file1);
        strcpy(fileArray[1], file2);
        strcpy(fileArray[2], file3);
        strcpy(fileArray[3], file4);
        strcpy(fileArray[4], file5);
        strcpy(fileArray[5], file6);

        init();
    }

	Skybox(int id, GLuint vao, GLuint vbo, char * fileName, int rawWidth, int rawHeight) {
        this->id = id;
        this->vao = vao;
        this->vbo = vbo;
        this->rawWidth = rawWidth;
        this->rawHeight = rawHeight;
        for (int i = 0; i < numSides; ++i){
            this->fileArray[i] = (char *) malloc(strlen(fileName));
            strcpy(this->fileArray[i], fileName);
        }

        init();
	}

    void display(){
        //vertex shader will push the texture out as far as possible
        //depth clamp will make sure it isn't clipped 
        glEnable(GL_DEPTH_CLAMP);

        glDepthFunc(GL_LEQUAL);
        glUseProgram(shaderProgram);

        glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(projectionMatrix * viewMatrix));
        
        glBindVertexArray(vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }

    void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
        this->viewMatrix = viewMatrix;
        this->projectionMatrix = projectionMatrix;

        display();
    }
        // free OpenGL resources
    void cleanUp (void) {
        glDeleteBuffers(1, &vbo);
        freeTexture(textureID);   
        printf("cleaned up Skybox class\n");
    }
};