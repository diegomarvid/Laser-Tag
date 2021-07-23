#include "Report.h"

Report::Report()
{
    last_hit = -1;
    Hits = (Hit*) malloc(sizeof(Hit) * MAX_HEALTH);
}

int Report::GetHitIndex(Hit hit)
{
    if(last_hit == -1) return -1;

    char player_id = hit.GetPlayerId();

    for (int i = 0; i <= last_hit; i++)
    {
        if(player_id == Hits[i].GetPlayerId()){
            return i;
        }
    }

    return -1;

}

void Report::AddHit(Hit hit)
{

    int Hit_Index = GetHitIndex(hit);

    if(Hit_Index == NOT_FOUND){
        last_hit++;
        Hits[last_hit] = hit;
    }else{
        char newDamage = Hits[last_hit].GetDamage() + hit.GetDamage();
        Hits[Hit_Index].SetDamage(newDamage);
    }


}

void Report::PrintHits()
{
    for (int i = 0; i <= last_hit; i++)
    {
        Hits[i].Print();
    }
}

void Report::Reset()
{
    delete [] Hits;
    last_hit = -1;
    Hits = (Hit*) malloc(sizeof(Hit) * MAX_HEALTH);
}