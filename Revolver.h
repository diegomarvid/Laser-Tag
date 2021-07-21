#ifndef REVOLVER_H
#define REVOLVER_H

#include "Gun.h"

class Revolver: public Gun {
   
   public:

      Revolver():Gun(){
         	this->id = 'K';
            this->magazine_size = 7;
            this->fire_rate = 500;
            this->damage = 1;
      };
      
     
};

#endif // REVOLVER_H