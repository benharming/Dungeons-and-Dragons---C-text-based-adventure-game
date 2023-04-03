#include "Party.h"
#include "Player.h"
#include "Map.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


void statusUpdate(Party &player,Room &room, Player array[])
{
    int treasureFound = 0;
    int treasureAmount = 0;
    player.setActiveMembers(array); // chekcs for the correct amount of players 
    cout << endl;
    cout << ":::::::::::::::::::::::: STATUS UPDATE ::::::::::::::::::::::::" << endl;
    cout << endl;
    cout << "Current room: ";
    if (room.getRoom() == 0)
    {
        cout << "No room" << endl;
    }
    if (room.getRoom() == 1)
    {
        cout << "Room 1" << endl;
    }
    if (room.getRoom() == 2)
    {
        cout << "Room 2" << endl;
    }
    if (room.getRoom() == 3)
    {
        cout << "Room 3" << endl;
    }
    if (room.getRoom() == 4)
    {
        cout << "Room 4" << endl;
    }
    if (room.getRoom() == 5)
    {
        cout << "Room 5" << endl;
    }

    cout << "Sorcerer's anger level: " << room.getSorcererAnger() << " out of 100" << endl;

    cout << "Gold: " << player.getGold() << endl;
    cout << endl;

    cout << "Party Members:" << endl;
    for(int i = 0; i < player.getActiveMembers(array); i++)
    {
        if(array[i].getStatus() == true)
        {
            cout << array[i].getName() << ": || Fullness Points: " << array[i].getFullness() << " || Weapon: ";
            if(array[i].getWeapon() == "")
            {
                cout << "No Weapons ||";
            }
            else
            {
                cout << array[i].getWeapon();
            }
            cout << " || Armor: ";
            if(array[i].getArmor() == true)
            {
                cout << "Equiped with armor!" << endl;
            }
            else
            {
                cout << "No armor equipped!" << endl;
            }
        }  
           
    }
    cout << endl;
    cout << "Materials: " << endl;
    cout << "Ingredients: " << player.getIngredients() << " kilograms" << endl;
    cout << "Cookware: " << player.getCookwareAt(0) << " Ceramic Pot(s), " << player.getCookwareAt(1) << " Frying Pan(s), and " << player.getCookwareAt(2) << " Cauldron(s)" << endl;
    cout << endl;
    Map map;
    map.displayMap();
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;

}

