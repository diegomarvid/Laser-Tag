#include "Arduino.h"
#include "Pistol.h"
#include "LaserTag_consts.h"


Pistol::Pistol()
{
	lastShotTime = 0L;
	gun = new Revolver();
	bullets = gun->GetMagazineSize();
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
	bullets = gun->GetMagazineSize();
}

void Pistol::CreateBulletString(char* string)
{
	string[0] = team;
	string[1] = gun->GetId();
}

bool Pistol::IsFasterThanFireRate()
{
	int currentShotTime = millis();
	
	if(currentShotTime - lastShotTime < gun->GetFireRate())
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