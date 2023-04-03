#include "Party.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

 void deadMembers(Party player, Room room, Player array[], int index){
     int alive=0;
     int dead=0;
     Player aliveArr[player.getActiveMembers(array)];
     Player deadArr[5];
     Player tempPlayer=array[index];

     for (int i = 0; i < 5; i++)
     {   
         if (array[i].getName() != "")
            {
             aliveArr[alive] = array[i];
             alive++;
         }
         else
         {
             deadArr[dead] = array[i];
             dead++;
         }
     }
     dead=0;

     for (int i = 0; i < player.getActiveMembers(array); i++)
     {
         array[i] = aliveArr[i];
     }
     for (int i = player.getActiveMembers(array); i < 5; i++)
     {
         array[i] = deadArr[dead];
     }
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