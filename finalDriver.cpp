#include "Room.h"
#include "Party.h"
#include "Misfortunes.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cctype>
#include "time.h"
#include <ctime>
using namespace std;

int split(string input_string, char separator, string arr[], int arr_size){//creates function with parameters
    int string_length=input_string.length();//sets input string length to integer
    int counter=0;//keeps track of how many pieces the string is split into
    int initial=0;//creates variable for first index
    string sub;
    if(input_string== " "){
        return 0;
    }
    for(int i=0; i<string_length; i++){//loops through each letter in string
        if(input_string[i]==separator){//if the current index is the separator you are looking for
            sub=input_string.substr(initial, i-initial);//creates splitted substring
            arr[counter]=sub;
            initial=i+1;//increase starting position
            counter++;//keeps track of how many time split
        }
        if((string_length-1)==i){//if searching string is at end
            sub=input_string.substr(initial);//creates substring
            arr[counter]=sub;//sets new substring to array
            counter++;
        }
    }
    if(counter>arr_size){
        return -1;
    }
    return counter;
}

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

void merchantMenu(Party &player, Room &room, Player array[]){
    cout << endl;
    cout << "Hello! Welcome to my shop! You may buy ingredients, weapons, armor, and cookware and sell treasure!" << endl; 
    cout << "You have " << player.getGold() << " gold to spend" << endl;
    player.setActiveMembers(array);
    player.setNumArmor(array);

    int shop = 0;
    int armor = 0;
    int ingredient = 0; 
    int cookware, numCookware = 0;
    int weapon, selection = 0;
    string weaponReplace = "x";
    int treasure, treasureFound, treasureAmount = 0;
    vector <string> treasureName;
    string weapons[5] = {"Club(C)", "Spear(S)", "Rapier(R)", "Battle-axe(B)", "Longsword(L)"};

    do{

        cout << endl;
        cout << "Here are your item choices. Let me know what you would like to buy!" << endl;
        cout << "(1) Ingredients: Ingredients allows you to restore fullness points, but a type of cookware is required to use. It costs 5 kilograms of ingredients to increase one fullness point." << endl;
        cout << "(2) Weapons: You are going to need weapons to fend off monsters, I would recommend buying everyone in your party a weapon!" << endl;
        cout << "(3) Armor: Armor is going to protect from monsters, I would also recommned buying all members of your party a set of armor!" << endl;
        cout << "(4) Cookware: Used to cook ingredients to restore fullness points!" << endl;
        cout << "(5) Sell treasure: If you were lucky enough to find some treasures, I'll take those pretty jewels off your hands. But every treasure's value varies, so show me what you got!  " << endl;
        cout << "(0) Exit: Make sure you have everything you need. I'll be vanishing after this sale!" << endl;
        cin >> shop;

        switch(shop){
            case 0: cout<<"Thanks for stopping by, best of luck on your journey!"<<endl;
            break;

            case 1:
                cout << "How many ingredients would you like to buy? 10 kilograms of ingredients costs " << 1 + (room.getRoom() * 0.25) << " gold." <<  endl; 
                cout << "You have " << player.getGold() << " gold, and " << player.getIngredients() << " kilograms of ingredients" << endl;
                cin >> ingredient;

                if (ingredient < 0)
                {
                    cout << "Invalid input!." << endl; 
                }
                else if (ingredient == 0)
                {
                    cout << "Ok no ingredients for you :(" << endl; 
                }
                else if (ingredient + (room.getRoom() * 0.25) > player.getGold()) // checks if they have enough gold to purcahse
                {
                    cout << endl; 
                    cout << "You do not have enough gold to purcahse "<<ingredient<<" kilograms of ingredients" << endl;
                }
                else
                {
                    player.setIngredients(player.getIngredients() + ingredient); //  updates amount of ingredients
                    player.setGold(player.getGold() - (ingredient + (room.getRoom() * 0.25))); // updates amount of gold to what room number they are in
                    cout << endl; 
                    cout << "You now have " << player.getIngredients() << " kilograms of ingredients!"<< endl;
                }
            break;
            
            case 2:
                cout << endl; 
                cout << "(1) A Club(C) costs " << 2 + (2 * (room.getRoom() * 0.25)) << " gold." << endl; 
                cout << "(2) A Spear(S) costs " << 2 + (2 * (room.getRoom() * 0.25)) << " gold." << endl;
                cout << "(3) A +1 Rapier(R) costs " << 5 + (5 * (room.getRoom() * 0.25)) << " gold." << endl;
                cout << "(4) A +2 Battle-axe(B) costs " << 15 + (15 * (room.getRoom() * 0.25)) << " gold." << endl;
                cout << "(5) A +3 Longsword(L) costs " << 50 + (50 * (room.getRoom() * 0.25)) << " gold." << endl;
                cout << endl;
                cout << "Rapiers, Battle-axes, and Longswords will increase your chances of surivival" << endl;
                cout<<endl;

                for (int i = 0; i < player.getActiveMembers(array); i++) //displays each members weapon
                {
                    if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1)
                    {
                        if (array[i].getWeapon() == "")
                        {
                            cout << "and " << array[i].getName() << " does not have a weapon." << endl; 
                        }
                        else
                        {
                            cout << "and " << array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon." << endl;
                        }
                    }
                    else
                    {
                        if (array[i].getWeapon() == "")
                        {
                            cout << array[i].getName() << " does not have a weapon, "; 
                        }
                        else
                        {
                            cout <<  array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon, ";
                        }
                    }
                }

                cout << "You have " << player.getGold() << " gold available to spend. What would you like to purchase?" << endl;
                cin >> weapon;
                
                if (weapon == 0)
                {
                    cout << endl;
                    cout << "Returning to the Merchant Menu." << endl;
                }
                else if (weapon == 1)
                {
                    if (player.getGold() < 2 + (2 * (room.getRoom() * 0.25))) // checks if the party has sufficient funds
                    {
                        cout << endl;
                        cout << "Insuffcient Funds. You only have " <<  player.getGold() << " gold."<< endl;
                    }
                    else
                    {
                        cout << endl; 
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1)
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << "and " << array[i].getName() << " does not have a weapon." << endl; 
                                }
                                else
                                {
                                    cout << "and " << array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon." << endl;
                                }
                            }
                            else
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << array[i].getName() << " does not have a weapon, "; 
                                }
                                else
                                {
                                    cout <<  array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon, ";
                                }
                            }
                        }
                        cout << endl;
                        cout << "Who would like to give the club to?" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            if (player.getActiveMembers(array) == 1)
                            {
                                cout << array[i].getName() << " 1";
                            }
                            else
                            {
                                if (i == player.getActiveMembers(array) - 1)
                                {
                                    cout << "or " << array[i].getName() << " (" << i + 1 << ")";
                                }
                                else
                                {
                                    cout << array[i].getName() << " (" << i + 1 << "), ";
                                }
                            }     
                        }
                        cout << "Press 0 if you would like to return to Merchant Menu." << endl; 
                        cin >> selection;

                        if (selection == 0)
                        {
                            cout << endl; 
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (selection < 0 || selection > player.getActiveMembers(array)) // checks for a valid user input
                        {
                            cout << endl;
                            cout << "Invalid input." << endl; 
                        }
                        else
                        {
                            if (array[selection - 1].getWeapon() != "") //checks if player has a weapon or not
                            {
                                if (array[selection - 1].getWeapon() == "Club") // if the player already has a weapon
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " is already holding a weapon!" << endl;
                                }
                                else
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " already has a " << array[selection - 1].getWeapon() << ". Would you like to replace it with a Club? (Type Yes or No)" << endl;
                                    cin >> weaponReplace;

                                    if (weaponReplace == "yes" || weaponReplace == "Yes")
                                    {   
                                        array[selection - 1].setWeapon("Club"); // sets players weapon to club
                                        player.setGold(player.getGold() - (2 + (2 * (room.getRoom() * 0.25)))); // adjusts gold balance 
                                        cout << endl;
                                        cout << array[selection - 1].getName() << " now has a Club!" << endl;
                                        cout << "You have " << player.getGold() << " gold remaining." << endl;
                                    }
                                    else if (weaponReplace == "no" || weaponReplace == "No")
                                    {
                                        cout << endl; 
                                        cout << array[selection - 1].getName() << " will keep their " << array[selection - 1].getWeapon() <<endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid input." << endl;
                                    }
                                }   
                            }
                            else //  if the player does not have a weapon
                            {
                                array[selection - 1].setWeapon("Club"); // sets players weapon to a club
                                player.setGold(player.getGold() - (2 + (2 * (room.getRoom() * 0.25)))); // adjusts gold balance 
                                cout << endl;
                                cout << array[selection - 1].getName() << " now has a Club!" << endl;
                                cout << "You have " << player.getGold() << " gold remaining." << endl;
                            }
                        }
                    }
                }
                else if (weapon == 2) // spear selection 
                {
                    if (player.getGold() < 2 + (2 * (room.getRoom() * 0.25))) // checks if party has enough money 
                    {
                        cout << endl;
                        cout << "Infsuffcient Funds. You only have " <<  player.getGold() << " gold!"<< endl;
                    }
                    else
                    {
                        cout << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++) // displays palyers weapons
                        {
                            if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1)
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << "and " << array[i].getName() << " does not have a weapon." << endl; 
                                }
                                else
                                {
                                    cout << "and " << array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon." << endl;
                                }
                            }
                            else
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << array[i].getName() << " does not have a weapon, "; 
                                }
                                else
                                {
                                    cout <<  array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon, ";
                                }
                            }
                        } 
                        cout << endl;
                        cout << "Who would you like to give the Spear to?" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            if (player.getActiveMembers(array) == 1)
                            {
                                cout << array[i].getName() << " 1";
                            }
                            else
                            {
                                if (i == player.getActiveMembers(array) - 1)
                                {
                                    cout << "or " << array[i].getName() << " (" << i + 1 << ")";
                                }
                                else
                                {
                                    cout << array[i].getName() << " (" << i + 1 << "), ";
                                }
                            }     
                        }
                        cout << "Press 0 if you would like to return to Merchant Menu." << endl;
                        cin >> selection;

                        if (selection == 0)
                        {
                            cout << endl; 
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (selection < 0 || selection > player.getActiveMembers(array)) // if the user inputs something invalid
                        {
                            cout << endl;
                            cout << "Invalid input." << endl; 
                        }
                        else
                        {
                            if (array[selection - 1].getWeapon() != "") // if player already has a weapon
                            {
                                if (array[selection - 1].getWeapon() == "Spear") //  if player already has a spear
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " is already holding a weapon!" << endl;
                                }
                                else // if player already has something other than a spear
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " already has a " << array[selection - 1].getWeapon() << ". Would you like to replace it with a Spear? (Type Yes or No)" << endl;
                                    cin >> weaponReplace;

                                    if (weaponReplace == "yes" || weaponReplace == "Yes")
                                    {   
                                        array[selection - 1].setWeapon("Spear");
                                        player.setGold(player.getGold() - (2 + (2 * (room.getRoom() * 0.25))));
                                        cout << endl;
                                        cout << array[selection - 1].getName() << " now has a Spear as their weapon!" << endl;
                                        cout << "You have " << player.getGold() << " gold remaining." << endl;
                                    }
                                    else if (weaponReplace == "no" || weaponReplace == "No")
                                    {
                                        cout << endl; 
                                        cout << array[selection - 1].getName() << " will keep their " << array[selection - 1].getWeapon() <<endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid input." << endl;
                                    }
                                }   
                            }
                            else // if player does not have a weapon
                            {
                                array[selection - 1].setWeapon("Spear");
                                player.setGold(player.getGold() - (2 + (2 * (room.getRoom() * 0.25))));
                                cout << endl;
                                cout << array[selection - 1].getName() << " now has a Spear as their weapon!" << endl;
                                cout << "You have " << player.getGold() << " gold remaining." << endl;
                            }
                        }
                    }                      
                }
                else if (weapon == 3) // rapier selection 
                {
                    if (player.getGold() < 5 + (5 * (room.getRoom() * 0.25))) //  checks if they have enough gold
                    {
                        cout << endl;
                        cout << "Insuffcient Funds. You only have " <<  player.getGold() << " gold."<< endl;
                    }
                    else
                    {
                        cout << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++) // displays all players weapons
                        {
                            if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1)
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << "and " << array[i].getName() << " does not have a weapon." << endl; 
                                }
                                else
                                {
                                    cout << "and " << array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon." << endl;
                                }
                            }
                            else
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << array[i].getName() << " does not have a weapon, "; 
                                }
                                else
                                {
                                    cout <<  array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon, ";
                                }
                            }
                        } 
                        cout << endl;
                        cout << "Who would you like to give the Rapier to?" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++) // displays palyers to give weapon to
                        {
                            if (player.getActiveMembers(array) == 1)
                            {
                                cout << array[i].getName() << " 1";
                            }
                            else
                            {
                                if (i == player.getActiveMembers(array) - 1)
                                {
                                    cout << "or " << array[i].getName() << " (" << i + 1 << ")";
                                }
                                else
                                {
                                    cout << array[i].getName() << " (" << i + 1 << "), ";
                                }
                            }     
                        }
                        cout << "Press 0 if you would like to return to Merchant Menu." << endl;
                        cin >> selection;

                        if (selection == 0)
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (selection < 0 || selection > player.getActiveMembers(array)) // if user inputs an ivalid input
                        {
                            cout << endl;
                            cout << "Invalid input." << endl; 
                        }
                        else // 
                        {
                            if (array[selection - 1].getWeapon() != "") // if the player already has weapon
                            {
                                if (array[selection - 1].getWeapon() == "Rapier") // if the player already has a weapon
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " is already holding a weapon!" << endl;
                                }
                                else // if the player has anything else than rapier 
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " already has a " << array[selection - 1].getWeapon() << ". Would you like to replace it with a Rapier? (Type Yes or No)" << endl;
                                    cin >> weaponReplace;

                                    if (weaponReplace == "yes" || weaponReplace == "Yes")
                                    {   
                                        array[selection - 1].setWeapon("Rapier");
                                        player.setGold(player.getGold() - (5 + (5 * (room.getRoom() * 0.25))));
                                        cout << endl;
                                        cout << array[selection - 1].getName() << " now has a Rapier as their weapon!" << endl;
                                        cout << "You have " << player.getGold() << " gold remaining." << endl;
                                    }
                                    else if (weaponReplace == "no" || weaponReplace == "No")
                                    {
                                        cout << endl; 
                                        cout << "Okay! " << array[selection - 1].getName() << " will keep their " << array[selection - 1].getWeapon()<< endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid input." << endl;
                                    }
                                }   
                            }
                            else // if the player has no weapon 
                            {
                                array[selection - 1].setWeapon("Rapier");
                                player.setGold(player.getGold() - (5 + (5 * (room.getRoom() * 0.25))));
                                cout << endl;
                                cout << array[selection - 1].getName() << " now has a Rapier!" << endl;
                                cout << "You have " << player.getGold() << " gold remaining." << endl;
                            }
                        }
                    }
                }
                else if (weapon == 4) // battle-axe selection 
                {
                    if (player.getGold() < 15 + (15 * (room.getRoom() * 0.25))) // chekcs if player has enough gold 
                    {
                        cout << endl;
                        cout << "Insufficient Funds. You only have " <<  player.getGold() << " gold."<< endl;
                    }
                    else 
                    {
                        cout << endl; 
                        for (int i = 0; i < player.getActiveMembers(array); i++) //  displays all active players
                        {
                            if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1)
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << "and " << array[i].getName() << " does not have a weapon." << endl; 
                                }
                                else
                                {
                                    cout << "and " << array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon." << endl;
                                }
                            }
                            else
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << array[i].getName() << " does not have a weapon, "; 
                                }
                                else
                                {
                                    cout <<  array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon, ";
                                }
                            }
                        }
                        cout << endl;
                        cout << "Who would you like to give the Battle-axe to?" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            if (player.getActiveMembers(array) == 1)
                            {
                                cout << array[i].getName() << " 1";
                            }
                            else
                            {
                                if (i == player.getActiveMembers(array) - 1)
                                {
                                    cout << "or " << array[i].getName() << " (" << i + 1 << ")";
                                }
                                else
                                {
                                    cout << array[i].getName() << " (" << i + 1 << "), ";
                                }
                            }     
                        }
                        cout << "Press 0 if you would like to return to Merchant Menu" << endl;
                        cin >> selection;

                        if (selection == 0)
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        if (selection < 0 || selection > player.getActiveMembers(array)) // if the user inputs an invalid input
                        {
                            cout << endl;
                            cout << "Invalid input." << endl; 
                        }
                        else 
                        {
                            if (array[selection - 1].getWeapon() != "") // if the player already has a weapon 
                            {
                                if (array[selection - 1].getWeapon() == "Battle-axe") // if the player already has a battle axe
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " is already holding a weapon!" << endl;
                                }
                                else // if player already has anything else but a battle axe
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " already has a " << array[selection - 1].getWeapon() << ". Would you like to replace it with a Battle-axe? (Type Yes or No)" << endl;
                                    cin >> weaponReplace;

                                    if (weaponReplace == "yes" || weaponReplace == "Yes")
                                    {   
                                        array[selection - 1].setWeapon("Battle-axe");
                                        player.setGold(player.getGold() - (15 + (15 * (room.getRoom() * 0.25))));
                                        cout << endl;
                                        cout << array[selection - 1].getName() << " now has a Battle-axe as their weapon!" << endl;
                                        cout << "You have " << player.getGold() << " gold remaining." << endl;
                                    }
                                    else if (weaponReplace == "no" || weaponReplace == "No")
                                    {
                                        cout << endl; 
                                        cout << array[selection - 1].getName() << " will keep their " << array[selection - 1].getWeapon() << endl;
                                        cout << "You have " << player.getGold() << " gold remaining." << endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid input." << endl;
                                    }
                                }   
                            }
                            else // if the player has no weapon slots 
                            {
                                array[selection - 1].setWeapon("Battle-axe");
                                player.setGold(player.getGold() - (5 + (5 * (room.getRoom() * 0.25))));
                                cout << endl;
                                cout << array[selection - 1].getName() << " now has a Battle-axe as their weapon!" << endl;
                                cout << "You have " << player.getGold() << " gold remaining." << endl;
                            }
                        }                            
                    }                       
                }
                else if (weapon == 5) // longsword selection 
                {
                    if (player.getGold() < 50 + (50 * (room.getRoom() * 0.25))) // checks if player has enough gold 
                    {
                        cout << endl;
                        cout << "Insufficent Funds. You only have " <<  player.getGold() << " gold."<< endl; 
                    }
                    else
                    {
                        cout << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1)
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << "and " << array[i].getName() << " does not have a weapon." << endl; 
                                }
                                else
                                {
                                    cout << "and " << array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon." << endl;
                                }
                            }
                            else
                            {
                                if (array[i].getWeapon() == "")
                                {
                                    cout << array[i].getName() << " does not have a weapon, "; 
                                }
                                else
                                {
                                    cout <<  array[i].getName() << " has a " << array[i].getWeapon() << " as their weapon, ";
                                }
                            }
                        } 
                        cout << endl;
                        cout << "Who would you like to give the Longsword to?" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++) // displays all players 
                        {
                            if (player.getActiveMembers(array) == 1)
                            {
                                cout << array[i].getName() << " 1";
                            }
                            else
                            {
                                if (i == player.getActiveMembers(array) - 1)
                                {
                                    cout << "or " << array[i].getName() << " (" << i + 1 << ")";
                                }
                                else
                                {
                                    cout << array[i].getName() << " (" << i + 1 << "), ";
                                }
                            }     
                        }
                        cout << "Press 0 to return to Merchant Menu" << endl;
                        cin >> selection;

                        if (selection == 0)
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (selection < 0 || selection > player.getActiveMembers(array)) // if user inputs an invalid input 
                        {
                            cout << endl;
                            cout << "Invalid input." << endl; 
                        }
                        else 
                        {
                            if (array[selection - 1].getWeapon() != "") // if player already has a weapon 
                            {
                                if (array[selection - 1].getWeapon() == "Longsword") // if the player already has a longsword
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " is already holding weapon!" << endl;
                                }
                                else // if the player is already has anything but a longsword 
                                {
                                    cout << endl;
                                    cout << array[selection - 1].getName() << " already has a " << array[selection - 1].getWeapon() << ". Would you like to replace it with a longsword (Type Yes or No)" << endl;
                                    cin >> weaponReplace;

                                    if (weaponReplace == "yes" || weaponReplace == "Yes")
                                    {   
                                        array[selection - 1].setWeapon("Longsword");
                                        player.setGold(player.getGold() - (5 + (5 * (room.getRoom() * 0.25))));
                                        cout << endl;
                                        cout << array[selection - 1].getName() << " now has a Longsword as their weapon!" << endl;
                                        cout << "You have " << player.getGold() << " gold remaining." << endl;
                                    }
                                    else if (weaponReplace == "no" || weaponReplace == "No")
                                    {
                                        cout << endl; 
                                        cout << array[selection - 1].getName() << " will keep their " << array[selection - 1].getWeapon() << endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "Invalid input." << endl;
                                    }
                                }   
                            }
                            else // if the player has no weapon 
                            {
                                array[selection - 1].setWeapon("Longsword");
                                player.setGold(player.getGold() - (50 + (50 * (room.getRoom() * 0.25))));
                                cout << endl;
                                cout << array[selection - 1].getName() << " now has a Longsword as their weapon!" << endl;
                                cout << "You have " << player.getGold() << " gold remaining." << endl; 
                            }
                        }    
                    }                       
                }
                else
                {
                    cout << endl;
                    cout << "Invalid input." << endl;
                }
            break;

            case 3:
            player.setNumArmor(array); 
                if (player.getActiveMembers(array) == player.getNumArmor()) //  if all players have armor
                {
                    cout << endl;
                    cout << "Everyone " << player.getActiveMembers(array) << " already has armor! No more armor is avaliable." << endl; 
                }
                else // if at least one player doesn't have armor 
                {
                    if (player.getGold() < 5 + (5 * (room.getRoom() * 0.25))) //checks if they have enough gold
                    {
                        cout << endl;
                        cout << "Insufficient Funds!" << endl;
                    }
                    else 
                    {
                        cout << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++) // displays each player and if they have armor 
                        {
                            if (i == player.getActiveMembers(array) - 1 && player.getActiveMembers(array) != 1) 
                            {
                                if (array[i].getArmor() == false)
                                {
                                    cout << "and " << array[i].getName() << " does not have armor." << endl; 
                                }
                                else
                                {
                                    cout << "and " << array[i].getName() << " has armor." << endl;
                                }
                            }
                            else
                            {
                                if (player.getActiveMembers(array) == 1)
                                {
                                    cout << array[i].getName() << " does not have a set of armor.";
                                }
                                else
                                {
                                    if (array[i].getArmor() == false)
                                    {
                                        cout << array[i].getName() << " does not have armor, "; 
                                    }
                                    else
                                    {
                                        cout <<  array[i].getName() << " has armor, ";
                                    }
                                }
                                
                            }
                        }
                        cout << endl;
                        cout << "Who would you like to the purchase the armor for?" << endl;
                    
                        for (int i = 0; i < player.getActiveMembers(array); i++) // displays each player
                        {
                            if (player.getActiveMembers(array) == 1)
                            {
                                cout << array[i].getName() << " 1";
                            }
                            else
                            {
                                if (i == player.getActiveMembers(array) - 1)
                                {
                                    cout << "or " << array[i].getName() << " (" << i + 1 << ")";
                                }
                                else
                                {
                                    cout << array[i].getName() << " (" << i + 1 << "), ";
                                }
                            }     
                        }
                        cout << "Press 0 to return to Merchant Menu." << endl;
                        cin >> armor;
                        

                        if (armor == 0) 
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu." << endl;
                        }
                        else if (armor < 0 || armor > player.getActiveMembers(array)) // if the user enters an invalid input
                        {
                            cout << endl;
                            cout << "Invalid input." << endl; 
                        }
                        else   
                        {
                            if (array[armor - 1].getArmor() == true) // checks if player already has armor
                            {
                                cout << endl;
                                cout << array[armor - 1].getName() << " already has armor!" << endl;   
                            }
                            else // if player does not have armor 
                            {
                                array[armor - 1].setArmor(true); //  updates armor
                                player.setGold(player.getGold() - (5 + (5 * (room.getRoom() * 0.25)))); // adjusts gold balance 
                                player.setNumArmor(array);
                                cout << endl;
                                cout << array[armor - 1].getName() << " now has armor!" << endl;
                                cout << "You have " << player.getGold() << " gold remaining." << endl;
                            }
                        }
                    }   
                }
                break;
                

                case 4:
                 cout << endl; 
                cout << "(1) A ceramic pot costs " << 5 + (5 * (room.getRoom() * 0.25)) << " gold, with a 25% chance of breaking" << endl; 
                cout << "(2) A frying pan costs " << 10 + (10 * (room.getRoom() * 0.25)) << " gold, with a 10% chance of breaking" << endl;
                cout << "(3) A cauldron costs " << 20 + (20 * (room.getRoom() * 0.25)) << " gold, with a 2% chance of breaking" << endl; 
                cout << endl;
                cout << "You have " << player.getCookwareAt(0) << " ceramic pot, " << player.getCookwareAt(1) << " frying pan, and " << player.getCookwareAt(2) << " cauldron." << endl; 
                cout << "You have "<< player.getGold() << " gold available to spend. What cookware would you like to buy?." << endl;
                cin >> cookware;

                if (cookware == 0)
                {
                    cout << endl;
                    cout << "Returning to Merchant Menu" << endl;
                }
                else if (cookware == 1) //cermaic pot selection 
                {
                    if (player.getGold() < 5 + (5 * (room.getRoom() * 0.25))) // checks if they have enough gold 
                    {
                        cout << endl;
                        cout << "Insufficient Funds. You only have " << player.getGold() << " gold." << endl;
                    }
                    else
                    {
                        cout << endl; 
                        cout << "A Ceramic pot is " << 5 + (5 * (room.getRoom() * 0.25)) << " gold. How many would you like?" << endl; 
                        cout << "You have " << player.getGold() << " gold avaiable to spend." << endl;
                        cin >> numCookware;

                        if (numCookware < 0)
                        {
                            cout << endl; 
                            cout << "Invalid Input!" << endl;
                        }
                        else if (numCookware == 0)
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (numCookware * (5 + (5 * (room.getRoom() * 0.25))) > player.getGold()) //  checks if they have insufficient funds
                        {
                            cout << endl; 
                            cout << "Insufficient Funds. You only have " << player.getGold() << " gold." << endl;
                        }
                        else 
                        {
                            player.setCookwareAt(numCookware + player.getCookwareAt(0), 0); // updates amount of cookware
                            player.setGold(player.getGold() - (numCookware * (5 + (5 * (room.getRoom() * 0.25))))); // updates gold balance 
                            cout << endl;
                            cout << "You now have " << player.getCookwareAt(0) << " ceramic pot, and " << player.getGold() << " gold left!" << endl;
                        }
                    }
                }
                else if (cookware == 2) // frying pan option 
                {
                    if (player.getGold() < 10 + (10 * (room.getRoom() * 0.25))) // checks if they have enough gold 
                    {
                        cout << endl;
                        cout << "Insufficent Funds. You only have " << player.getGold() << " gold." << endl; 
                    }
                    else
                    {
                        cout << endl; 
                        cout << "A Frying pans is " << 10 + (10 * (room.getRoom() * 0.25)) << " gold. How many would you like?" << endl;
                        cout << "You have " << player.getGold() << " gold available to spend." << endl; 
                        cin >> numCookware;

                        if (numCookware < 0)
                        {
                            cout << endl; 
                            cout << "Invalid Input!" << endl;
                        }
                        else if (numCookware == 0)
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (numCookware * (10 + (10 * (room.getRoom() * 0.25))) > player.getGold()) //  if they have insufficeint funds
                        {    
                            cout << endl; 
                            cout << "Insufficient Funds. You only have " << player.getGold() << " gold." << endl;
                        }
                        else //  if they don't have enough gold to buy how many pans they want 
                        {
                            player.setCookwareAt(numCookware + player.getCookwareAt(1), 1); // updates amount of cookware
                            player.setGold(player.getGold() - (numCookware * (10 + (10 * (room.getRoom() * 0.25))))); //updates gold balance 
                            cout << endl; 
                            cout << "You now have " << player.getCookwareAt(1) << " frying pan, and " << player.getGold() << " gold left!" << endl;
                        }
                    }
                }
                else if (cookware == 3) // cauldron option 
                {
                    if (player.getGold() < 20 + (20 * (room.getRoom() * 0.25))) // checks if they have enough gold 
                    {
                        cout << endl;
                        cout << "Insufficient Funds. You only have " << player.getGold() << " gold." << endl; 
                    }
                    else 
                    {
                        cout << endl; 
                        cout << "Cauldrons are " << 20 + (20 * (room.getRoom() * 0.25)) << " gold a. How many would you like?" << endl;
                        cout << "You have " << player.getGold() << " gold available to spend." << endl; 
                        cin >> numCookware;

                        if (numCookware < 0)
                        {
                            cout << endl; 
                            cout << "Invalid Input!" << endl;
                        }
                        else if (numCookware == 0)
                        {
                            cout << endl;
                            cout << "Returning to Merchant Menu" << endl;
                        }
                        else if (numCookware * (20 + (20 * (room.getRoom() * 0.25))) > player.getGold()) // if they have insufficient funds
                        {
                            cout << endl; 
                            cout << "Insufficent Funds. You only have " << player.getGold() << " gold." << endl;
                        }
                        else // if they don't have enough gold to buy how many cauldrons they want 
                        {
                            player.setCookwareAt(numCookware + player.getCookwareAt(2), 2); //  updates amount of cookware
                            player.setGold(player.getGold() - (numCookware * (20 + (20 * (room.getRoom() * 0.25))))); // updates gold balance 
                            cout << endl; 
                            cout << "You now have " << player.getCookwareAt(2) << " cauldron, and " << player.getGold() << " gold left!" << endl;
                        }
                    }
                }
                else
                {
                    cout << endl; 
                    cout << "Invalid input." << endl;
                }
            break;
            
            case 5:
            treasureFound = 0;
                treasureName.clear();
                for (int i = 0; i < 5; i++)
                {
                    for (int j = 0; j < 2; j++) //  checks how many treasures have been found 
                    {
                        if (player.getTreasureFoundAt(i, j) == true)
                        {
                            treasureFound++;
                        }
                    }
                }
                if (treasureFound == 0) // if no treasure has been found 
                {
                    cout << endl;
                    cout << "You have no Treasure to sell :(" << endl;
                }
                else // if 1 or more treasures have been found 
                {
                    treasureAmount = 0;
                    cout << endl;
                    cout << "Treasure in Room 1 is worth 10 gold." << endl;
                    cout << "Treasure in Room 2 is worth 20 gold." << endl;
                    cout << "Treasure in Room 3 is worth 30 gold." << endl;
                    cout << "Treasure in Room 4 is worth 40 gold." << endl;
                    cout << "Treasure in Room 5 is worth 50 gold." << endl;
                    cout << "You have these Treasures to sell:" << endl;
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 2; j++) //  prints out treasure items that they can sell
                        {
                            if (player.getTreasureFoundAt(i, j) == true)
                            {
                                cout << "(" << treasureAmount + 1 << ") " << room.getTreasureAt(i, j) << " SELLING PRICE: " << (i + 1) * 10 << " gold." << endl;
                                treasureName.push_back(room.getTreasureAt(i, j));
                                treasureAmount++; 
                            }
                        }
                    }
                    cout << endl;
                    cout << "What treasure would you like to sell?" << endl; 
                    cin >> treasure;

                    if (treasure == 0)
                    {
                        cout << endl;
                        cout << "Returning to Merchant Menu." << endl;
                    }
                    else if (treasure > 0 && treasure <= treasureAmount) // if users input is invalid 
                    {
                        cout << endl;
                        cout << "I'll take that " << treasureName.at(treasure - 1) << " for ";
                        if (room.getTreasureAt(0,0) == treasureName.at(treasure - 1) || room.getTreasureAt(0,1) == treasureName.at(treasure - 1))
                        {
                            player.setGold(player.getGold() + 10); // updates gold balance 
                            cout << "10 gold! You now have " << player.getGold() << " gold!" << endl;
                            if (room.getTreasureAt(0,0) == treasureName.at(treasure - 1))
                            {
                                player.setTreasureFoundAt(0,0, false); //  removes treasure from inventory 
                            }
                            else
                            {
                                player.setTreasureFoundAt(0,1, false); // removes treasure from inventory
                            }

                        }
                        if (room.getTreasureAt(1, 0) == treasureName.at(treasure - 1) || room.getTreasureAt(1, 1) == treasureName.at(treasure - 1))
                        {
                            player.setGold(player.getGold() + 20); // updates gold balance 
                            cout << "20 gold! You now have " << player.getGold() << " gold!" << endl;
                            if (room.getTreasureAt(1, 0) == treasureName.at(treasure - 1))
                            {
                                player.setTreasureFoundAt(1, 0, false); // removes treasure from inventory
                            }
                            else
                            {
                                player.setTreasureFoundAt(1, 1, false); //removes treasure from inventory
                            }
                        }
                        if (room.getTreasureAt(2, 0) == treasureName.at(treasure - 1) || room.getTreasureAt(2,1) == treasureName.at(treasure - 1))
                        {
                            player.setGold(player.getGold() + 30); // updates gold balance 
                            cout << "30 gold! You now have " << player.getGold() << " gold!" << endl;
                            if (room.getTreasureAt(2, 0) == treasureName.at(treasure - 1))
                            {
                                player.setTreasureFoundAt(2, 0, false); // removes treasure from inventory
                            }
                            else
                            {
                                player.setTreasureFoundAt(2, 1, false); // removes treasure from inventory
                            }
                        }
                        if (room.getTreasureAt(3, 0) == treasureName.at(treasure- 1) || room.getTreasureAt(3,1) == treasureName.at(treasure - 1)) 
                        {
                            player.setGold(player.getGold() + 40); // updaates gold balance 
                            cout << "40 gold! You now have " << player.getGold() << " gold!" << endl;
                            if (room.getTreasureAt(3, 0) == treasureName.at(treasure - 1))
                            {
                                player.setTreasureFoundAt(3, 0, false); // removes treasure from inventory
                            }
                            else
                            {
                                player.setTreasureFoundAt(3, 1, false); // removes treasure from inventory
                            }
                        }
                        if (room.getTreasureAt(4, 0) == treasureName.at(treasure - 1) || room.getTreasureAt(4, 1) == treasureName.at(treasure - 1)) 
                        {
                            player.setGold(player.getGold() + 50); // updates gold balance 
                            cout << "50 gold! You now have " << player.getGold() << " gold!" << endl;
                            if (room.getTreasureAt(4, 0) == treasureName.at(treasure - 1))
                            {
                                player.setTreasureFoundAt(4, 0, false); // removes treasure from inventory
                            }
                            else
                            {
                                player.setTreasureFoundAt(4, 1, false); // removes treasure from inventory
                            }
                        }
                    }
                    else
                    {
                        cout << endl; 
                        cout << "Invalid input." << endl;
                    }
                }
            break;

             default:
                cout << endl;
                cout << "Invalid input." << endl;
            break;
        } 

    }while(shop!=0);
}

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

