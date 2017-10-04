/*
    Sun.hpp (non-rotating planet)

    Lemuel Dizon
    Ramses Ordonez
    10/2/2017
*/

class Sun: public Shape {

public:
    glm::mat4 getModelMatrix() {
        return (this->translationMatrix * this->rotationMatrix * this->scaleMatrix);
    }

    void update() {
        this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
    }

}