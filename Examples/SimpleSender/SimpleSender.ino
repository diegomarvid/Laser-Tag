#include <LaserTag.h>

const int TX_SIGNAL_PIN = 8;

const char PLAYER_ID = 'A';

LaserTag laserTag(RED_TEAM, PLAYER_ID);

Button TriggerButton(18);
Button ReloadButton(26);

void setup() {
  
  Serial.begin(115200);

  pinMode(TX_SIGNAL_PIN, OUTPUT);

  laserTag.SetWifiCredentials("Ricciardi", "ricciardi");

  laserTag.SetIRTransmitterPin(TX_SIGNAL_PIN);
  laserTag.SetInterruptCallback(Callback);

  Serial.print("LaserTag game loaded up as team: ");
  Serial.println(laserTag.GetCurrentTeam());

}

void Callback()
{
  laserTag.HandleInterrupt();
}

void onConnectionEstablished() {

  laserTag.HandleMQTTConnection();
  
}

void loop() 
{
  
  laserTag.MQTTLoop();

  if(TriggerButton.IsReleased())
  {
    Serial.println("Shooting!");
    laserTag.Shoot();
  }

  if(ReloadButton.IsReleased())
  {
    laserTag.Reload();
  }

     
}