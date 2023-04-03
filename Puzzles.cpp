
#include "Puzzles.h"
#include <iostream>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

Puzzle::Puzzle()
{
    srand(time(NULL));
    int y = 0;
    y = rand() % 9 + 0;
    string line;
    string spl[2];
    int counter = 0;
    string puz[10][2];
    puz[0][0] = "You measure my life in hours and I serve you by expiring. I'm quick when I'm thin and slow when I'm fat. The wind is my enemy.";
    puz[0][1] = "candle";
    puz[1][0] = "I have cities, but no houses. I have mountains, but no trees. I have water, but no fish. What am I?";
    puz[1][1] = "map";
    puz[2][0] = "What English word has three consecutive double letters?";
    puz[2][1] = "bookkeeper";
    puz[3][0] = "I have keys, but no locks and space, and no rooms. You can enter, but you can't go outside. What am I?";
    puz[3][1] = "keyboard";
    puz[4][0] = "What gets wet while drying?";
    puz[4][1] = "towel";
    puz[5][0] = "First you eat me, then you get eaten. What am I?";
    puz[5][1] = "fishhook";
    puz[6][0] = "Which word in the dictionary is always spelled incorrectly?";
    puz[6][1] = "incorrectly";
    puz[7][0] = "What is able to go up a chimney when down but unable to go down a chimney when up?";
    puz[7][1] = "umbrella";
    puz[8][0] = "What has a head and a tail, but no body or legs?";
    puz[8][1] = "coin";
    puz[9][0] = "I am a solitary word, 5 letters long. Behead me once, I am the same. Behead me again, I am still the same.";
    puz[9][1] = "alone";

    puz[y][0] = riddle;
    puz[y][1] = solution;

    riddle = puz[y][0];
    solution = puz[y][1];
}
Puzzle::Puzzle(string r, string s, int i)
{
    string line;
}
void Puzzle::setSolution(string s)
{
    solution = s;
}
string Puzzle::getSolution()
{
    return solution;
}
void Puzzle::setRiddle(string r)
{
    riddle = r;
}
string Puzzle::getRiddle()
{
    return riddle;
}