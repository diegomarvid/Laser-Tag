#ifndef PISTOL_h
#define PISTOL_h

#include "Arduino.h"
#include <MOTT.h>
#include "LaserTag_consts.h"



class Pistol
{
	
	MOTT *mott;
	char team;
	int bullets;
	unsigned long lastShotTime;
	
  private:
 	void CreateBulletString(char* string);
	bool IsFasterThanFireRate();

	
  public:
	Pistol();
    Pistol(MOTT *aMott, char aTeam);
	void ChangeTeam(char aTeam);
	void SetMOTT(MOTT *aMott);
	void Shoot();
	void Reload();

	
	
};

#endif