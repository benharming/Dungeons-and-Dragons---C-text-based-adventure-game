#include "Room.h"
#include "Party.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void displayFinalStats(Party &player, Room &room, Player array[], bool win)
{
    if (win == true) // if player wins the game 
    {
        ofstream file; //  outputs info 
        vector <string> treasureName;
        int treasureAmount = 0;
        file.open("results.txt");
        file << endl; 
        file << "::::::::::::::::: FINAL STATS ::::::::::::::::::" << endl;
        cout << endl;
        cout << "::::::::::::::::: FINAL STATS ::::::::::::::::::" << endl;
        file << endl;
        file << "It took you " << room.getSorcererAnger() / 2 << " turns to escape." << endl;
        cout << endl;
        cout << "It took you " << room.getSorcererAnger() / 2 << " turns to escape the dungeon!" << endl;
        file << "You escaped the dungeon and the sorcer with " << player.getGold() << " gold remaining" << endl;
        cout << "You escaped the dungeon and the sorcer with " << player.getGold() << " gold remaining!" << endl;

        if (player.getActiveMembers(array) == 1) //if the leader is the only one left 
        {
            file << endl;
            file << "You were the only one to survive. Your party members will rest in peace" << endl;
            file << endl;
            cout << endl;
            cout << "You were the only one to survive. Your party members will rest in peace" << endl;
            cout << endl;
            file << "Heres what went wrong for your party members: " << endl;
            cout << "Heres what went wrong for your party members: " << endl;
            for (int i = 1; i < 5; i++)
            {
                file << array[i].getName();
                cout << array[i].getName();
                file << " was killed by " << array[i].getCauseOfDeath() <<endl;
                cout << " was killed by " << array[i].getCauseOfDeath() <<endl;
            }
            file << endl;
            file << "These are the treasures you found on your journey:" << endl;
            cout << endl;
            cout << "These are the treasures you found on your journey:" << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (player.getTreasureFoundAt(i, j) == true)
                    {
                        file << "(" << treasureAmount + 1 << ") " << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        cout << "(" << treasureAmount + 1 << ") " << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        treasureName.push_back(room.getTreasureAt(i, j));
                        treasureAmount++; 
                    }
                }
            }
            file << endl;
            file << "::::::::::::::::: GAME OVER :::::::::::::::::::" << endl;
            file << endl;
            cout << endl;
            cout << "::::::::::::::::: GAME OVER :::::::::::::::::::" << endl;
            cout << endl;

        }
        else if (player.getActiveMembers(array) == 5) //if everyone lived
        {
            file << endl;
            file << "You escpaed the sorcer and the dungeon without any of your party dying! Great Job!" << endl; 
            cout << endl;
            cout << "You escpaed the sorcer and the dungeon without any of your party dying! Great Job!" << endl; 
            file << endl;
            file << "Here are the treasures you found on your journey:" << endl;
            cout << endl;
            cout << "Here are the treasures you found on your journey:" << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (player.getTreasureFoundAt(i, j) == true)
                    {
                        file << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        cout << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        treasureName.push_back(room.getTreasureAt(i, j));
                        treasureAmount++; 
                    }
                }
            }
            file << endl;
            file << "::::::::::::::::: GAME OVER ::::::::::::::::::::" << endl;
            file << endl;
            cout << endl;
            cout << "::::::::::::::::: GAME OVER ::::::::::::::::::::" << endl;
            cout << endl;
        }
        else // if more than 1 player won the game 
        {
            file << endl;
            file << "You and ";
            cout << endl; 
            cout << "You and ";
            if (player.getActiveMembers(array) == 2) //if two players won the game 
            {
                file << array[1].getName();
                cout << array[1].getName();
                file << " espaced the sorcer and the dungeon! Great Job!" << endl;
                cout << " espaced the sorcer and the dungeon! Great Job!" << endl;
                file << "Heres went wrong for your party members:" << endl;
                cout << "Heres went wrong for your party members:" << endl;
                for (int i = 1; i < 5; i++)
                {
                    if (array[i].getCauseOfDeath() != "")
                    {
                        file << array[i].getName();
                        cout << array[i].getName();
                        file << " was killed by a " << array[i].getCauseOfDeath() << endl;
                        cout << " was killed by a " << array[i].getCauseOfDeath() << endl;
                    }
                }
                file << endl;
                file << "These are the treasures you found on your journey:" << endl;
                cout << endl;
                cout << "These are the treasures you found on your journey:" << endl;
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 2; j++) // prints out treasure found 
                    {
                        if (player.getTreasureFoundAt(i, j) == true)
                        {
                            file << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                            cout << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                            treasureName.push_back(room.getTreasureAt(i, j));
                            treasureAmount++; 
                        }
                    }
                }
                file << endl;
                file << "================== GAME OVER ==================" << endl;
                file << endl;
                cout << endl;
                cout << "================= GAME OVER ===================" << endl;
                cout << endl;
            }
            else //if three or four players won the game 
            {
                for (int i = 1; i < player.getActiveMembers(array); i++)
                {
                    if (i == player.getActiveMembers(array) - 1)
                    {
                        file << "and " << array[i].getName();
                        cout << "and " << array[i].getName();
                    }
                    else
                    {
                        file << array[i].getName() << ", ";
                        cout << array[i].getName() << ", ";
                    }
                }
                file << " you managed to escape the sorcer and the dungeon but some of your party didn't make it" << endl;;
                file << endl;
                cout << " you managed to escape the sorcer and the dungeon but some of your party didn't make it" << endl;
                file << "Heres what went wrong for your party members: " << endl;
                cout << "Heres what went wrong for your party members: " << endl;
                for (int i = 1; i < 5; i++)
                {
                    if (array[i].getCauseOfDeath() != "")
                    {
                        file << array[i].getName();
                        cout << array[i].getName();
                        file << " was killed by a " << array[i].getCauseOfDeath() << endl;
                        cout << " was killed by a " << array[i].getCauseOfDeath() << endl;
                    }
                }
            }
            file << endl;
            file << "These are the treasures you found on your journey:" << endl;
            cout << endl;
            cout << "These are the treasures you found on your journey:" << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (player.getTreasureFoundAt(i, j) == true)
                    {
                        file << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        cout << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        treasureName.push_back(room.getTreasureAt(i, j));
                        treasureAmount++; 
                    }
                }
            }
            file << endl;
            file << "================== GAME OVER ==================" << endl;
            file << endl;
            cout << endl;
            cout << "================= GAME OVER ===================" << endl;
            cout << endl;
        }

        file.close();
    }
    else //  if the players loose 
    {
        ofstream outFile;
        vector <string> treasureNames;
        int treasureCounter = 0;
        outFile.open("results.txt");
        outFile << endl;
        outFile << "::::::::::::::::: FINAL STATS :::::::::::::::::" << endl;
        cout << endl;
        cout << ":::::::::::::::::: FINAL STATS ::::::::::::::::::" << endl;
        if (room.getSorcererAnger() >= 100) // if sorcerers anger reaches 100
        {
            outFile << endl;
            outFile << "Everyone in party has died! Your party had " << player.getGold() << " gold." << endl;
            cout << endl;
            cout << "Everyone in party has died! Your party had " << player.getGold() << " gold." << endl;
            outFile << "You have made the sorcerer upset and he has destroyed the dungeon and your party" << endl;
            cout << "You have made the sorcerer upset and he has destroyed the dungeon and your party" << endl;
            outFile << endl;
            outFile << "These are the treasures you found on your journey:" << endl;
            cout << endl;
            cout << "These are the treasures you found on your journey:" << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (player.getTreasureFoundAt(i, j) == true)
                    {
                        outFile << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        cout << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        treasureNames.push_back(room.getTreasureAt(i, j));
                        treasureCounter++; 
                    }
                }
            }
            outFile << endl;
            outFile << ":::::::::::::::::: GAME OVER ::::::::::::::::::" << endl;
            outFile << endl;
            cout << endl;
            cout << "::::::::::::::::: GAME OVER ::::::::::::::::::::::" << endl;
            cout << endl;
        }
        else if (player.getActiveMembers(array) == 0) // if everyone died 
        {   
            outFile << endl;
            outFile << "Everyone in party has died! Your party had " << player.getGold() << " gold." << endl;
            cout << endl;
            cout << "Everyone in party has died! Your party had " << player.getGold() << " gold." << endl;
            outFile << endl;
            outFile << "Heres what went wrong for your party members:" << endl;
            cout << endl;
            cout << "Heres what went wrong for your party members:" << endl;
            for (int i = 0; i < 5; i++)
            {
                outFile << array[i].getName();
                cout << array[i].getName();
                outFile << " was killed by a " << array[i].getCauseOfDeath() <<endl;
                cout << " was killed by a " << array[i].getCauseOfDeath() <<endl;
                
            }
            outFile << endl;
            outFile << "These are the treasures you found on your journey:" << endl;
            cout << endl;
            cout << "These are the treasures you found on your journey:" << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (player.getTreasureFoundAt(i, j) == true)
                    {
                        outFile << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        cout << room.getTreasureAt(i, j) << " price " << (i + 1) * 10 << " gold." << endl;
                        treasureNames.push_back(room.getTreasureAt(i, j));
                        treasureCounter++; 
                    }
                }
            }
            outFile << endl;
            outFile << ":::::::::::::::: GAME OVER ::::::::::::::::::::" << endl;
            outFile << endl;
            cout << endl;
            cout << "::::::::::::::::: GAME OVER ::::::::::::::::::::" << endl;
            cout << endl;
        }
        else // if user quits 
        {
            
            outFile << endl;
            outFile << array[0].getName() << " is a coward and exited the dungeon early. The party had " << player.getGold() << " gold before exiting." << endl;
            cout << endl;
            cout << array[0].getName() << " is a coward and exited the dungeon early. The party had " << player.getGold() << " gold before exiting." << endl;
            cout << endl;
            outFile << endl;
            outFile << "These are the treasures you found on your short journey: " << endl;
            cout << endl;
            cout << "These are the treasures you found on your journey: " << endl;
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (player.getTreasureFoundAt(i, j) == true)
                    {
                        outFile << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        cout << room.getTreasureAt(i, j) << " price: " << (i + 1) * 10 << " gold." << endl;
                        treasureNames.push_back(room.getTreasureAt(i, j));
                        treasureCounter++; 
                    }
                }
            }
            outFile << endl;
            outFile << ":::::::::::::::: GAME OVER :::::::::::::::::::" << endl;
            outFile << endl;
            cout << endl;
            cout << "::::::::::::::::: GAME OVER :::::::::::::::::::" << endl;
            cout << endl;
        } 
        
        outFile.close();
    }
}