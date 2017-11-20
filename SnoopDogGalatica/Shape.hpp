/*
	Shape.hpp

	Lemuel Dizon
	Ramses Ordonez
	Kelly Kim

	10/2/2017
*/

# ifndef __INCLUDES465__
# include "../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __SHAPE__

class Shape {
    
public:

    int id;
    int numOfVert;
    char * fileName;
    float size;
	float modelSize;

    GLuint vPosition;
    GLuint vColor;
    GLuint vNormal;

    glm::mat4 scaleMatrix;
	glm::mat4 translationMatrix;
    glm::vec3 rotationAxis;
	glm::mat4 rotationMatrix;    
    float radians;

	Shape() {

	}

    Shape(int id, int numOfVert, char * fileName, float size) {
        this->id = id;
        this->numOfVert = numOfVert;
        this->fileName = fileName;
        this->size = size;

        translationMatrix = glm::translate(glm::mat4(), glm::vec3(0));
        rotationAxis = glm::vec3(0);
        radians = glm::radians(1.0f);
    }

	Shape(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix) {
		this->id = id;
		this->numOfVert = numOfVert;
		this->fileName = fileName;
		this->size = size;

		this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
		rotationAxis = glm::vec3(0, 1, 0);
		radians = glm::radians(1.0f);
	}

    Shape(int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians) {
        this->id = id;
        this->numOfVert = numOfVert;
        this->fileName = fileName;
        this->size = size;

        this->translationMatrix = glm::translate(glm::mat4(), translationMatrix);
        this->rotationAxis = rotationAxis;
        this->radians = glm::radians(radians);
    }

	void initializeShape(GLuint(&VAO)[11], GLuint(&buffer)[11], GLuint &shaderProgram) {
		float modelSize = loadModelBuffer(this->fileName, this->numOfVert, VAO[this->id], buffer[this->id], shaderProgram,
			this->vPosition, this->vColor, this->vNormal, "vPosition", "vColor", "vNormal");
		this->setScaleMatrix(modelSize);
	}

	void displayShape(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix, GLuint &MVP, GLuint (&VAO)[11]) {
		glm::mat4 ModelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
		glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(ModelViewProjectionMatrix));
		glBindVertexArray(VAO[this->id]);
		glDrawArrays(GL_TRIANGLES, 0, this->numOfVert);
	}

    void setScaleMatrix(float modelSize) {
		this->modelSize = modelSize;
        this->scaleMatrix = glm::scale(glm::mat4(), glm::vec3(size * 1.0f / modelSize));
    }

	void sendToCenter() {
		this->translationMatrix = glm::mat4(0);
	}

    glm::mat4 getModelMatrix() {
        return (translationMatrix * scaleMatrix);
    }

    glm::mat4 getTranslationMatrix(){
        return this->translationMatrix;
    }

    glm::mat4 getOrientationMatrix() {
        return (this->translationMatrix * this->rotationMatrix);
    }

    float getSize(){
        return this->size;
    }

};