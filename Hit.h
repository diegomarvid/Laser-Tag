#ifndef HIT_H
#define HIT_H 

#include <Arduino.h>

class Hit {

    char player_id;
    int damage;

    public:
        Hit();
        Hit(char aPlayerId, int aDamage){
            player_id = aPlayerId;
            damage = aDamage;
        };

        char GetPlayerId()
        {
            return player_id;
        }

        int GetDamage()
        {
            return damage;
        }

        void SetDamage(int aDamage){
            damage = aDamage;
        }

        void Print(){
            Serial.print("[");
            Serial.print(player_id);
            Serial.print(", ");
            Serial.print(damage);
            Serial.println("]");
        };


};

#endif

