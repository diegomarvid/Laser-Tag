#include "Arduino.h"
#include "Pistol.h"
#include "LaserTag_consts.h"
#include "Pistol_consts.h"

Pistol::Pistol(MOTT *aMott, int aTeam)
{
	mott = aMott;
	team = aTeam;
	bullets = MAGAZINE_SIZE;
}

void Pistol::Reload()
{
	bullets = MAGAZINE_SIZE;
}

void Pistol::Shoot()
{
	
	if(bullets <= 0)
	{
		Serial.println("No more bullets");
		return;
	} 
	
	if(bullets > 0){
		bullets--;
	}
	
	Serial.println("Pew!");
	

	if(team == WHITE_TEAM)
	{
		mott->SendSignal(WhiteTeamBullet);
	}
	
	if(team == BLUE_TEAM)
	{
		mott->SendSignal(BlueTeamBullet);
	}
	
	if(team == RED_TEAM)
	{
		mott->SendSignal(RedTeamBullet);
	}
	
	if(team == GREEN_TEAM)
	{
		mott->SendSignal(GreenTeamBullet);
	}
	
}