#include "Arduino.h"
#include "LaserTag.h"
#include "LaserTag_consts.h"

LaserTag::LaserTag(char aTeam)
{
	team = aTeam;
	team_index = GetTeamIndex(team);

	pistol.SetMOTT(&mott);
	pistol.ChangeTeam(aTeam);
	pistol.SetGunType(REVOLVER_ID);

	weapon_index = GetWeaponIndex(REVOLVER_ID);

	shield.SetMOTT(&mott);
	shield.ChangeTeam(aTeam);

}

void LaserTag::SetIRTransmitterPin(int pin)
{
	mott.SetTxPin(pin);
}

void LaserTag::SetIRRecieverPin(int pin)
{
	mott.SetRxPin(pin);
}

void LaserTag::SetInterruptCallback(void (*f)())
{
	mott.SetBitTime(1L, f); //  speed: 1 bit / ms
}

int LaserTag::GetTeamIndex(char aTeam)
{

	for(int i = 0; i < 4; i++){
		if(Teams[i] == aTeam)
		{
			return i;
		}
	}

	return 0;

}

void LaserTag::HandleInterrupt()
{
	mott.HandleInterrupt();
}

void LaserTag::ChangeTeam(char aTeam)
{
	pistol.ChangeTeam(aTeam);
	shield.ChangeTeam(aTeam);
}

void LaserTag::ChangeToNextTeam(){

	team_index++;
	if(team_index == 4)
	{
		team_index = 0;
	}

	team = Teams[team_index];

	ChangeTeam(team);
}

char LaserTag::GetCurrentTeam(){
	return team;
}

void LaserTag::ChangeWeaponType(int weapon_id){
	pistol.ChangeGunType(weapon_id);
}

char LaserTag::GetCurrentWeapon()
{
	return pistol.GetCurrentWeapon();
}

int LaserTag::GetWeaponIndex(char aWeaponId)
{

	for(int i = 0; i < 2; i++){
		if(Weapons[i] == aWeaponId)
		{
			return i;
		}
	}

	return 0;

}

void LaserTag::ChangeToNextWeapon(){

	weapon_index++;

	if(weapon_index == 2)
	{
		weapon_index = 0;
	}

	ChangeWeaponType(Weapons[weapon_index]);

}

void LaserTag::Shoot()
{
	if(!AmIDead())
	{
		pistol.Shoot();
	}
	
}

void LaserTag::Reload()
{	Serial.println("Reloading...");
	pistol.Reload();
}

void LaserTag::EnableBulletDetection()
{
	return mott.EnableSampling();
}

bool LaserTag::DetectedBullet()
{
	return shield.DetectedBullet();
}

bool LaserTag::IsBulletFromSameTeam()
{
	return shield.IsBulletFromSameTeam();
}

void LaserTag::Resume()
{
	shield.Resume();
}

bool LaserTag::AmIDead()
{
	return shield.IsShieldDead();
}

void LaserTag::ResetHealth()
{
	shield.ResetHealth();
}


