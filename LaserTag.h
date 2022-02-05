#ifndef LaserTag_h
#define LaserTag_h

#include "Arduino.h"
#include "Button.h"
#include <MOTT.h>
#include <Pistol.h>
#include <Shield.h>
#include "LaserTag_consts.h"
#include "Weapons_consts.h"
#include <EspMQTTClient.h>

class LaserTag
{

  MOTT mott;
	Pistol pistol;
	Shield shield;

  int team_index;
  int weapon_index;

  char team;
  char player_id;

  bool game_started = false;

  EspMQTTClient *client;

  private:
    int GetTeamIndex(char aTeam);
    int GetWeaponIndex(char aTeam);
    String CreateJsonConnected();
    String CreateJsonTeam();
    void HandleSendDamage();

  public:
    LaserTag(char aTeam, char aplayerId);  
    void SetWifiCredentials(const char *ssid, const char *password);
    void MQTTLoop();
    void HandleMQTTConnection();
    void SetIRTransmitterPin(int pin);
    void SetIRRecieverPin(int pin);
    void SetInterruptCallback(void (*f)());
    void HandleInterrupt();
    void ChangeTeam(char aTeam);
    void ChangeToNextTeam();
    char GetCurrentTeam();
    void ChangeWeaponType(int weapon_id);
    char GetCurrentWeapon();
    void ChangeToNextWeapon();
    void Shoot();
    void Reload();
    void EnableBulletDetection();
    void DisableBulletDetection();
    bool DetectedBullet();
    bool IsBulletFromSameTeam();
    void Resume();
    bool AmIDead();
    void ResetHealth();
    void SendTeam();

    

	
};

#endif