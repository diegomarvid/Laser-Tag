#ifndef REPORT_H
#define REPORT_H 

#include "Shield_consts.h"
#include "Hit.h"


class Report{

    Hit* Hits;

    int last_hit;

    public:
        Report();
        void AddHit(Hit hit);
        void PrintHits();
        int CheckIfPlayerHitMeAlready(Hit hit);

};

#endif