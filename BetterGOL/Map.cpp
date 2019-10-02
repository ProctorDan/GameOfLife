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

Map::Map()
{
    height = 5;
    length = 5;
    density = .5;
} 

Map::~Map()
{
    delete currentMap;
    delete newMap;
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

char** Map::getCurrentMap()
{
    return currentMap;
}

char** Map::getNewMap()
{
    return newMap;
}


void Map::setEmptyMaps()
{
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
}

void Map::buildFileMap()
{
    fstream mapStream;
    string filePath;
    bool foundFile = false;
    cout << "Type the file path to input." << endl;
    while (!foundFile)
    {
        cin >> filePath;
        mapStream.open(filePath);
        if (mapStream.fail())
        {
            cout << "That file does not exist." << endl;
            cout << "Please enter another file path." << endl;
            continue;
        }
        else
        {
            cout << "File inputted." << endl;
            foundFile = true;
        }
    }

    string line;
    int lineCount = -2;

    while(getline(mapStream, line))
    {
        if (lineCount == -2)
        {
            stringstream dimensions(line);
            dimensions >> height;
            lineCount++;
            continue;
        }
        else if (lineCount == -1)
        {
            stringstream dimensions(line);
            dimensions >> length;
            lineCount++;
            continue;
        }

        else if (lineCount == 0)
        {
            setEmptyMaps();
        }

        for(int ch = 0; ch < line.length(); ++ch)
        {
            currentMap[lineCount][ch] = line[ch];
            newMap[lineCount][ch] = line[ch];
        }
        lineCount++;
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
    setEmptyMaps();    

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
