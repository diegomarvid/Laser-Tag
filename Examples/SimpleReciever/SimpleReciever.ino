#include <MOTT.h>
#include <LaserTag.h>

const char PLAYER_ID = 'A';

LaserTag laserTag(WHITE_TEAM, PLAYER_ID);

const int RX_SIGNAL_PIN = 7;

void setup() {
  Serial.begin(9600);

  pinMode(RX_SIGNAL_PIN, INPUT);
  
  laserTag.SetIRRecieverPin(RX_SIGNAL_PIN);
  laserTag.SetInterruptCallback(Callback);

  laserTag.EnableBulletDetection();

  Serial.println("LaserTag game loaded up as White Team");

  Serial.println("-------------------------");
  Serial.println("Ready to detect bullets...");

}

void Callback()
{
  laserTag.HandleInterrupt();
}

char string[25];

void loop() {

 if(laserTag.DetectedBullet()){

    if(!laserTag.IsBulletFromSameTeam())
    {
      
    }

    if(laserTag.AmIDead())
    {
      Serial.println("I died!");
    }

    laserTag.Resume();
 }
  

}
