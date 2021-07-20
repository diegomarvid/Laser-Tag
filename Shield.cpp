#include "Arduino.h"
#include "Shield.h"
#include "Shield_consts.h"


Shield::Shield(MOTT *aMott, char aTeam)
{
	mott = aMott;
	team = aTeam;
	health = MAX_HEALTH;
}

void Shield::ChangeTeam(char aTeam)
{
	team = aTeam;
}

bool Shield::DetectedBullet()
{
	
	if(mott->SamplingEnded())
	{
		mott->ObtainSample(BulletString);

		Serial.println(BulletString);

		if(IsBulletFromSameTeam())
		{
			Serial.println("Same team!");
			
		} else{

			UpdateHealth();
			Serial.print("Health: ");
			Serial.print(health);
			Serial.println(" hp.");

		}

		return true;

	} else{	
		return false;
	}
	
}

bool Shield::IsBulletFromSameTeam()
{
	return team == BulletString[0];
}

void Shield::UpdateHealth()
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

