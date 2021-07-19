#include "Arduino.h"
#include "Pistol.h"
#include "LaserTag_consts.h"
#include "Pistol_consts.h"

Pistol::Pistol(MOTT *aMott, char aTeam)
{
	mott = aMott;
	team = aTeam;
	bullets = MAGAZINE_SIZE;
	lastShotTime = 0L;
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
		Serial.println("Disparaste muy rapido");
		return;
	}

	bullets--;

	Serial.print("Pew! Bullets left: ");
	Serial.println(bullets);

	char BulletString[2];

	CreateBulletString(BulletString);

	mott->SendSignal(BulletString);
	
}