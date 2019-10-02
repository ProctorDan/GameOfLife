#include "Map.h"
#include "GameModes.h"
#include "GameFunctions.h"
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

    GameFunctions *gameFunc = new GameFunctions();

    if (inp == "1")
    {
        gameFunc->setRandom(true);
    }
    else
    {
        gameFunc->setRandom(false);
    }

    gameFunc->chooseMode();

    delete gameFunc;
    return 0;
}