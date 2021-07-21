#ifndef GUN_H
#define GUN_H

class Gun {

    protected:
        char id;     
        int magazine_size;     
        int fire_rate;  
        int damage;

   public:

        Gun(){

        }
        
        char GetId(){
            return id;
        }

        int GetMagazineSize(){
            return magazine_size;
        }

        int GetFireRate(){
            return fire_rate;
        }

        int GetDamage(){
            return damage;
        }
      
};

#endif