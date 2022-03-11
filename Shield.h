#ifndef SHIELD_h_h
#define SHIELD_h

#include "Arduino.h"
#include <MOTT.h>
#include <EspMQTTClient.h>
#include "LaserTag_consts.h"
#include "Weapons.h"
#include "Shield_consts.h"
#include "Hit.h"
#include "Report.h"

class Shield
{
	
	MOTT *mott;
	char team;
  char player_id;
  int health;
  bool alive;
  char BulletString[3];
  Gun *gun;
  char currentGunId;

  EspMQTTClient *client;

  Report report;
	
  private:
    void UpdateHealth();
    void CreateGun(int weapon_id);
    String CreateJsonDied();
    bool IsSampleCorrectFormat(char *aBulletString);
	
  public:
    Shield();
    void ChangeTeam(char aTeam);
    void SetPlayerId(char aPlayerId);
    void SetMOTT(MOTT *aMott);
    void SetClient(EspMQTTClient *aClient);
    bool DetectedBullet();
    bool IsBulletFromSameTeam();
    void Resume();
    bool IsShieldDead();
    void ResetHealth();
    String GetJsonReport();

	
};

#endif