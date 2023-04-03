
#include "Misfortunes.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

Misfortunes::Misfortunes()
{
    likeliness = 40;
    srand(time(NULL));
    int x = rand() % 100 + 1;
    if (x <= likeliness)
    {
        occurrence = true;
    }
    else
    {
        occurrence = false;   
    }

    int y = rand() % 5 + 1; //changed probabilities
    if (y == 1)
    {
        type = "food stolen";
    }
    if (y == 2)
    {
        type = "cookware stolen";
    }
    if (y == 3)
    {
        type = "armor stolen";
    }
    if (y == 4)
    {
        type = "armor broke";
    }
    if (y == 5)
    {
        type = "weapon broke";
    }
}
Misfortunes::Misfortunes(string t, int l, bool o)
{
    type = t;
    occurrence = o;
    likeliness = l;

}
void Misfortunes::setActualType(string t)
{
    type = t;
}
string Misfortunes::getActualType()
{
    return type;
}
void Misfortunes::setLikeliness(int l)
{
    likeliness = l;
}
void Misfortunes::setRandomOccurrence(int l)
{
    srand (time(NULL));
    int x = rand() % 100 + 1;
    if (x <= l)
    {
        occurrence = true; 
    }
    else
    {
        occurrence = false;
    }
}
void Misfortunes::setActualOccurrence(bool o) 
{
    occurrence = o;
}
bool Misfortunes::getOccurrence()
{
    return occurrence;
}
