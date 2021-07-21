#include "Gun.h"
#include "Weapons.h"
#include "Weapons_consts.h"

class WeaponCreationFactory
{
    public:
        static void CreateGun(int weapon_id, Gun *gun)
        {
            Serial.println("Voy a crear arma");
 
            switch(weapon_id)
            {
                case REVOLVER_ID:
                    gun = new Revolver();
                    break;
                case ROCKET_LAUNCHER_ID:
                    gun = new RocketLauncher();
                    break;
                default:
                    gun = new Revolver();
            }
        }
};