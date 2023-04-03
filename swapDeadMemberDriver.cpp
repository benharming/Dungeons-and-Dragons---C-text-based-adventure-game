#include "Party.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;


void swapDeadMembers(Party &player, Room &room, Player array[], int index)
{
    Player temp[5]; // array to hold the Player objects
    Player tempObj = array[index]; // Array to make sure player info is not lost

    for (int i = 0; i < 5; i++) //moves info from array to temp array
    {
        temp[i] = array[i];
    }

    for (int i = 0; i < index; i++) // moves info from temp back to array
    {
        array[i] = temp[i];
    }
    for (int i = index; i < 4; i++) 
    {
        array[i] = temp[i + 1];
    }
    array[4] = tempObj; //assigns original player to last elemnt of array
}

