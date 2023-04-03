#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(){
    name="";
    fullness=50;
    weapon="";
    armor=0;
    status=1;
}

Player::Player(string n, int f, string w, bool a, bool s){
    name=n;
    fullness=f;
    weapon=w;
    armor=a;
    status=s;
}

string Player::getName(){
    return name;
}

void Player::setName(string n){
    name=n;
}

int Player::getFullness(){
    return fullness;
}

void Player::setFullness(int f){
    fullness=f;

}

string Player::getWeapon(){
    return weapon;
}

void Player::setWeapon(string w){
    weapon=w;
}

bool Player::getArmor(){
    return armor;
}

void Player::setArmor(bool a){
    armor=a;
}

bool Player::getStatus(){
    return status;
}

void Player::setStatus(bool s){
    status=s;
}

void Player::setCauseOfDeath(string d)
{
    causeOfDeath = d;
}

string Player::getCauseOfDeath()
{
    return causeOfDeath;
}