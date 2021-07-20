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
	//Shield shield;

  char team;

  int TX_SIGNAL_PIN;
	
 	
  public:
    LaserTag(char aTeam);
    void Shoot();
    void ChangeTeam(char aTeam);
    void SetIRTransmitterPin(int pin);
    void SetInterruptCallback(void (*f)());
    void HandleInterrupt();
    

	
};

#endif