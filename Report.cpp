#include "Report.h"

Report::Report()
{
    last_hit = -1;
    Hits = (Hit*) malloc(sizeof(Hit) * MAX_HEALTH);
}

void Report::AddHit(Hit hit)
{
    last_hit++;
    Hits[last_hit] = hit;

}

void Report::PrintHits()
{
    for (int i = 0; i <= last_hit; i++)
    {
        Hits[i].Print();
    }
}