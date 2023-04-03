#define MERCHANT_H
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Merchant{
    private:
    double numGold;
    int ingredient;
    int weapons;
    int armor;
    int cookware;
    int treasures;


    public:
    Merchant();
    Merchant(double, int, int, int, int, int);

    double getnumGold();
    void setnumGold(double);

    int getIngredient();
    void setIngredient(int);

    int getWeapons();
    void setWeapons(int);

    int getArmor();
    void setArmor(int);

    int getCookware();
    void setCookware(int);

    int getTreasures();
    void setTreasures(int);

};