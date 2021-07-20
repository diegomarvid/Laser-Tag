#include "Arduino.h"
#include "LaserTag.h"
#include "LaserTag_consts.h"

LaserTag::LaserTag(char aTeam)
{
	team = aTeam;

	pistol.SetMOTT(&mott);
	pistol.ChangeTeam(aTeam);
	//Shield shield(&mott, team);

}

void LaserTag::SetIRTransmitterPin(int pin)
{
	TX_SIGNAL_PIN = pin;
	mott.SetTxPin(TX_SIGNAL_PIN);
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
	pistol.Shoot();
}

void LaserTag::ChangeTeam(char aTeam)
{
	pistol.ChangeTeam(aTeam);
	//shield.ChangeTeam(aTeam);
}




