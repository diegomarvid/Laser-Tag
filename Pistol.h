#ifndef PISTOL_h
#define PISTOL_h

#include "Arduino.h"
#include <MOTT.h>
#include "LaserTag_consts.h"
#include "Gun.h"
#include "Weapons.h"



class Pistol
{
	
	MOTT *mott;
	char team;
	int bullets;
	unsigned long lastShotTime;
	Gun *gun;
	
  private:
 	void CreateBulletString(char* string);
	bool IsFasterThanFireRate();
	void CreateGun(int weapon_id);

	
  public:
	Pistol();
	void ChangeTeam(char aTeam);
	void SetMOTT(MOTT *aMott);
	void SetGunType(int weapon_id);
	void Shoot();
	void Reload();

	
	
};

#endif