#include <LaserTag.h>

const char PLAYER_ID = 'A';

Button ConnectedButton(18);

LaserTag laserTag(RED_TEAM, PLAYER_ID);


const int RX_SIGNAL_PIN = 26;

void setup() {
  Serial.begin(115200);

  pinMode(RX_SIGNAL_PIN, INPUT);

  laserTag.SetWifiCredentials("Ricciardi", "ricciardi");
  
  laserTag.SetIRRecieverPin(RX_SIGNAL_PIN);
  
  laserTag.SetInterruptCallback(Callback);

  Serial.println("LaserTag game loaded up as Red Team");

}

void Callback()
{
  laserTag.HandleInterrupt();
}

void onConnectionEstablished() {

  laserTag.HandleMQTTConnection();
  
}


void loop() {


  if(ConnectedButton.IsReleased())
  {
    Serial.println("Sending team...");
    laserTag.SendTeam();
  }

 laserTag.MQTTLoop();

 if(laserTag.DetectedBullet()){

    if(!laserTag.IsBulletFromSameTeam())
    {
      //Shake motor
    }

    if(laserTag.AmIDead())
    {
      Serial.println("I died!");
    }

    laserTag.Resume();
 }
  

}