#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>
#include <sstream>

using namespace std;

int main (int argc, char **argv)
{
    
    string inp;
    
    while (inp != "1" && inp!= "2")
    {
        cout << "Welcome to GAME OF LIFE!" << endl;
        cout << "Enter 1 or 2 to choose configuration." << endl;
        cout << "1. Choose the dimensions with a random configuration" << endl;
        cout << "2. Enter the file path" << endl; 
        cin >> inp;

        if (inp != "1" && inp != "2")
        {
            cout << endl << "Bro I said 1 or 2... " << inp << " wasn't an option! Try again." << endl;
            cout << endl;
        }

    }    

    Map *m = new Map();
    if (inp == "1")
    {
        m->setRandom(true);
    }
    else
    {
        m->setRandom(false);
    }

    char** map = m->getMap();
    m->chooseMode();

    delete m;
    return 0;
    
}