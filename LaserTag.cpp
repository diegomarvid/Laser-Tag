#include "Arduino.h"
#include "LaserTag.h"
#include "LaserTag_consts.h"

LaserTag::LaserTag(char aTeam)
{
	team = aTeam;

	pistol.SetMOTT(&mott);
	pistol.ChangeTeam(aTeam);
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
	mott.SetBitTime(1L, f);
}

void LaserTag::HandleInterrupt()
{
	mott.HandleInterrupt();
}

void LaserTag::Shoot()
{
	if(!AmIDead())
	{
		pistol.Shoot();
	}
	
}

void LaserTag::Reload()
{
	pistol.Reload();
}

void LaserTag::ChangeTeam(char aTeam)
{
	pistol.ChangeTeam(aTeam);
	shield.ChangeTeam(aTeam);
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


