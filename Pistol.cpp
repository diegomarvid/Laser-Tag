#include "Arduino.h"
#include "Pistol.h"
#include "LaserTag_consts.h"
#include "Pistol_consts.h"

Pistol::Pistol()
{
	bullets = MAGAZINE_SIZE;
	lastShotTime = 0L;
}

 void Pistol::SetMOTT(MOTT *aMott)
 {
	 mott = aMott;
 }
 

void Pistol::ChangeTeam(char aTeam)
{
	team = aTeam;
}

void Pistol::Reload()
{
	bullets = MAGAZINE_SIZE;
}

void Pistol::CreateBulletString(char* string)
{
	string[0] = team;
	string[1] = PISTOL_ID;
}

bool Pistol::IsFasterThanFireRate()
{
	int currentShotTime = millis();
	
	if(currentShotTime - lastShotTime < FIRE_RATE)
	{
		return true;
	}

	lastShotTime = currentShotTime;

	return false;
}

void Pistol::Shoot()
{
	
	if(bullets <= 0)
	{
		Serial.println("No more bullets");
		return;
	} 

	if(IsFasterThanFireRate())
	{
		Serial.println("You shoot too fast");
		return;
	}

	bullets--;

	char BulletString[2];

	CreateBulletString(BulletString);

	Serial.print("Pew [");
	Serial.print(BulletString);
	Serial.print("] Bullets left: ");
	Serial.println(bullets);

	mott->SendSignal(BulletString);
	
}