/*
-function takes in the room number (int) as a paramter and generates a random monster depending on which room the player is in
-returns a string (the random monster)
*/
string getRandomMonster(int roomNumber)
{
    srand(time(NULL));
    int randomMonster = rand() % 4 + 1; // random int b/w 1-4 to generate which monster lvl to choose from
    string monster;
   
    if (roomNumber == 1)
    {
        if (randomMonster == 1)
        {
            monster = "Animated armor";
        }
        if (randomMonster == 2)
        {
            monster = "Bugbear";
        }
        if (randomMonster == 3)
        {
            monster = "Harpy";
        }
        if (randomMonster == 4)
        {
            monster = "Scarecrow";
        }
    }
    if (roomNumber == 2)
    {
        if (randomMonster == 1)
        {
            monster = "Minotaur";
        }
        if (randomMonster == 2)
        {
            monster = "Owlbear";
        }
        if (randomMonster == 3)
        {
            monster = "Banshee";
        }
        if (randomMonster == 4)
        {
            monster = "Wereboar";
        }
    }
    if (roomNumber == 3)
    {
        if (randomMonster == 1)
        {
            monster = "Giant crocodile";
        }
        if (randomMonster == 2)
        {
            monster = "Troll";
        }
        if (randomMonster == 3)
        {
            monster = "Hobgoblin warrior";
        }
        if (randomMonster == 4)
        {
            monster = "Mammoth";
        }
    }
    if (roomNumber == 4)
    {
        if (randomMonster == 1)
        {
            monster = "Stone giant";
        }
        if (randomMonster == 2)
        {
            monster = "Night hag";
        }
        if (randomMonster == 3)
        {
            monster = "Assassin";
        }
        if (randomMonster == 4)
        {
            monster = "Hydra";
        }
    }
    if (roomNumber == 5)
    {
        if (randomMonster == 1)
        {
            monster = "Cloud giant";
        }
        if (randomMonster == 2)
        {
            monster = "Silver dragon";
        }
        if (randomMonster == 3)
        {
            monster = "Vampire";
        }
        if (randomMonster == 4)
        {
            monster = "Lich";
        }
    }
    return monster;
}
/*
-takes in 3 parameters, player (Party), room (Room), array[] (Player)
-The function calculates the winner of the fight based off of the formula given to us
-returns a bool, true if win and false if lose
*/
bool getMonsterWinner(Party &player, Room &room, Player array[])
{
    player.setNumArmor(array);
    player.setActiveMembers(array);
    player.setNumWeapons(array);

    srand(time(NULL));
    int randNumOne = rand() % 6 + 1; //random number b/w 1-6
    int randNumTwo  = rand() % 36 + 6; // another random number seperate from num1
    randNumTwo = randNumTwo / 6; //makes randnum 2 b/w 1-6

    int numArmor = player.getNumArmor();
    int numWeapons = player.getNumWeapons();
    int challengeLvl = room.getRoom();
    int numUpgradedWeapons = 0;

    bool clubFound = false;
    bool spearFound = false;
    bool rapierFound = false;
    bool battleAxeFound = false;
    bool longswordFound = false;
    int bonuspts = 0;

    double armorVar = 0;

    for(int i = 0; i < 5; i++)
    {
        if (array[i].getWeapon() == "Club")
        {
            clubFound = true;
        }
        if (array[i].getWeapon() == "Spear")
        {
            spearFound = true;
        }
        if (array[i].getWeapon() == "Rapier")
        {
            rapierFound = true;
            numUpgradedWeapons++;
        }
        if (array[i].getWeapon() == "Battle-axe")
        {
            battleAxeFound = true;
            numUpgradedWeapons++;
        }
        if (array[i].getWeapon() == "Longsword")
        {
            longswordFound = true;
            numUpgradedWeapons++;
        }
    }
    if (clubFound == true && spearFound == true && rapierFound == true && battleAxeFound == true && longswordFound == true) // check if every weapon is found + adds a bonus point
    {
        bonuspts = 1;
    }
   
    if (numArmor == 0) // because cant divide by 0
    {
        armorVar = 1;
    }
    else
    {
        armorVar = 1 / numArmor; //used as 1/a
    }
   
   double winNumber = (randNumOne * (numWeapons + numUpgradedWeapons) + bonuspts) - ((randNumTwo * challengeLvl) * armorVar); //calculates the winner
   if (winNumber > 0) //returns true if win and false if lose...
   {
       return true;
   }
   else
   {
       return false;
   }
   
}


