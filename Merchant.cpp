#include "Merchant.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Merchant::Merchant(){
    numGold=100.0;
    ingredient=0;
    weapons=0;
    armor=0;
    cookware=0;
    treasures=0;
}

Merchant::Merchant(double gold, int i, int w, int a, int c , int t){
    numGold=gold;
    ingredient=i;
    weapons=w;
    armor=a;
    cookware=c;
    treasures=t;
}

double Merchant::getnumGold(){
    return numGold;
}

void Merchant::setnumGold(double gold){
    numGold=gold;
}

int Merchant::getIngredient(){
    return ingredient;
}

void Merchant::setIngredient(int i){
    ingredient=i;
}

int Merchant::getWeapons(){
    return weapons;
}

void Merchant::setWeapons(int w){
    weapons=w;
}

int Merchant::getArmor(){
    return armor;
}

void Merchant::setArmor(int a){
    armor=a;
}

int Merchant::getCookware(){
    return cookware;
}

void Merchant::setCookware(int c){
    cookware=c;
}

int Merchant::getTreasures(){
    return treasures;
}

void Merchant::setTreasures(int t){
    treasures=t;
}