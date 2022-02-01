#ifndef REPORT_H
#define REPORT_H 

#include "Shield_consts.h"
#include "Hit.h"

class Report{

    static const int NOT_FOUND = -1;

    Hit* Hits;

    int last_hit;

    private:       
        String CreateJsonHit(char id, int damage);
    public:
        Report();
        void AddHit(Hit hit);
        void PrintHits();
        String CreateJsonReport(char myId);
        int GetHitIndex(Hit hit);
        void Reset();


};

#endif