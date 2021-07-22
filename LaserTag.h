#ifndef LaserTag_h
#define LaserTag_h

#include "Arduino.h"
#include <MOTT.h>
#include <Pistol.h>
#include <Shield.h>
#include "LaserTag_consts.h"
#include "Weapons_consts.h"

class LaserTag
{

  MOTT mott;
	Pistol pistol;
	Shield shield;

  int team_index;

  char team;

  private:
    int GetTeamIndex(char aTeam);

  public:
    LaserTag(char aTeam);
    void SetIRTransmitterPin(int pin);
    void SetIRRecieverPin(int pin);
    void SetInterruptCallback(void (*f)());
    void HandleInterrupt();
    void ChangeTeam(char aTeam);
    void ChangeToNextTeam();
    char GetCurrentTeam();
    void ChangeWeaponType(int weapon_id);
    char GetCurrentWeapon();
    void Shoot();
    void Reload();
    void EnableBulletDetection();
    bool DetectedBullet();
    bool IsBulletFromSameTeam();
    void Resume();
    bool AmIDead();
    void ResetHealth();
    

	
};

#endif