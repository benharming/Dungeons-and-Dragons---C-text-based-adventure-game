#include "Party.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "time.h"
using namespace std; 

/*
-takes in 3 parameters, player (Party), room (Room), array[] (Player)
-The function calculates the winner of the fight based off of the formula given to us
-returns a bool, true if win and false if lose
*/
bool getMonsterWinner(Party &player, Room &room, Player array[])
{
    player.setNumArmor(array);
    player.setActiveMembers(array);
    player.setNumWeapons(array);

    srand(time(NULL));
    int randNumOne = rand() % 6 + 1; //random number b/w 1-6
    int randNumTwo  = rand() % 36 + 6; // another random number seperate from num1
    randNumTwo = randNumTwo / 6; //makes randnum 2 b/w 1-6

    int numArmor = player.getNumArmor();
    int numWeapons = player.getNumWeapons();
    int challengeLvl = room.getRoom();
    int numUpgradedWeapons = 0;

    bool clubFound = false;
    bool spearFound = false;
    bool rapierFound = false;
    bool battleAxeFound = false;
    bool longswordFound = false;
    int bonuspts = 0;

    double armorVar = 0;

    for(int i = 0; i < 5; i++)
    {
        if (array[i].getWeapon() == "Club")
        {
            clubFound = true;
        }
        if (array[i].getWeapon() == "Spear")
        {
            spearFound = true;
        }
        if (array[i].getWeapon() == "Rapier")
        {
            rapierFound = true;
            numUpgradedWeapons++;
        }
        if (array[i].getWeapon() == "Battle-axe")
        {
            battleAxeFound = true;
            numUpgradedWeapons++;
        }
        if (array[i].getWeapon() == "Longsword")
        {
            longswordFound = true;
            numUpgradedWeapons++;
        }
    }
    if (clubFound == true && spearFound == true && rapierFound == true && battleAxeFound == true && longswordFound == true) // check if every weapon is found + adds a bonus point
    {
        bonuspts = 1;
    }
   
    if (numArmor == 0) // because cant divide by 0
    {
        armorVar = 1;
    }
    else
    {
        armorVar = 1 / numArmor; //used as 1/a
    }
   
   double winNumber = (randNumOne * (numWeapons + numUpgradedWeapons) + bonuspts) - ((randNumTwo * challengeLvl) * armorVar); //calculates the winner
   if (winNumber > 0) //returns true if win and false if lose...
   {
       return true;
   }
   else
   {
       return false;
   }
   
}


