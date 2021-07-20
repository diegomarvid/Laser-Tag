#ifndef LaserTag_h
#define LaserTag_h

#include "Arduino.h"
#include <MOTT.h>
#include <Pistol.h>
#include <Shield.h>
#include "LaserTag_consts.h"

class LaserTag
{

  MOTT mott;
	Pistol pistol;
	Shield shield;

  char team;
 	
  public:
    LaserTag(char aTeam);
    void ChangeTeam(char aTeam);
    void SetIRTransmitterPin(int pin);
    void SetIRRecieverPin(int pin);
    void SetInterruptCallback(void (*f)());
    void HandleInterrupt();
    void Shoot();
    void EnableBulletDetection();
    bool DetectedBullet();
    bool IsBulletFromSameTeam();
    void Resume();
    

	
};

#endif