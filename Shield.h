#ifndef SHIELD_h_h
#define SHIELD_h

#include "Arduino.h"
#include <MOTT.h>
#include "LaserTag_consts.h"

class Shield
{
	
	MOTT *mott;
	int team;
	
  private:

	
  public:
    Shield(MOTT *aMott, int aTeam);
	
};

#endif