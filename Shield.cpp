#include "Arduino.h"
#include "Shield.h"
#include "Shield_consts.h"

Shield::Shield()
{
	health = MAX_HEALTH;
	alive = true;
	currentGunId = 'X';
}

void Shield::SetMOTT(MOTT *aMott)
{
	mott = aMott;
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

		if(IsShieldDead())
		{
			return true;
		}

		if(IsBulletFromSameTeam())
		{
			Serial.println("Friendly fire is OFF");
			
		} else{

			UpdateHealth();
			Serial.print("OUCH! Health: ");
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

	if(weapon_id == REVOLVER_ID)
	{
		gun = new Revolver();

	}

	if(weapon_id == ROCKET_LAUNCHER_ID)
	{
		gun = new RocketLauncher();	
	}

	health -= gun->GetDamage();

	if(health <= 0)
	{
		alive = false;
	}

}

void Shield::Resume(){
	mott->ResumeSampling();
}

bool Shield::IsShieldDead()
{
	return alive == false;
}

void Shield::ResetHealth()
{
	alive = true;
	health = MAX_HEALTH;
}

