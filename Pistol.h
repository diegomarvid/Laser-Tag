#ifndef PISTOL_h
#define PISTOL_h

#include "Arduino.h"
#include <MOTT.h>
#include "LaserTag_consts.h"



class Pistol
{
	
	MOTT *mott;
	int team;
	int bullets;
	
  private:

	
  public:
    Pistol(MOTT *aMott, int aTeam);
	void Shoot();
	void Reload();

	
	
};

#endif