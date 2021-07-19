#include "Arduino.h"
#include "Shield.h"
#include "LaserTag_consts.h"


Shield::Shield(MOTT *aMott, int aTeam)
{
	mott = aMott;
	team = aTeam;
}


