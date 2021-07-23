#ifndef SHIELD_h_h
#define SHIELD_h

#include "Arduino.h"
#include <MOTT.h>
#include "LaserTag_consts.h"
#include "Weapons.h"
#include "Shield_consts.h"
#include "Hit.h"
#include "Report.h"


class Shield
{
	
	MOTT *mott;
	char team;
  int health;
  bool alive;
  char BulletString[2];
  Gun *gun;
  char currentGunId;

  Report report;
	
  private:
    void UpdateHealth();
	
  public:
    Shield();
    void ChangeTeam(char aTeam);
    void SetMOTT(MOTT *aMott);
    bool DetectedBullet();
    bool IsBulletFromSameTeam();
    void Resume();
    bool IsShieldDead();
    void ResetHealth();
	
};

#endif