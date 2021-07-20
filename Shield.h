#ifndef SHIELD_h_h
#define SHIELD_h

#include "Arduino.h"
#include <MOTT.h>
#include "LaserTag_consts.h"
#include "Pistol_consts.h"

class Shield
{
	
	MOTT *mott;
	char team;
  int health;
  char BulletString[2];
	
  private:
    void UpdateHealth();
	
  public:
    Shield(MOTT *aMott, char aTeam);
    void ChangeTeam(char aTeam);
    bool DetectedBullet();
    bool IsBulletFromSameTeam();
    void Resume();
	
};

#endif