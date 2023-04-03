#include "Room.h"
#include <iostream>
#include <fstream>
#include <string> 
using namespace std;


    Room::Room()
    {
        room = 0;
        for(int i = 0; i < 5; i++)
        {
            keys[i] = false;
        }
        sorcererAnger = 0;
        ifstream fin;
        string line;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                treasure[i][j] = ""; 
            }
        }


    }
    Room::Room(double r, bool k[], int s, string t[][3])
    {
        room = r;
        for (int i = 0; i < 5; i++)
        {
            keys[i] = k[i];
        }
        sorcererAnger = s;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                treasure[i][j] = t[i][j];
            }
        }
    }

    double Room::getRoom()
    {
        return room;
    }
    void Room::setRoom(double r)
    {
        room = r;
    }
    
    bool Room::getKeyAt(int kIndex)
    {
        return keys[kIndex];
    }
    void Room::setKeyAt(int kIndex, bool k)
    {
        keys[kIndex] = k;
    }

    int Room::getSorcererAnger()
    {
        return sorcererAnger;
    }
    void Room::setSorcererAnger(int s)
    {
        sorcererAnger = s;
    }
    
    string Room::getTreasureAt(int tRow, int tColumn)
    {
        return treasure[tRow][tColumn];
    }
    void Room::setTreasureAt(int tRow, int tColumn, string tName)
    {
        treasure[tRow][tColumn] = tName;
    }

