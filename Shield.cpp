#include "Arduino.h"
#include "Shield.h"


Shield::Shield()
{
	health = MAX_HEALTH;
	alive = true;
	currentGunId = 'X';
	eliminated = 'X';
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
  json += "\"true\",";
  json += "\"eliminated\":\"";
  json += eliminated;
  json += "\"";
  json += "}";

  return json;
}

bool Shield::DetectedBullet()
{
	
	if(mott->SamplingEnded())
	{
		mott->ObtainSample(BulletString);

		if (IsSampleCorrectFormat(BulletString))
		{

			Serial.print("<< MOTT: "); Serial.println(BulletString);

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

		}

		return true;
		

	} else{	
		return false;
	}
	
}

bool Shield::IsSampleCorrectFormat(char *aBulletString)
{
	char id = aBulletString[0];

	if(id < 48 || id > 122) {return false;}

	// Serial.print("Passed id condition: ");
	// Serial.print(id);

	char team = aBulletString[1];

	bool isValidTeam = false;

	for(int i = 0; i < TEAM_AMOUNT; i++)
	{
		if(team == Teams[i]) {
			isValidTeam = true;
		}
	}

	if(!isValidTeam) {return false;}

	// Serial.print("Passed team condition: ");
	// Serial.print(team);

	char gun_id = aBulletString[2];

	if(gun_id < 48 || gun_id > 122) {return false;}

	// Serial.print("Passed gun id condition: ");
	// Serial.print(gun_id);

}

bool Shield::IsBulletFromSameTeam()
{
	return team == BulletString[1];
}

void Shield::CreateGun(int weapon_id)
{
	switch(weapon_id)
	{
		case REVOLVER_ID:
			gun = new Revolver();
			break;
		case ROCKET_LAUNCHER_ID:
			gun = new RocketLauncher();
			break;
		case TURRET_LEVEL1_ID:
			gun = new Turret1();
			break;
		case TURRET_LEVEL2_ID:
			gun = new Turret2();
			break;
		case TURRET_LEVEL3_ID:
			gun = new Turret3();
			break;
		default:
			Serial.println("Shield didnt find correct weapon id, using revolver as default");
			gun = new Revolver();
	}
}

void Shield::UpdateHealth()
{
	if(alive == false) return;

	char weapon_id = BulletString[2];

	CreateGun(weapon_id);

	Hit hit(BulletString[0], gun->GetDamage());
	report.AddHit(hit);

	health -= gun->GetDamage();

	if(health <= 0)
	{
		alive = false;
		eliminated = BulletString[0];
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



