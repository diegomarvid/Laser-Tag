#include "Arduino.h"
#include "LaserTag.h"
#include "LaserTag_consts.h"

const char *BROKER_IP = "broker.hivemq.com";
const char* DEVICE_NAME = "esp32";

EspMQTTClient client2(
  "default",
  "default",
  BROKER_IP 
  //DEVICE_NAME
);


LaserTag::LaserTag(char aTeam, char aPlayerId)
{

	player_id = aPlayerId;

	client = &client2;

	client->enableDebuggingMessages();

	team = aTeam;
	team_index = GetTeamIndex(team);

	pistol.SetMOTT(&mott);
	pistol.ChangeTeam(aTeam);
	pistol.SetGunType(REVOLVER_ID);
	pistol.SetPlayerId(player_id);

	weapon_index = GetWeaponIndex(REVOLVER_ID);

	shield.SetMOTT(&mott);
	shield.ChangeTeam(aTeam);
	shield.SetClient(client);
	shield.SetPlayerId(player_id);

	

}

void LaserTag::SetWifiCredentials(const char *ssid, const char *password)
{
	client->setMqttClientName("esp32");
	client->setWifiCredentials(ssid, password);
}

void LaserTag::MQTTLoop()
{
	client->loop();
}

void LaserTag::HandleSendDamage()
{
	client->publish("LaserTag/SendDamageTaken", "Hello world");
}

String LaserTag::CreateJsonConnected()
{

  String json = "{\"id\":\"";
  json += player_id;
  json += "\",\"connected\":";
  json += "\"true\"";
  json += "}";


  return json;
}

String LaserTag::CreateJsonTeam()
{

  String json = "{\"id\":\"";
  json += player_id;
  json += "\",\"team\":\"";
  json += team;
  json += "\"}";


  return json;
}

void LaserTag::SendTeam()
{
	client->publish("LaserTag/Team", CreateJsonTeam());
}

void LaserTag::HandleMQTTConnection()
{

	client->subscribe("LaserTag/Start", [&] (const String &payload)  {
	
		Serial.println("Starting game...");
		game_started = true;
		EnableBulletDetection();
		ResetHealth();
		Reload();
	});

	client->subscribe("LaserTag/SendDamage", [&] (const String &payload)  {
	
		client->publish("LaserTag/SendDamageTaken", shield.GetJsonReport());
		game_started = false;
		DisableBulletDetection();

	});

   client->publish("LaserTag/Connected", CreateJsonConnected());

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

	for(int i = 0; i < TEAM_AMOUNT; i++){
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
	if(team_index == TEAM_AMOUNT)
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

	for(int i = 0; i < WEAPONS_AMOUNT; i++){
		if(Weapons[i] == aWeaponId)
		{
			return i;
		}
	}

	return 0;

}

void LaserTag::ChangeToNextWeapon(){

	weapon_index++;

	if(weapon_index == WEAPONS_AMOUNT)
	{
		weapon_index = 0;
	}

	ChangeWeaponType(Weapons[weapon_index]);

}

void LaserTag::Shoot()
{

	if(!game_started) return;

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

void LaserTag::DisableBulletDetection()
{
	return mott.DisableSampling();
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


