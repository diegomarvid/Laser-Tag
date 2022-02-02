#include "Arduino.h"
#include "Shield.h"


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

void Shield::SetClient(EspMQTTClient *aClient)
{
	client = aClient;
}

void Shield::SetPlayerId(char aPlayerId)
{
	player_id = aPlayerId;
}

String Shield::CreateJsonDied()
{

  String json = "{\"id\":\"";
  json += player_id;
  json += "\",\"died\":";
  json += "\"true\"";
  json += "}";

  return json;
}

bool Shield::DetectedBullet()
{
	
	if(mott->SamplingEnded())
	{
		mott->ObtainSample(BulletString);

		Serial.print("<<<MOTT: "); Serial.println(BulletString);

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

			report.PrintHits();

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
	if(alive == false) return;

	char weapon_id = BulletString[2];

	if(weapon_id == REVOLVER_ID)
	{
		gun = new Revolver();

	}

	if(weapon_id == ROCKET_LAUNCHER_ID)
	{
		gun = new RocketLauncher();	
	}

	Hit hit(BulletString[0], gun->GetDamage());
	report.AddHit(hit);

	health -= gun->GetDamage();

	if(health <= 0)
	{
		alive = false;
		client->publish("LaserTag/Died", CreateJsonDied());

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
	report.Reset();
}

String Shield::GetJsonReport()
{
	return report.CreateJsonReport(player_id);
}

