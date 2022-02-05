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
            this->damage = 50;
      };
};

class Revolver: public Gun {
   
   public:

      Revolver():Gun(){
         	this->id = REVOLVER_ID;
            this->magazine_size = 7;
            this->fire_rate = 500;
            this->damage = 10;
      };  
};

class Turret1: public Gun {
   
   public:

      Turret1():Gun(){
         	this->id = TURRET_LEVEL1_ID;
            this->magazine_size = INT_MAX;
            this->fire_rate = 1000;
            this->damage = 2;
      };  
};

class Turret2: public Gun {
   
   public:

      Turret2():Gun(){
         	this->id = TURRET_LEVEL2_ID;
            this->magazine_size = INT_MAX;
            this->fire_rate = 1000;
            this->damage = 5;
      };  
};

class Turret3: public Gun {
   
   public:

      Turret3():Gun(){
         	this->id = TURRET_LEVEL3_ID;
            this->magazine_size = INT_MAX;
            this->fire_rate = 300;
            this->damage = 1;
      };  
};

#endif // ROCKET_LAUNCHER_H