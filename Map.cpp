#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <time.h>
#include <sstream>
#include <unistd.h>

using namespace std;

Map::Map()
{

} 

Map::~Map()
{
    delete currentMap;
    delete newMap;
}

void Map::setRandom(bool randy)
{

    if(randy)
    {
        buildRandomMap();
    }
    else
    {
        cout << "oy" << endl;
    }

    setPrint();
}

void Map::setPrint()
{
    bool method = false;

    while(!method)
    {
        cout << "Choose the method in which you would like to print each generational map." << endl;
        cout << "Available print methods: \"pause\", \"enter\", \"file\"" << endl;
        cout << "Pause holds program for 1 second. Enter waits until you press enter. File outputs everything to a file." << endl;
    
        cin >> pMethod;
        transform(pMethod.begin(), pMethod.end(), pMethod.begin(), ::tolower);
        if(pMethod == "pause")
        {
            method = true;
        }
        else if(pMethod == "enter")
        {
            method = true;
        }
        else if(pMethod == "file")
        {
            method = true;
        }
        else
        {
            method = false;
            cout << "Sorry yo that wasn't an option... try again!" << endl;
            system("pause");
            cout << endl;
        }
    }
}

int Map::getHeight()
{
    return height;
}

int Map::getLength()
{
    return length;
}

float Map::getDensity()
{
    return density;
}

char** Map::getMap()
{
    return currentMap;
}

void Map::printMap()
{
    if (pMethod == "pause")
    {
        for(int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < length; ++j) 
            {
                cout << currentMap[i][j];
            }
            cout << endl;
        }
        sleep(1);
    }
    else if (pMethod == "enter")
    {
        for(int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < length; ++j) 
            {
                cout << currentMap[i][j];
            }
            cout << endl;
        }
        system("pause");
        cout << endl;
    }
    else if (pMethod == "file")
    {
        for(int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < length; ++j) 
            {
                cout << currentMap[i][j];
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Something went wrong outputting file..." << endl;
    }
    

}

void Map::buildRandomMap()
{
    bool l = false;
    bool h = false;
    bool dens = false;

    while(!h)
    {
        cout << "Please enter a height for the map" << endl; 
        cin >> height;

        if(cin.fail())
        {
            cout << "That was not an integer." << endl;
            cin.clear();
            cin.ignore(256,'\n');
        }

        else
        {
            h = true;
        }
    }
        
    while(!l)
    {
        cout << "Please enter a length for the map" << endl; 
        cin >> length;

        if(cin.fail())
        {
            cout << "That was not an integer." << endl;
            cin.clear();
            cin.ignore(256,'\n');
        }

        else
        {
            l = true;
        }
    }

    while(!dens)
    {
        cout << "Please enter a density between 0 and 1 for the map" << endl; 
        cin >> density;

        if(cin.fail())
        {
            cout << "That was not a float." << endl;
            cin.clear();
            cin.ignore(256,'\n');
        }

        else if ((density >= 0.0) && (density <= 1.0))
        {
            dens = true;
        }

        else
        {
            cout << "That was not between 0 and 1... c'mon it's not that hard" << endl;
        }

    }
    // creates the same new map and current map to start
    currentMap = new char*[height];
    for (int i = 0; i < height; ++i)
    {
        currentMap[i] = new char[length];
    }
    newMap = new char*[height];
    for (int i = 0; i < height; ++i)
    {
        newMap[i] = new char[length];
    }    

    for (int j = 0; j < height; ++j)
    {
      for (int f = 0; f < length; ++f)
      {
          currentMap[j][f] = '-';
          newMap[j][f] = '-';
      }
    }

    int totalCells = height * length;
    float numX = round(totalCells * density);
    srand(time(NULL));
    int randH = 0;
    int randL = 0;
    int xCount = 0;

    while(xCount != numX)
    {
        randH = rand() % (height);
        randL = rand() % (length);

        if (currentMap[randH][randL] == '-')
        {
            currentMap[randH][randL] = 'X';
            newMap[randH][randL] = 'X';
            xCount++;
        } 
    } 
}

bool Map::checkStable()
{
    for (int i = 0; i < height; ++i)
    {
       	for (int j = 0; j < length; ++j) 
        {
	       	if (currentMap[i][j] == newMap[i][j]) 
            {
	       		continue;
	        }
           	else 
            {
           		return false;
         	}
       	}
    }

    cout << "The world is stable." << endl;
    return true;  
}

void Map::classicMode()
{
    cout << "Welcome to classic mode!" << endl;
    sleep(1);
    generation = 1;
    bool check = false;

    while(!check)
    {

    }
    
}
