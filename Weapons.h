#ifndef ROCKET_LAUNCHER_H
#define ROCKET_LAUNCHER_H

#include "Gun.h"
#include "Weapons_consts.h"

class RocketLauncher: public Gun {
   
   public:

      RocketLauncher():Gun(){
         	this->id = ROCKET_LAUNCHER_ID;
            this->magazine_size = 1;
            this->fire_rate = 2000;
            this->damage = 10;
      };
};

class Revolver: public Gun {
   
   public:

      Revolver():Gun(){
         	this->id = REVOLVER_ID;
            this->magazine_size = 7;
            this->fire_rate = 500;
            this->damage = 1;
      };  
};

#endif // ROCKET_LAUNCHER_H