
#ifndef MISFORTUNES_H
#define MISFORTUNES_H
#include <string>
using namespace std; 

class Misfortunes
{
    

    private:
        string type;
        bool occurrence;
        int likeliness;
    
    public:
        Misfortunes();
        Misfortunes(string t, int l, bool o);

        void setRandomType();
        void setActualType(string t);
        string getActualType();

        void setLikeliness(int l);
        int getLikeliness();
        
        void setRandomOccurrence(int l);
        void setActualOccurrence(bool o);
        bool getOccurrence();
};


#endif
