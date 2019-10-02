#include "GameModes.h"
#include "GameFunctions.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>
#include <sstream>
#include <unistd.h>
#include <limits>


using namespace std;

GameFunctions::GameFunctions()
{

} 

GameFunctions::~GameFunctions()
{

}


void GameFunctions::setRandom(bool randy)
{

    if(randy)
    {
        Map().buildRandomMap();
    }
    else
    {
        Map().buildFileMap();
    }

    height = Map().getHeight();
    length = Map().getLength();
    density = Map().getDensity();

    GameModes().setPrint();
}



void GameFunctions::chooseMode()
{
    cout << "Choose a game mode to play" << endl;
    cout << "Modes: \"classic\", \"mirror\", \"donut\"." << endl;
    string choose;
    bool mode = false;
    while(!mode)
    {
        cin >> choose;
        transform(choose.begin(), choose.end(), choose.begin(), ::tolower);
        if (choose == "classic")
        {
            mode = true;
            GameModes().classicMode();
        }
        else if (choose == "mirror")
        {
            mode = true;
            GameModes().mirrorMode();
        }
        else if (choose == "donut")
        {
            mode = true;
            GameModes().donutMode();
        }
        else
        {
            cout << "Sorry that wasn't a game mode. Try again." << endl;
        }
    }
}




string GameFunctions::getOut()
{
    return outFile;
}

