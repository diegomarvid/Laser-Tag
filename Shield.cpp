#include "Arduino.h"
#include "Shield.h"
#include "Shield_consts.h"


Shield::Shield(MOTT *aMott, char aTeam)
{
	mott = aMott;
	team = aTeam;
	health = MAX_HEALTH;
}

bool Shield::DetectedBullet()
{
	char BulletString[2];

	if(mott->SamplingEnded())
	{
		mott->ObtainSample(BulletString);

		if(IsBulletFromDifferentTeam(BulletString))
		{
			return false;
		}

		UpdateHealth(BulletString);

		return true;

	} else{	
		return false;
	}
	
}

bool Shield::IsBulletFromDifferentTeam(char* BulletString)
{
	return team != BulletString[0];
}

void Shield::UpdateHealth(char* BulletString)
{
	char weapon_id = BulletString[1];

	if(weapon_id == PISTOL_ID)
	{
		health -= PISTOL_DAMAGE;
	}

}

void Shield::Resume(){
	mott->ResumeSampling();
}

