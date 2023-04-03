#include "Party.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

    Party::Party()
    {
        Player p[5];
        gold = 100;
        ingredients = 0;
        num_armor = 0;
        cookware[0] = 0;
        cookware[1] = 0;
        cookware[2] = 0;
        activeMembers = 5;
        
    }
    Party::Party(Player p[], double g, int i, int a, int cook[], int aMems, bool t[][2])
    {
        for(int i = 0; i > 5; i++)
        {
            party[i] = p[i];
        }
        gold = g;
        ingredients = i;
        num_armor = a;
        cookware[0] = cook[0];
        cookware[1] = cook[1];
        cookware[2] = cook[2];
        activeMembers = aMems;
        for(int i = 0; i < 5; i++)
        {
           for(int j = 0; i < 2; i++)
            {
                treasureFound[i][j] = t[i][j];
            } 
        }

    }
    Player Party::getPartyMember(int pIndex)
    {
        return party[pIndex];
    }
    void Party::setParty(Player p[])
    {
        for (int i = 0; i < 5; i++)
        {
        party[i] = p[i];
        }
    }
    
    double Party::getGold()
    {
        return gold;
    }
    void Party::setGold(double g)
    {
        gold = g;
    }
    int Party::getIngredients()
    {
        return ingredients;
    }
    void Party::setIngredients(int i)
    {
        ingredients = i;
    }
    int Party::getNumArmor()
    {
        return num_armor;
    }
    void Party::setNumArmor(Player p[])
    {
        int counter = 0;
        for (int i = 0; i < 5; i++)
        {
            if (p[i].getArmor() == true)
            {
                counter++; 
            }
        }
        num_armor = counter;
    }
    int Party::getNumWeapons()
    {
        return num_weapons;
    }
    void Party::setNumWeapons(Player p[])
    {
        int counter = 0;
        for (int i = 0; i < 5; i++)
        {
            if (p[i].getWeapon() != "")
            {
                counter++;
            }
        }
    num_weapons = counter;
    }
    int Party::getCookwareAt(int cIndex)
    {
        return cookware[cIndex];
    }
    void Party::setCookwareAt(int cook, int cIndex)
    {
        cookware[cIndex] = cook;
    }
    int Party::getActiveMembers(Player p[])
    {
        return activeMembers;
    }
    void Party::setActiveMembers(Player p[])
    {
        activeMembers = 0;
        for (int i = 0; i < 5; i++)
        {
            if (p[i].getStatus() == true)
            {
                activeMembers++;
            }
        }
    }
    bool Party::getTreasureFoundAt(int tRow, int tColumn)
    {
        return treasureFound[tRow][tColumn];
    }
    void Party::setTreasureFoundAt(int tRow, int tColumn, bool isFound)
    {
        treasureFound[tRow][tColumn] = isFound;
    }
