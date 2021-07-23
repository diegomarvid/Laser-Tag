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

        void Print(){
            Serial.print("[");
            Serial.print(player_id);
            Serial.print(", ");
            Serial.print(damage);
            Serial.println("]");
        };


};

#endif