void setTreasure(Room &room){
    ifstream file;
    string line;
    int counter=0;
    string splitter[3];
    file.open("treasure.txt");

    while(getline(file, line)){
        if(line!= "1 Room" && line!= "2 Rooms" && line!="3 Rooms" && line!="4 Rooms" && line!="5 Rooms"){
            split(line, ',' , splitter, 3);
            room.setTreasureAt(counter, 0, splitter[0]);
            room.setTreasureAt(counter, 1, splitter[1]);
            room.setTreasureAt(counter, 2, splitter[2]);
            counter++;

        }
    }
    file.close();
}

void setRiddle(string riddles[][2])
{
    ifstream inFile;
    string line;
    int counter = 0;
    string spl[2];
    inFile.open("riddles.txt");
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            if (line != "")
            {
                split(line, ',', spl, 2);
                riddles[counter][0] = spl[0];
                riddles[counter][1] = spl[1];
                counter++;
            }
        }
    }
    inFile.close();
}

int main(){
    Player leader, player1, player2, player3, player4;
    Player array[5] = {leader, player1, player2, player3, player4};
    Party player;
    player.setParty(array);

    // initialize variables (these will be used as different options and counters for various aspects of the game)
    bool finished = false;
    bool wonGame = false;
    int action = 1;
    int weaponNum = 0;
    int merchantChance = 0;
    int playersWeapon = 0;
    int monsterChoice = 0;
    int armorNum = 0;
    int playerArmor = 0;
    int cookwareChoice = 0;
    int ingredientChoice = 0;
    int x = 0;
    string riddles[10][2];
    setRiddle(riddles);
    string riddleSol = "";
    char tempChar = 'a';
    string tempStr = "";
    string monster = "";
    bool monsterWin = false;
    bool monsterZ = false;
   
    cout << endl;
    cout << "Welcome! What is your name?" << endl;
    string leaderName;
    getline(cin, leaderName);
    array[0].setName(leaderName);

    cout << endl;
    cout << "Nice to meet you, " << array[0].getName() << "! Please introduce your 4 companions: (Press enter after each name entry!)" << endl;
    string name1, name2, name3, name4;
    getline(cin, name1);
    getline(cin, name2);
    getline(cin, name3);
    getline(cin, name4);
    array[1].setName(name1);
    array[2].setName(name2);
    array[3].setName(name3);
    array[4].setName(name4);

    cout << endl;
    cout << "Awesome! " << name1 << ", " << name2 << ", " << name3 << ", and " << name4 << ", I'm glad you can join " << leaderName <<" on his/her journey!" << endl;
    cout << endl;
    cout << "My name is Porky and I will be your guide." << endl;
    cout << endl;
    cout << "To escape the dungeon, you must be clear all 5 rooms while fighting monsters, interacting with various merchants, exploring the rooms, and solving puzzles" << endl;
    cout << endl;
    cout << "Your party will start with 100 gold to spend how you like" << endl;
    cout << "You will come across merchants in each room, however their prices increase the further you are in the dungeon, so I recommend stocking up early!" << endl;
   
   
    char ready = 'z';
    Room dungeon;
    setTreasure(dungeon);
   
    do
    {
        cout << "Are you ready to enter the dungeon and start your journey? (Y/N)" << endl; //ask user to start the game
        cin >> ready;

        if (ready == 'y' || ready == 'Y') //allows it to be not case sensitive
        {
            cout << endl;
            cout << "You have now entered the dungeon, let's visit the merchant" << endl;
            merchantMenu(player, dungeon, array);
            dungeon.setRoom(1);

            while (finished == false) //loop runs as long as finished is set to true
            {
                statusUpdate(player, dungeon, array);
                cout << endl;
                cout << "Would you like to (1) Move, (2) Investigate, (3) Pick a Fight, (4) Cook and Eat, or (0) quit?" << endl;
                cin >> action;
                player.setActiveMembers(array);
                player.setNumArmor(array);
                player.setNumWeapons(array);
                Misfortunes misfortune; // misfortune with default likeliness score of 40% to represesnt the misfortune before every turn
                if (action > 5 || action < 1) //validates action choice
                {
                    misfortune.setActualOccurrence(false);
                }
                if (misfortune.getOccurrence() == true)
                {
                    if (misfortune.getActualType() == "armor stolen")
                    {
                        if (player.getNumArmor() == 0) // if there is no armor to be taken a, new misfortune (does this with weapons too)
                        {
                            srand(time(NULL));
                            x = rand() % 3 + 1;
                            if (x == 1)
                            {
                                if (player.getNumWeapons() == 0)
                                {
                                    player.setIngredients(0);
                                    cout << endl;
                                    cout << "Dungeon bandits have stolen all your ingredients!" << endl;
                                }
                                else // if there are weapons to be stolen:
                                {
                                    srand(time(NULL));
                                    playersWeapon = rand() % player.getNumWeapons() + 1; // random number -> person who's weapon is stolen
                                    weaponNum = 0; //counter to compare
                                    for (int i = 0; i < 5; i++)
                                    {
                                        if (array[i].getArmor() == true) //if have armor
                                        {
                                            weaponNum++;
                                            if (weaponNum == playersWeapon) // if counter equals random number, set weapons to empty string
                                            {
                                                array[i].setWeapon("");
                                                cout << endl;
                                                cout << array[i].getName() << " had their weapon stolen by dungeon bandits!" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                            if (x == 2) // all ingredients stolen
                            {
                                player.setIngredients(0);
                                cout << endl;
                                cout << "Dungeon bandits have stolen all your ingredients!" << endl;
                            }
                            if (x == 3) //all cookware stolen
                            {
                                player.setCookwareAt(0, 0);
                                player.setCookwareAt(0, 1);
                                player.setCookwareAt(0, 3);
                                cout << endl;
                                cout << "Dungeon bandits have stolen all your cookware!" << endl;
                            }
                        }
                        else // if party has armor
                        {
                            srand(time(NULL));
                            playerArmor = rand() % player.getNumArmor() + 1; //same as above
                            for (int i = 0; i < 5; i++)
                            {
                                if (array[i].getArmor() == true)
                                {
                                    armorNum++;
                                    if (armorNum == playerArmor)
                                    {
                                        array[i].setArmor(false);
                                        cout << endl;
                                        cout << "Oh no! " << array[i].getName() << " had their armor stolen by dungeon bandits!" << endl;
                                    }
                                }
                            }
                        }
                    }
                    if (misfortune.getActualType() == "armor broke") // if the misfortune is armor broke
                    {
                        if (player.getNumArmor() == 0) // if there no armor to be broken,
                        {
                            srand(time(NULL));
                            x = rand() % 3 + 1;
                            if (x == 1)
                            {
                                if (player.getNumWeapons() == 0) // if total number of weapons among the party is 0
                                {
                                    player.setIngredients(0); // take all ingredients from party.
                                    cout << endl;
                                    cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your ingredients!" << endl;
                                }
                                else // if the party does have weapons:
                                {
                                    srand(time(NULL));
                                    playersWeapon = rand() % player.getNumWeapons() + 1;
                                    weaponNum = 0;
                                    for (int i = 0; i < 5; i++)
                                    {
                                        if (array[i].getArmor() == true)
                                        {
                                            weaponNum++;
                                            if (weaponNum == playersWeapon)
                                            {
                                                array[i].setWeapon("");
                                                cout << endl;
                                                cout << "Oh no! " << array[i].getName() << " had their weapon stolen by dungeon bandits!" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                            if (x == 2) // reset ingredients
                            {
                                player.setIngredients(0);
                                cout << endl;
                                cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your ingredients!" << endl;
                            }
                            if (x == 3) //reset cookware
                            {
                                player.setCookwareAt(0, 0);
                                player.setCookwareAt(0, 1);
                                player.setCookwareAt(0, 3);
                                cout << endl;
                                cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your cookware!" << endl;
                            }
                        }
                        else // if party has armor, pick a random number -> armor gets broken
                        {
                            srand(time(NULL));
                            playerArmor = rand() % player.getNumArmor() + 1;
                            armorNum = 0;
                            for (int i = 0; i < 5; i++)
                            {
                                if (array[i].getArmor() == true)
                                {
                                    armorNum++;
                                    if (armorNum == playerArmor)
                                    {
                                        array[i].setArmor(false);
                                        cout << endl;
                                        cout << "Oh no! " << array[i].getName() << "'s armor broke!" << endl;
                                    }
                                }
                            }
                        }
                    }
                    if (misfortune.getActualType() == "weapon broke")
                    {
                        if (player.getNumWeapons() == 0) // if no weapons
                        {
                            srand(time(NULL));
                            x = rand() % 3 + 1;
                            if (x == 1)
                            {
                                if (player.getNumArmor() == 0) // if no armor reset the ingredients
                                {
                                    player.setIngredients(0);
                                    cout << endl;
                                    cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your ingredients!" << endl;
                                }
                                else // if party has armor,
                                {
                                    srand(time(NULL));
                                    playerArmor = rand() % player.getNumArmor() + 1; //random number decides who's armor is stolen
                                    armorNum = 0;
                                    for (int i = 0; i < 5; i++)
                                    {
                                        if (array[i].getArmor() == true)
                                        {
                                            armorNum++;
                                            if (armorNum == playerArmor)
                                            {
                                                array[i].setArmor(true);
                                                cout << endl;
                                                cout << "Oh no! " << array[i].getName() << " had their armor stolen by dungeon bandits!" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                            if (x == 2) // ingredients stolen
                            {
                                player.setIngredients(0);
                                cout << endl;
                                cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your ingredients!" << endl;
                            }
                            if (x == 3) // cookware stolen
                            {
                                player.setCookwareAt(0, 0);
                                player.setCookwareAt(0, 1);
                                player.setCookwareAt(0, 3);
                                cout << endl;
                                cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your cookware!" << endl;
                            }
                        }
                        else // if party has weapons
                        {
                            srand(time(NULL));
                            playersWeapon = rand() % player.getNumWeapons() + 1;
                            for (int i = 0; i < 5; i++)
                            {
                                if (array[i].getWeapon() != "")
                                {
                                    weaponNum++;
                                    if (weaponNum == playersWeapon)
                                    {
                                        array[i].setWeapon("");
                                        cout << endl;
                                        cout << "Oh no! " << array[i].getName() << "'s weapon broke!" << endl;
                                    }
                                }
                            }
                        }
                    }
                    if (misfortune.getActualType() == "food stolen") // reset ingredients
                    {
                        player.setIngredients(0);
                        cout << endl;
                        cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your ingredients!" << endl;
                    }
                    if (misfortune.getActualType() == "cookware stolen") // reset cookware
                    {
                        player.setCookwareAt(0, 0);
                        player.setCookwareAt(0, 1);
                        player.setCookwareAt(0, 2);
                        cout << endl;
                        cout << "Oh no! Dungeon bandits appeared out of the darkness and stole all your cookware!" << endl;
                    }
                }
                switch (action) // menu selection
                {
                    case 0: // if quit
                        finished = true;
                    break;
                    case 1: //move case -> we made it so you automatically move each time and generate an event instead of using a map (map was not working)
                        cout << endl;
                        cout << "Is that a merchant you spy in the shadows of the room?" << endl;
                        srand(time(NULL));
                        merchantChance = rand() % 3 + 1;
                        if (merchantChance == 1)
                        {
                            monster = getRandomMonster(dungeon.getRoom()); // if merchant is evil
                            cout << endl;
                            cout << "It turns out your gut was wrong, it's actually the " << monster << "!" << endl;
                            do
                            {
                                cout << "Will you choose to attack (1) or surrender a party member to the " << monster << " (2)?" << endl;
                                cin >> monsterChoice;
                                if (monsterChoice == 1)
                                {
                                    cout << endl;
                                    cout << "You work up the courage and attack the " << monster << "!" << endl;
                                    monsterWin = getMonsterWinner(player, dungeon, array);
                                    if (monsterWin == true)
                                    {
                                        srand(time(NULL));
                                        x = rand() % 3 + 1;
                                        cout << endl;
                                        cout << "After a vicious battle, you were able to defeat the monster!" << endl;
                                        cout << "The " << monster << " dropped 10 gold and 5 kilograms of ingredients!" << endl;
                                        player.setIngredients(player.getIngredients() + 20);
                                        player.setGold(player.getGold() + 50);
                                        if (x == 1)
                                        {

                                            cout << "Look! " << monster << " dropped the key to get out of ";
                                            if (dungeon.getRoom() == 1)
                                            {
                                                dungeon.setKeyAt(1, true);
                                                cout << "Room 1!" << endl;
                                            }
                                            if (dungeon.getRoom() == 2)
                                            {
                                                dungeon.setKeyAt(2, true);
                                                cout << "Room 2!" << endl;
                                            }
                                            if (dungeon.getRoom() == 3)
                                            {
                                                dungeon.setKeyAt(3, true);
                                                cout << "Room 3!" << endl;
                                            }
                                            if (dungeon.getRoom() == 4)
                                            {
                                                dungeon.setKeyAt(4, true);
                                                cout << "Room 4!" << endl;
                                            }
                                            if (dungeon.getRoom() == 5)
                                            {
                                                dungeon.setKeyAt(5, true);
                                                cout << "Room 5!" << endl;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "The " << monster << " was able to fend off your attack, but you were able to escape alive" << endl;
                                        for (int i = 1; i < 5; i++)
                                        {
                                            if (array[i].getStatus() == true)
                                            {
                                                srand(time(NULL));
                                                x = rand() % 100 + 1;
                                                if (array[i].getArmor() == true)
                                                {
                                                    if (x <= 5)
                                                    {
                                                        array[x].setStatus(false);
                                                        array[x].setCauseOfDeath(monster);
                                                        array[x].setArmor(false);
                                                        array[x].setWeapon("");
                                                        player.setActiveMembers(array);
                                                        cout << array[i].getName() << " was brutally killed by " << monster << "!" << endl;
                                                        swapDeadMembers(player, dungeon, array, i);
                                                    }
                                                }
                                                else
                                                {
                                                    if (x <= 10)
                                                    {
                                                        array[x].setStatus(false);
                                                        array[x].setCauseOfDeath(monster);
                                                        array[x].setArmor(false);
                                                        array[x].setWeapon("");
                                                        player.setActiveMembers(array);
                                                        cout << array[i].getName() << " was brutally killed by " << monster << "!" << endl;
                                                        swapDeadMembers(player, dungeon, array, i);
                                                    }
                                                }
                                            }
                                        }
                                        cout << "You lost ";
                                        if (player.getIngredients() < 30)
                                        {
                                            cout << player.getIngredients();
                                            player.setIngredients(0);
                                        }
                                        else
                                        {
                                            cout << 30;
                                            player.setIngredients(player.getIngredients() - 30);
                                        }
                                        cout << " kilograms of ingredients and " << player.getGold() * 0.25 << " gold!" << endl;
                                        cout << endl;
                                        cout << "Everyone's fullness levels dropped by one point!" << endl;
                                        for (int i = 0; i < player.getActiveMembers(array); i++)
                                        {
                                            array[i].setFullness(array[i].getFullness() - 1);
                                            if (array[i].getFullness() == 0)
                                            {
                                                cout << array[i].getName() << " has died, their fullness levels dropped to zero!" << endl;
                                                array[i].setCauseOfDeath("Starved");
                                                array[i].setArmor(false);
                                                array[i].setStatus(false);
                                                array[i].setWeapon("");
                                                swapDeadMembers(player, dungeon, array, i);
                                            }
                                        }
                                    }
                                    dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                                }
                                else if (monsterChoice == 2)
                                {
                                    player.setActiveMembers(array);
                                    srand(time(NULL));
                                    x = rand() % (player.getActiveMembers(array) - 1) + 1;
                                    cout << endl;
                                    cout << "You escape from the " << monster << ", while it finished off " << array[x].getName() << endl;
                                    array[x].setStatus(false);
                                    array[x].setCauseOfDeath(monster);
                                    array[x].setArmor(false);
                                    array[x].setWeapon("");
                                    player.setActiveMembers(array);
                                    swapDeadMembers(player, dungeon, array, x);
                                    cout << endl;
                                    cout << "Everyone's fullness levels dropped by one point!" << endl;
                                    for (int i = 0; i < player.getActiveMembers(array); i++)
                                    {
                                        array[i].setFullness(array[i].getFullness() - 1);
                                        if (array[i].getFullness() == 0)
                                        {
                                            cout << array[i].getName() << " has died, their fullness levels dropped to zero!" << endl;
                                            array[i].setCauseOfDeath("Starved");
                                            array[i].setArmor(false);
                                            array[i].setStatus(false);
                                            array[i].setWeapon("");
                                            swapDeadMembers(player, dungeon, array, i);
                                        }
                                    }
                                    dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "Invalid input, try again!" << endl;
                                }
                            } while (monsterChoice != 1 && monsterChoice != 2);
                        }
                        else // if merchant is good
                        {
                            cout << endl;
                            cout << "You inch closer and discover It's a merchant!" << endl;
                            cout << "In order to uncover if the merchant is good or neutral, you will need to answer their riddle correctly." << endl;
                            cout << "If they are good, they will offer to sell goods. If they are neutral, the merchant will peacefully walk away." << endl;
                           
                            srand(time(NULL));
                            x = rand() % 10 + 1;
                            if (merchantChance == 2) // if merchant is neutral
                            {
                                cout << endl;
                                cout << "\"" << riddles[x - 1][0] << "\"" << endl;
                                cin.ignore();
                                getline(cin, riddleSol);

                                for (int i = 0; i < riddleSol.length(); i++)
                                {
                                    tempChar = tolower(riddleSol[i]);
                                    tempStr.push_back(tempChar);
                                }
                                riddleSol = tempStr;

                                if (riddleSol == riddles[x - 1][1])
                                {
                                    cout << endl;
                                    cout << "You answered correctly, but the merchant was neutral. " << endl;
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "You answered incorrectly, but it wouldn't have mattered anyway, the merchant was neutral" << endl;
                                }
                            }
                            if (merchantChance == 3) // if merchant is good
                            {
                                cout << endl;
                                cout << "\"" << riddles[x - 1][0] << "\"" << endl;
                                cin.ignore();
                                getline(cin, riddleSol);

                                for (int i = 0; i < riddleSol.length(); i++)
                                {
                                    tempChar = tolower(riddleSol[i]);
                                    tempStr.push_back(tempChar);
                                }
                                riddleSol = tempStr;

                                if (riddleSol == riddles[x - 1][1])
                                {
                                    cout << endl;
                                    cout << "That is correct! Since you are correct, I will sell to you..." << endl;
                                    merchantMenu(player, dungeon, array);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "Incorrect! You are not worthy of my services..." << endl;
                                }
                            }
                        }
                        cout << endl;
                        cout << "Everyone's fullness levels dropped by one point!" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            array[i].setFullness(array[i].getFullness() - 1);
                            if (array[i].getFullness() == 0)
                            {
                                cout << array[i].getName() << " died, their fullness levels dropped to zero!" << endl;
                                array[i].setCauseOfDeath("Starved");
                                array[i].setArmor(false);
                                array[i].setStatus(false);
                                array[i].setWeapon("");
                                swapDeadMembers(player, dungeon, array, i);
                            }
                        }
                        dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                    break;
                    case 2:
                        srand(time(NULL));
                        x = rand() % 10 + 1;
                        cout << endl;
                        cout << "searching the room...";
                        if (x <= 2) // if found a key
                        {
                            if (dungeon.getKeyAt(dungeon.getRoom() - 1) == false) // if player doesn't have the key
                            {
                                cout << "you came across the key to get out of ";
                                if (dungeon.getRoom() == 1)
                                {
                                    cout << "Room 1!" << endl;
                                    dungeon.setKeyAt(0, true);
                                }
                                if (dungeon.getRoom() == 2)
                                {
                                    cout << "Room 2!" << endl;
                                    dungeon.setKeyAt(1, true);
                                }
                                if (dungeon.getRoom() == 3)
                                {
                                    cout << "Room 3" << endl;
                                    dungeon.setKeyAt(2, true);
                                }
                                if (dungeon.getRoom() == 4)
                                {
                                    cout << "Room 4" << endl;
                                    dungeon.setKeyAt(3, true);
                                }
                                if (dungeon.getRoom() == 5)
                                {
                                    cout << "Room 5" << endl;
                                    dungeon.setKeyAt(4, true);
                                }
                            }
                            else // if player has the key, find gold instead
                            {
                                cout << "you found " << dungeon.getTreasureAt(dungeon.getRoom() - 1, 3) << "!" << endl;
                                if (dungeon.getRoom() == 1)
                                {  
                                    player.setGold(player.getGold() + 50);
                                }
                                if (dungeon.getRoom() == 2)
                                {  
                                    player.setGold(player.getGold() + 100);
                                }
                                if (dungeon.getRoom() == 3)
                                {  
                                    player.setGold(player.getGold() + 500);
                                }
                                if (dungeon.getRoom() == 4)
                                {  
                                    player.setGold(player.getGold() + 1000);
                                }
                                if (dungeon.getRoom() == 5)
                                {  
                                    player.setGold(player.getGold() + 5000);
                                }
                            }
                        }
                        else if (x <= 4) //random treasure yay
                        {
                            cout << endl;
                            cout << "you have found ";
                            srand(time(NULL));
                            x = rand() % 3 + 1;
                            if (x == 1)
                            {
                                if (player.getTreasureFoundAt(dungeon.getRoom() - 1, x - 1) == false) // if havent found treasure
                                {
                                    cout << "a " << dungeon.getTreasureAt(dungeon.getRoom() - 1, x - 1) << "!" << endl;
                                    player.setTreasureFoundAt(dungeon.getRoom() - 1, x - 1, true);
                                }
                                else
                                {
                                    cout << dungeon.getTreasureAt(dungeon.getRoom() - 1, 3) << "!" << endl;
                                    if (dungeon.getRoom() == 1)
                                    {  
                                        player.setGold(player.getGold() + 50);
                                    }
                                    if (dungeon.getRoom() == 2)
                                    {  
                                        player.setGold(player.getGold() + 100);
                                    }
                                    if (dungeon.getRoom() == 3)
                                    {  
                                        player.setGold(player.getGold() + 500);
                                    }
                                    if (dungeon.getRoom() == 4)
                                    {  
                                        player.setGold(player.getGold() + 1000);
                                    }
                                    if (dungeon.getRoom() == 5)
                                    {  
                                        player.setGold(player.getGold() + 5000);
                                    }
                                }
                               
                            }
                            if (x == 2)
                            {
                                if (player.getTreasureFoundAt(dungeon.getRoom() - 1, x - 1) == false) // if havent found that treasure
                                {
                                    cout << "a(n) " << dungeon.getTreasureAt(dungeon.getRoom() - 1, x - 1) << "!" << endl;
                                    player.setTreasureFoundAt(dungeon.getRoom() - 1, x - 1, true);
                                }
                                else
                                {
                                    cout << dungeon.getTreasureAt(dungeon.getRoom() - 1, 3) << "!" << endl;
                                    if (dungeon.getRoom() == 1)
                                    {  
                                        player.setGold(player.getGold() + 50);
                                    }
                                    if (dungeon.getRoom() == 2)
                                    {  
                                        player.setGold(player.getGold() + 100);
                                    }
                                    if (dungeon.getRoom() == 3)
                                    {  
                                        player.setGold(player.getGold() + 500);
                                    }
                                    if (dungeon.getRoom() == 4)
                                    {  
                                        player.setGold(player.getGold() + 1000);
                                    }
                                    if (dungeon.getRoom() == 5)
                                    {  
                                        player.setGold(player.getGold() + 5000);
                                    }
                                }
                            }
                            if (x == 3)
                            {
                                cout << dungeon.getTreasureAt(dungeon.getRoom() - 1, 3) << "!" << endl;
                                if (dungeon.getRoom() == 1)
                                {  
                                    player.setGold(player.getGold() + 50);
                                }
                                if (dungeon.getRoom() == 2)
                                {  
                                    player.setGold(player.getGold() + 100);
                                }
                                if (dungeon.getRoom() == 3)
                                {  
                                    player.setGold(player.getGold() + 500);
                                }
                                if (dungeon.getRoom() == 4)
                                {  
                                    player.setGold(player.getGold() + 1000);
                                }
                                if (dungeon.getRoom() == 5)
                                {  
                                    player.setGold(player.getGold() + 5000);
                                }
                            }
                        }
                        else if(x <= 6) //monster!
                        {
                            monster = getRandomMonster(dungeon.getRoom());
                            cout << endl;
                            cout << "you unfortunatley come across " << monster << "!" << endl;
                            do
                            {
                                cout << "Will you attack (1) or surrender a party member to the " << monster << " (2)?" << endl;
                                cin >> monsterChoice;
                                if (monsterChoice == 1)
                                {
                                    cout << endl;
                                    cout << "You work up the courage and attack " << monster << "!" << endl;
                                    monsterWin = getMonsterWinner(player, dungeon, array);
                                    if (monsterWin == true)
                                    {
                                        srand(time(NULL));
                                        x = rand() % 3 + 1;
                                        cout << endl;
                                        cout << "After a vicious fight, you defeated the monster!" << endl;
                                        cout << "The " << monster << " dropped 10 gold and 5 kilograms of ingredients!" << endl;
                                        player.setIngredients(player.getIngredients() + 20);
                                        player.setGold(player.getGold() + 50);
                                        if (x == 1)
                                        {

                                            cout << "It looks like the " << monster << " dropped the key to get out of ";
                                            if (dungeon.getRoom() == 1)
                                            {
                                                dungeon.setKeyAt(1, true);
                                                cout << "Room 1!" << endl;
                                            }
                                            if (dungeon.getRoom() == 2)
                                            {
                                                dungeon.setKeyAt(2, true);
                                                cout << "Room 2!" << endl;
                                            }
                                            if (dungeon.getRoom() == 3)
                                            {
                                                dungeon.setKeyAt(3, true);
                                                cout << "Room 3" << endl;
                                            }
                                            if (dungeon.getRoom() == 4)
                                            {
                                                dungeon.setKeyAt(4, true);
                                                cout << "Room 4" << endl;
                                            }
                                            if (dungeon.getRoom() == 5)
                                            {
                                                dungeon.setKeyAt(5, true);
                                                cout << "Room 5" << endl;
                                            }
                                        }

                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "The " << monster << " was too tough to defeat, but you escaped" << endl;
                                        for (int i = 1; i < 5; i++)
                                        {
                                            if (array[i].getStatus() == true)
                                            {
                                                srand(time(NULL));
                                                x = rand() % 100 + 1;
                                                if (array[i].getArmor() == true)
                                                {
                                                    if (x <= 5)
                                                    {
                                                        array[x].setStatus(false);
                                                        array[x].setCauseOfDeath(monster);
                                                        array[x].setArmor(false);
                                                        array[x].setWeapon("");
                                                        player.setActiveMembers(array);
                                                        cout << array[i].getName() << " was bruttally killed by " << monster << "!" << endl;
                                                        swapDeadMembers(player, dungeon, array, i);
                                                    }
                                                }
                                                else
                                                {
                                                    if (x <= 10)
                                                    {
                                                        array[x].setStatus(false);
                                                        array[x].setCauseOfDeath(monster);
                                                        array[x].setArmor(false);
                                                        array[x].setWeapon("");
                                                        player.setActiveMembers(array);
                                                        cout << array[i].getName() << " was brutally killed by " << monster << "!" << endl;
                                                        swapDeadMembers(player, dungeon, array, i);
                                                    }
                                                }
                                            }
                                        }
                                        cout << "You lost ";
                                        if (player.getIngredients() < 30)
                                        {
                                            cout << player.getIngredients();
                                            player.setIngredients(0);
                                        }
                                        else
                                        {
                                            cout << 30;
                                            player.setIngredients(player.getIngredients() - 30);
                                        }

                                        cout << " kilograms of ingredients and " << player.getGold() * 0.25 << " gold!" << endl;
                                    }
                                }
                                else if (monsterChoice == 2)
                                {
                                    player.setActiveMembers(array);
                                    srand(time(NULL));
                                    x = rand() % (player.getActiveMembers(array) - 1) + 1;
                                    cout << endl;
                                    cout << "You escaped the " << monster << ", while it was finishing off " << array[x].getName() << endl;
                                    array[x].setStatus(false);
                                    array[x].setCauseOfDeath(monster);
                                    array[x].setArmor(false);
                                    array[x].setWeapon("");
                                    player.setActiveMembers(array);
                                    swapDeadMembers(player, dungeon, array, x);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "Invalid input, try again." << endl;
                                }
                            } while (monsterChoice != 1 && monsterChoice != 2);
                        }
                        else
                        {
                            cout << "Unfortunatley you were not able to find anything." << endl;
                        }
                        cout << endl;
                        cout << "Everyone's fullness levels dropped by one point!" << endl;
                        for (int i = 0; i < player.getActiveMembers(array); i++)
                        {
                            array[i].setFullness(array[i].getFullness() - 1);
                            if (array[i].getFullness() == 0)
                            {
                                cout << array[i].getName() << " died, their fullness levels dropped to zero!" << endl;
                                array[i].setCauseOfDeath("Starved");
                                array[i].setArmor(false);
                                array[i].setStatus(false);
                                array[i].setWeapon("");
                                swapDeadMembers(player, dungeon, array, i);
                                player.setActiveMembers(array);
                            }
                        }
                        dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                    break;
                  case 3: // if user chooses to fight a monster
                        monster = getRandomMonster(dungeon.getRoom()); // get a random monster from the room
                        cout << endl;
                        cout << "A(n) " << monster << " appeared! " << endl;
                        do
                        {
                            cout << "Will you attack (1) or surrender a party member to the " << monster << " (2)?" << endl;
                            cin >> monsterChoice;
                            if (monsterChoice == 1) // if choose attack
                            {
                                cout << endl;
                                cout << "You work up the courage and attack " << monster << "!" << endl;
                                monsterWin = getMonsterWinner(player, dungeon, array);
                                if (monsterWin == true) // if party wins against the monster
                                {
                                    srand(time(NULL));
                                    x = rand() % 3 + 1; // random number to check if monster drops a key
                                    cout << endl;
                                    cout << "After a viscous fight, you emerged victorious!" << endl;
                                    cout << "The " << monster << " dropped 10 gold and 5 kilograms of ingredients!" << endl;
                                    player.setIngredients(player.getIngredients() + 20);
                                    player.setGold(player.getGold() + 50);
                                    if (x == 1 && dungeon.getKeyAt(1) == false) // if y = 1 and theres not a key, get key for room that player is in
                                    {

                                        cout << "Look! " << monster << " dropped the key to get out of ";
                                        if (dungeon.getRoom() == 1)
                                        {
                                            dungeon.setKeyAt(0, true);
                                            cout << "Room 1!" << endl;
                                        }
                                        if (dungeon.getRoom() == 2)
                                        {
                                            dungeon.setKeyAt(1, true);
                                            cout << "Room 2!" << endl;
                                        }
                                        if (dungeon.getRoom() == 3)
                                        {
                                            dungeon.setKeyAt(2, true);
                                            cout << "Room 3!" << endl;
                                        }
                                        if (dungeon.getRoom() == 4)
                                        {
                                            dungeon.setKeyAt(3, true);
                                            cout << "Room 4!" << endl;
                                        }
                                        if (dungeon.getRoom() == 5)
                                        {
                                            dungeon.setKeyAt(4, true);
                                            cout << "Room 5!" << endl;
                                        }
                                    }

                                   
                                }
                                else // if you lose the battle with the monster
                                {
                                    cout << endl;
                                    cout << "The " << monster << " was able to fend off your attack, but you were able to esacpe alive" << endl;
                                    for (int i = 1; i < 5; i++) // use a for loop to get individual chances for each people to die, with armor reducing the chances
                                    {
                                        if (array[i].getStatus() == true)
                                        {
                                            srand(time(NULL));
                                            x = rand() % 100 + 1;
                                            if (array[i].getArmor() == true)
                                            {
                                                if (x <= 5) // 5% chance of party member with armor dying
                                                {
                                                    array[x].setStatus(false);
                                                    array[x].setCauseOfDeath(monster);
                                                    array[x].setArmor(false);
                                                    array[x].setWeapon("");
                                                    player.setActiveMembers(array);
                                                    cout << array[i].getName() << " was brutally killed by " << monster << "!" << endl;
                                                    swapDeadMembers(player, dungeon, array, i);
                                                }
                                            }
                                            else
                                            {
                                                if (x <= 10) // 10% chance of dying w/o aromor
                                                {
                                                    array[x].setStatus(false);
                                                    array[x].setCauseOfDeath(monster);
                                                    array[x].setArmor(false);
                                                    array[x].setWeapon("");
                                                    player.setActiveMembers(array);
                                                    cout << array[i].getName() << " was brutally killed by " << monster << "!" << endl;
                                                    swapDeadMembers(player, dungeon, array, i);
                                                }
                                            }
                                        }
                                    }
                                    cout << "You lost! ";
                                    if (player.getIngredients() < 30)
                                    {
                                        cout << player.getIngredients();
                                        player.setIngredients(0);
                                    }
                                    else
                                    {
                                        cout << 30;
                                        player.setIngredients(player.getIngredients() - 30);
                                    }

                                    cout << " kilograms of ingredients and " << player.getGold() * 0.25 << " gold." << endl;
                                }
                                cout << endl;
                                cout << "Everyone's fullness levels dropped by one point!" << endl;
                                for (int i = 0; i < player.getActiveMembers(array); i++)
                                {
                                    array[i].setFullness(array[i].getFullness() - 1);
                                    if (array[i].getFullness() == 0)
                                    {
                                        cout << array[i].getName() << " has died! Their fullness levels dropped to zero!" << endl;
                                        array[i].setCauseOfDeath("Starved");
                                        array[i].setArmor(false);
                                        array[i].setStatus(false);
                                        array[i].setWeapon("");
                                        swapDeadMembers(player, dungeon, array, i);
                                        player.setActiveMembers(array);
                                    }
                                }
                                dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                            }
                            else if (monsterChoice == 2) // if surrender...
                            {
                                player.setActiveMembers(array);
                                srand(time(NULL));
                                x = rand() % (player.getActiveMembers(array) - 1) + 1; //random number to see who dies
                                cout << endl;
                                cout << "You escape from the " << monster << ", while it finished off " << array[x].getName() << endl;
                                array[x].setStatus(false);
                                array[x].setCauseOfDeath(monster);
                                array[x].setArmor(false);
                                array[x].setWeapon("");
                                player.setActiveMembers(array);
                                swapDeadMembers(player, dungeon, array, x);
                                cout << endl;
                                cout << "Everyone's fullness levels have dropped by one point!" << endl;
                                for (int i = 0; i < player.getActiveMembers(array); i++)
                                {
                                    array[i].setFullness(array[i].getFullness() - 1);
                                    if (array[i].getFullness() == 0)
                                    {
                                        cout << array[i].getName() << " died because their fullness levels dropped to zero!" << endl;
                                        array[i].setCauseOfDeath("Starved");
                                        array[i].setArmor(false);
                                        array[i].setStatus(false);
                                        array[i].setWeapon("");
                                        swapDeadMembers(player, dungeon, array, i);
                                        player.setActiveMembers(array);
                                    }
                                }
                                dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                            }
                            else // if input is invalid
                            {
                                cout << endl;
                                cout << "Invalid input... try again!" << endl;
                            }
                        } while (monsterChoice != 1 && monsterChoice != 2);
                    break;
                       case 4:
                        player.setActiveMembers(array);
                        if (player.getCookwareAt(0) == 0 && player.getCookwareAt(1) == 0 && player.getCookwareAt(2) == 0) //if no cookware
                        {
                            cout << endl;
                            cout << "It looks like you don't have any available cookware to use!" << endl;
                        }
                        else if (player.getIngredients() == 0) //if no ingredients
                        {
                            cout << endl;
                            cout << "It looks like you don't have any available ingredients to use!" << endl;
                        }
                        else
                        {
                            cout << endl;
                            cout << "To increase your party's fullness by 1 point, you need 5 kg of ingredients." << endl;
                            cout << "You have " << player.getActiveMembers(array) << " currently, so you will need to use at least " << player.getActiveMembers(array) * 5 << " kilograms of ingredients to cook a meal that will increase fullness" << endl;
                            do
                            {
                                cout << endl;
                                cout << "Which cookware would you like to use to prepare the meal for your party?" << endl;
                                cout << "You have " << player.getCookwareAt(0) << " ceramic pot(s) (1), " << player.getCookwareAt(1) << " frying pan(s) (2), and " << player.getCookwareAt(2) << " cauldrons (3). (Press 0 to return to menu)." << endl;
                                cin >> cookwareChoice;
                                if (cookwareChoice == 0)
                                {
                                    cout << endl;
                                    cout << "Returning to menu..." << endl;
                                }
                                else if (cookwareChoice == 1)
                                {
                                    if (player.getCookwareAt(0) == 0)
                                    {
                                        cout << endl;
                                        cout << "It looks like you don't have any ceramic pots available to use! Try another type of cookware?" << endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "How many kilograms of ingredients would you like to use?" << endl;
                                        cin >> ingredientChoice;
                                        if (ingredientChoice > player.getIngredients())
                                        {
                                            cout << endl;
                                            cout << "You don't have " << ingredientChoice << " kilograms of ingredients!" << endl;
                                        }
                                        else
                                        {
                                            if (5 * player.getActiveMembers(array) > ingredientChoice)
                                            {
                                                cout << endl;
                                                cout << "You didn't use enough ingredients to restore any fullness points" << endl;
                                                player.setIngredients(player.getIngredients() - ingredientChoice);
                                                cout << "You have " << player.getIngredients() << " kilograms of ingredients left!" << endl;
                                                dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                                            }
                                            else
                                            {
                                                srand(time(NULL));
                                                x = rand() % 4 + 1;
                                                if (x == 1)
                                                {
                                                    cout << endl;
                                                    cout << "Oh no! Your ceramic pot broke before you finished preparing the meal! " << ingredientChoice << " kilograms of ingredients were lost along with your ceramic pot!" << endl;
                                                    player.setIngredients(player.getIngredients() - ingredientChoice);
                                                    player.setCookwareAt(player.getCookwareAt(0) - 1, 0);
                                                }
                                                else
                                                {
                                                    cout << endl;
                                                    cout << "You used " << ingredientChoice << " kilograms of ingredients, and restored each party member's fullness by: ";

                                                    if (array[0].getFullness() + (ingredientChoice / player.getActiveMembers(array)) / 5 >= 10)
                                                    {
                                                        cout << 10 - array[0].getFullness() << "points." << endl;
                                                        for (int i = 0; i < player.getActiveMembers(array); i++)
                                                        {
                                                            array[i].setFullness(10);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << (ingredientChoice / player.getActiveMembers(array)) / 5 << "points." << endl;
                                                        for (int i = 0; i < player.getActiveMembers(array); i++)
                                                        {
                                                            array[i].setFullness(array[i].getFullness() + (ingredientChoice / player.getActiveMembers(array)) / 5 );
                                                        }
                                                    }
                                                    player.setIngredients(player.getIngredients() - ingredientChoice);
                                                }
                                            }
                                        }
                                    }
                                    dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                                }
                                else if (cookwareChoice == 2)
                                {
                                    if (player.getCookwareAt(1) == 0)
                                    {
                                        cout << endl;
                                        cout << "You do not have any frying pans available to use! Try another type of cookware?" << endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "How many kilograms of ingredients would you like to use?" << endl;
                                        cin >> ingredientChoice;
                                        if (ingredientChoice > player.getIngredients()) //if not enough ingredients
                                        {
                                            cout << endl;
                                            cout << "You don't have " << ingredientChoice << " kilograms of ingredients!" << endl;
                                        }
                                        else
                                        {
                                            if (5 * player.getActiveMembers(array) > ingredientChoice) //if not enough ingredients to restore fullness
                                            {
                                                cout << endl;
                                                cout << "You didn't use enough ingredients to restore any fullness points" << endl;
                                                player.setIngredients(player.getIngredients() - ingredientChoice);
                                                cout << "You have " << player.getIngredients() << " kilograms of ingredients left." << endl;
                                            }
                                            else
                                            {
                                                srand(time(NULL));
                                                x = rand() % 10 + 1;
                                                if (x == 1)
                                                {
                                                    cout << endl;
                                                    cout << "Your frying pan broke before you finished preparing the meal! " << ingredientChoice << " kilograms of ingredients were lost as well as your frying pan!" << endl;
                                                    player.setIngredients(player.getIngredients() - ingredientChoice);
                                                    player.setCookwareAt(player.getCookwareAt(1) - 1, 1);
                                                }
                                                else
                                                {
                                                    cout << endl;
                                                    cout << "You used " << ingredientChoice << " kilograms of ingredients, and restored each party member's fullness by: ";
                                                    if ((ingredientChoice / player.getActiveMembers(array)) / 5 > 10)
                                                    {
                                                        cout << 10 - array[0].getFullness() << "points." << endl;
                                                        for (int i = 0; i < player.getActiveMembers(array); i++)
                                                        {
                                                            array[i].setFullness(10);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << (ingredientChoice / player.getActiveMembers(array)) << "points." << endl;
                                                    }
                                                    player.setIngredients(player.getIngredients() - ingredientChoice);
                                                }
                                            }
                                        }
                                    }
                                    dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                                }
                                else if (cookwareChoice == 3)
                                {
                                     if (player.getCookwareAt(2) == 0)
                                    {
                                        cout << endl;
                                        cout << "You don't have any cauldrons available to use! Try another type of cookware?" << endl;
                                    }
                                    else
                                    {
                                        cout << endl;
                                        cout << "How many kilograms of ingredients would you like to use?" << endl;
                                        cin >> ingredientChoice;
                                        if (ingredientChoice > player.getIngredients())
                                        {
                                            cout << endl;
                                            cout << "You don't have " << ingredientChoice << " kilograms of ingredients!" << endl;
                                        }
                                        else
                                        {
                                            if (5 * player.getActiveMembers(array) > ingredientChoice)
                                            {
                                                cout << endl;
                                                cout << "You didn't use enough ingredients to restore any fullness points" << endl;
                                                player.setIngredients(player.getIngredients() - ingredientChoice);
                                                cout << "You have " << player.getIngredients() << " kilograms of ingredients left!" << endl;
                                            }
                                            else
                                            {
                                                srand(time(NULL));
                                                x = rand() % 100 + 1;
                                                if (x <= 2)
                                                {
                                                    cout << endl;
                                                    cout << "Your cauldron broke before you finished preparing the meal! " << ingredientChoice << " kilograms of ingredients were as well as your cauldron!" << endl;
                                                    player.setIngredients(player.getIngredients() - ingredientChoice);
                                                    player.setCookwareAt(player.getCookwareAt(2) - 1, 2);
                                                }
                                                else
                                                {
                                                    cout << endl;
                                                    cout << "You used " << ingredientChoice << " kilograms of ingredients, and restored each party member's fullness by: ";
                                                    if ((ingredientChoice / player.getActiveMembers(array)) / 5 > 10)
                                                    {
                                                        cout << 10 - array[0].getFullness() << "points." << endl;
                                                        for (int i = 0; i < player.getActiveMembers(array); i++)
                                                        {
                                                            array[i].setFullness(10);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << (ingredientChoice / player.getActiveMembers(array)) << "points." << endl;
                                                    }
                                                    player.setIngredients(player.getIngredients() - ingredientChoice);
                                                }
                                            }
                                        }
                                    }
                                    dungeon.setSorcererAnger(dungeon.getSorcererAnger() + 2);
                                }
                                else
                                {
                                    cout << endl;
                                    cout << "Invalid input, try again!" << endl;
                                }
                            } while (cookwareChoice != 1 && cookwareChoice != 2 && cookwareChoice != 3);
                        }  
                    break;
                   
                }
            }
            player.setActiveMembers(array);

            if (dungeon.getSorcererAnger() >= 100 || player.getActiveMembers(array) == 0 || action == 0)
            {
                displayFinalStats(player, dungeon, array, false);
            }
            else
            {
                displayFinalStats(player, dungeon, array, true);
            }
        }
        else if (ready == 'n' || ready == 'N') //display final stats at end of game
        {
            displayFinalStats(player, dungeon, array, false);
        }
        else
        {
            cout << "Invalid input. Try again..." << endl;
            cout << endl;
        }
    } while (ready != 'N' && ready != 'n' && ready != 'Y' && ready != 'y'); //stops game...
   
    return 0;
}