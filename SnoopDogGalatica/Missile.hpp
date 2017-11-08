/*
	Missile.hpp

	Lemuel Dizon
	Ramses Ordonez
	10/2/2017
*/


# ifndef __INCLUDES465__
# include "../../includes465/include465.hpp"
# define __INCLUDES465__
# endif

# define __Missile__

class Missile : public Shape {
    //update by target location and current position
    //
    //
    const private int UTL = 2000; //2000 updates to live
    const private int UTA = 200;  //200 updates to activate
    int ttl, activate;

public:
    Missile (int id, int numOfVert, char * fileName, float size, glm::vec3 translationMatrix, glm::vec3 rotationAxis, float radians) : 
    Shape(id, numOfVert, fileName, size, translationMatrix, rotationAxis, radians ){
        ttl = UTL;
        activate = UTA;
    };

    void update() {
        if(ttl > 0){ //translate all the time if there are time to live remaining
            this->translationMatrix =  glm::translate(this->translationMatrix, -step * getOut(this->rotationMatrix));
            if (activate > 0){
                activate--;//since not activated no rotation 
                if (activate == 0)
                    locate();
            }else{ //activated
                this->rotationMatrix = glm::rotate(this->rotationMatrix, this->radians, this->rotationAxis);
                ttl--;
            }
        }
    }

    void locate(){
        //find nearest target 
    }


    //
};