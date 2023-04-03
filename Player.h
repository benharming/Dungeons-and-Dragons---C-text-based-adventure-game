#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
using namespace std;

class Player{
    private:
    string name;
    int fullness;
    string weapon;
    bool armor;
    bool status;
    string causeOfDeath;

    public:
    Player();
    Player(string, int, string, bool, bool);

    string getName();
    void setName(string);

    int getFullness();
    void setFullness(int);

    string getWeapon();
    void setWeapon(string);

    bool getArmor();
    void setArmor(bool);

    bool getStatus();
    void setStatus(bool);

    void setCauseOfDeath(string d);
    string getCauseOfDeath();
};

#endif
