#include "Party.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "time.h"
using namespace std;

/*
-function takes in the room number (int) as a paramter and generates a random monster depending on which room the player is in
-returns a string (the random monster)
*/
string getRandomMonster(int roomNumber)
{
    srand(time(NULL));
    int randomMonster = rand() % 4 + 1; // random int b/w 1-4 to generate which monster lvl to choose from
    string monster;
   
    if (roomNumber == 1)
    {
        if (randomMonster == 1)
        {
            monster = "Animated armor";
        }
        if (randomMonster == 2)
        {
            monster = "Bugbear";
        }
        if (randomMonster == 3)
        {
            monster = "Harpy";
        }
        if (randomMonster == 4)
        {
            monster = "Scarecrow";
        }
    }
    if (roomNumber == 2)
    {
        if (randomMonster == 1)
        {
            monster = "Minotaur";
        }
        if (randomMonster == 2)
        {
            monster = "Owlbear";
        }
        if (randomMonster == 3)
        {
            monster = "Banshee";
        }
        if (randomMonster == 4)
        {
            monster = "Wereboar";
        }
    }
    if (roomNumber == 3)
    {
        if (randomMonster == 1)
        {
            monster = "Giant crocodile";
        }
        if (randomMonster == 2)
        {
            monster = "Troll";
        }
        if (randomMonster == 3)
        {
            monster = "Hobgoblin warrior";
        }
        if (randomMonster == 4)
        {
            monster = "Mammoth";
        }
    }
    if (roomNumber == 4)
    {
        if (randomMonster == 1)
        {
            monster = "Stone giant";
        }
        if (randomMonster == 2)
        {
            monster = "Night hag";
        }
        if (randomMonster == 3)
        {
            monster = "Assassin";
        }
        if (randomMonster == 4)
        {
            monster = "Hydra";
        }
    }
    if (roomNumber == 5)
    {
        if (randomMonster == 1)
        {
            monster = "Cloud giant";
        }
        if (randomMonster == 2)
        {
            monster = "Silver dragon";
        }
        if (randomMonster == 3)
        {
            monster = "Vampire";
        }
        if (randomMonster == 4)
        {
            monster = "Lich";
        }
    }
    return monster;
}

