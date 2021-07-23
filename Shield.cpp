#include "Arduino.h"
#include "Shield.h"
#include "Shield_consts.h"
#include "Hit.h"

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
			Serial.print("OUCH! Player ");
			Serial.print(BulletString[0]);
			Serial.print(" hit me, Health: ");
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
	return team == BulletString[1];
}

void Shield::UpdateHealth()
{
	char weapon_id = BulletString[2];

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

	Hit hit(BulletString[0], gun->GetDamage());
	hit.Print();

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

