#ifndef PUZZLE_H
#define PUZZLE_H
#include <iostream>
#include <string>
using namespace std;

class Puzzle
{
    

    private:
        string riddle;
        string solution;
        
    public:
        Puzzle();
        Puzzle(string r, string s, int i);

        void setSolution(string s);
        string getSolution();

        void setRiddle(string r);
        string getRiddle();
};

#endif