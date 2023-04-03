#ifndef PARTY_H
#define PARTY_H
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

class Party
{
    private:
    
        Player party[5];
        double gold;
        int ingredients;
        int num_armor;
        int num_weapons;
        int cookware[3];
        int activeMembers;
        bool treasureFound[5][2];

    public:

        Party();
        Party(Player p[], double g, int i, int a, int cook[], int aMems, bool t[][2]);

        Player getPartyMember(int pIndex);
        void setParty(Player p[]);
        
        double getGold();
        void setGold(double g);

        int getIngredients();
        void setIngredients(int i);

        int getNumArmor();
        void setNumArmor(Player p[]);

        int getNumWeapons();
        void setNumWeapons(Player p[]);

        int getCookwareAt(int cIndex);
        void setCookwareAt(int cook, int cIndex);

        int getActiveMembers(Player p[]);
        void setActiveMembers(Player p[]);

        bool getTreasureFoundAt(int tRow, int tColumn);
        void setTreasureFoundAt(int tRow, int tColumn, bool isFound);

};
#endif