#include <LaserTag.h>
#include <Button.h>

const bool PRESSED = 1;

const int TX_SIGNAL_PIN = 8;
const int R_LED_PIN = 9;
const int G_LED_PIN = 10;
const int B_LED_PIN = 11;

const char PLAYER_ID = 'D';

LaserTag laserTag(RED_TEAM, PLAYER_ID);

Button TriggerButton(4);
Button ReloadButton(5);
Button ChangeWeaponButton(6);
Button ChangeTeamButton(7);

void setup() {
  
  Serial.begin(9600);

  pinMode(TX_SIGNAL_PIN, OUTPUT);
  pinMode(R_LED_PIN, OUTPUT);
  pinMode(G_LED_PIN, OUTPUT);
  pinMode(B_LED_PIN, OUTPUT);

  SetLed(0,0,0);

  laserTag.SetIRTransmitterPin(TX_SIGNAL_PIN);
  laserTag.SetInterruptCallback(Callback);

  Serial.print("LaserTag game loaded up as team: ");
  Serial.println(laserTag.GetCurrentTeam());

}

void Callback()
{
  laserTag.HandleInterrupt();
}

void SetLed(int r, int g, int b)
{
  analogWrite(R_LED_PIN, 255 - r );
  analogWrite(G_LED_PIN, 255 - g );
  analogWrite(B_LED_PIN, 255 - b);
}


void loop() {

  if(TriggerButton.IsReleased())
  {
    laserTag.Shoot();
  }

  if(ReloadButton.IsReleased())
  {
    laserTag.Reload();
  }

  if(ChangeWeaponButton.IsReleased())
  {

    laserTag.ChangeToNextWeapon();
    Serial.print("Changed weapon to: ");
    Serial.println(laserTag.GetCurrentWeapon());
    
  }


  if(ChangeTeamButton.IsReleased())
  {

    laserTag.ChangeToNextTeam();
    //Serial.print("Changed team to: ");
    //Serial.println(laserTag.GetCurrentTeam());

    if(laserTag.GetCurrentTeam() == WHITE_TEAM)
    {
      SetLed(255,255,255);
      Serial.println(laserTag.GetCurrentTeam());
    }

    if(laserTag.GetCurrentTeam() == BLUE_TEAM)
    {
      SetLed(0,0,255);
      Serial.println(laserTag.GetCurrentTeam());
    }

    if(laserTag.GetCurrentTeam() == RED_TEAM)
    {
      SetLed(255,0,0);
      Serial.println(laserTag.GetCurrentTeam());
    }

      if(laserTag.GetCurrentTeam() == GREEN_TEAM)
    {
      SetLed(0,255,0);
      Serial.println(laserTag.GetCurrentTeam());
    }
    
  }
 
}
