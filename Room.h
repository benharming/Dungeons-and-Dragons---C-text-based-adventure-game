#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <string> 
using namespace std;

class Room
{
    private:
        double room;
        bool keys[5];
        int sorcererAnger;
        string treasure[5][3];
        

    public:
        Room();
        Room(double r, bool k[], int s, string t[][3]);
        
        double getRoom();
        void setRoom(double r);

        bool getKeyAt(int kIndex);
        void setKeyAt(int kIndex, bool k);
        
        int getSorcererAnger();
        void setSorcererAnger(int s);

        string getTreasureAt(int r, int c);
        void setTreasureAt(int r, int c, string t);

};
#endif