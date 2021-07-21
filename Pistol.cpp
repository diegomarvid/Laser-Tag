#include "Arduino.h"
#include "Pistol.h"
#include "WeaponCreationFactory.h"
#include "LaserTag_consts.h"


Pistol::Pistol()
{
	lastShotTime = 0L;
	
}

 void Pistol::SetMOTT(MOTT *aMott)
 {
	 mott = aMott;
 }

void Pistol::CreateGun(int weapon_id)
{
	//Serial.println("Voy a crear arma");

	switch(weapon_id)
	{
		case REVOLVER_ID:
			gun = new Revolver();
			break;
		case ROCKET_LAUNCHER_ID:
			gun = new RocketLauncher();
			break;
		default:
			gun = new Revolver();
	}
}

void Pistol::ChangeTeam(char aTeam)
{
	team = aTeam;
}

void Pistol::SetGunType(int weapon_id)
{
	CreateGun(weapon_id);
	bullets = gun->GetMagazineSize();
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