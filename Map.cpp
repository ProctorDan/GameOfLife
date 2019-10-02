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

Map::Map() // set default values
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

void Map::setRandom(bool randy)
{

    if(randy)
    {
        buildRandomMap();
    }
    else
    {
        buildFileMap();
    }

    setPrint();
}

void Map::setPrint() // sets print methods
{
    bool method = false;

    while(!method)
    {
        cout << endl;
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
            string partOut;
            method = true;
            cout << "\nEnter a name for the output file. The extension '.txt' will automatically be added to the end of the name." << endl;
            cin >> partOut;
            outFile = partOut + ".txt";
        }
        else
        {
            method = false;
            cout << endl << "Sorry yo that wasn't an option... try again!" << endl << endl;
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
        cout << "\nGeneration #" << generation << endl << endl;
        for(int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < length; ++j) 
            {
                cout << currentMap[i][j];
            }
            cout << endl;
        }
        sleep(1); // pauses for 1 second
    }
    else if (pMethod == "enter")
    {
        cout << "\nGeneration #" << generation << endl << endl;
        for(int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < length; ++j) 
            {
                cout << currentMap[i][j];
            }
            cout << endl;
        }
        if (generation == 0) // there is leftover input on the first generation so needed this
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press [enter] to continue..." << endl;
            cin.get();
        }
        else
        {
            cout << "Press [enter] to continue..." << endl;
            cin.get();
        }

    }
    else if (pMethod == "file")
    {
        ofstream mapStream;
        mapStream.open(outFile, ios::app);
        mapStream << "\nGeneration #" << generation << endl << endl;
        for(int i = 0; i < height; ++i) 
        {
            for (int j = 0; j < length; ++j) 
            {
                mapStream << currentMap[i][j];
            }
            mapStream << endl;
        }
    }
    else
    {
        cout << "Something went wrong outputting..." << endl;
    }
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

bool Map::checkStable() // checks if 
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

    if (pMethod == "file")
    {
        ofstream mapStream;
        mapStream.open(outFile, ios::app);
        mapStream << "\nThe world is stable.";
        mapStream.close();
    }
    else
    {
        cout << "The world is stable." << endl;
    }
    
    return true;  
}

void Map::copyMap()
{
    for (int j = 0; j < height; ++j)
    {
        for (int f = 0; f < length; ++f)
        {
          currentMap[j][f] = newMap[j][f];
        }
    }
}

void Map::chooseMode()
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
            classicMode();
        }
        else if (choose == "mirror")
        {
            mode = true;
            mirrorMode();
        }
        else if (choose == "donut")
        {
            mode = true;
            donutMode();
        }
        else
        {
            cout << "Sorry that wasn't a game mode. Try again." << endl;
        }
    }
}

void Map::alter(char top, char bottom, char left, char right, char tl, char tr, char bl, char br, int row, int col) // will alter the new map
{
    int neighborCount = 0;
    if (top == 'X')
    {
        neighborCount++;
    }
    if (bottom == 'X')
    {
        neighborCount++;
    }
    if (left == 'X')
    {
        neighborCount++;
    }
    if (right == 'X')
    {
        neighborCount++;
    }
    if (tl == 'X')
    {
        neighborCount++;
    }
    if (tr == 'X')
    {
        neighborCount++;
    }
    if (bl == 'X')
    {
        neighborCount++;
    }
    if (br == 'X')
    {
        neighborCount++;
    }
    
    if (neighborCount <= 1)
    {
        newMap[row][col] = '-';
    }
    else if (neighborCount == 3)
    {
        newMap[row][col] = 'X';
    }
    else if (neighborCount >= 4)
    {
        newMap[row][col] = '-';
    }
}

void Map::classicMode()
{

    if (pMethod == "file")
    {
        ofstream mapStream;
        mapStream.open(outFile);
        mapStream << "Welcome to classic mode!\n\n";
        mapStream.close();
    }
    else
    {
        cout << endl << "Welcome to classic mode!" << endl << endl;
    }
    
    generation = 0;
    bool check = false;

    while(!check)
    {
        printMap();
        generation++;

        for(int row = 0; row < height; ++row)
        {
            for(int col = 0; col < length; ++col)
            {
                char left;
                char right;
                char top;
                char bottom;
                char tr; // top right
                char tl; // top left
                char br; // bottom right
                char bl; // bottom left

                // Special cases (all side cells)
                if (row == 0 && col == 0) // top left
                {
                    top = '-';
                    tl = '-';
                    tr = '-';
                    left = '-';
                    bl = '-';
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    right = currentMap[row][col+1];
                }
                else if ((row == height - 1) && col == 0) // bottom left
                {
                    bottom = '-';
                    br = '-';
                    bl = '-';
                    left = '-';
                    tl = '-';
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (row == 0 && col == length - 1) // Top right
                {
                    bottom = currentMap[row+1][col];
                    br = '-';
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = '-';
                    top = '-';
                    tr = '-';
                    right = '-';      
                }
                else if ((row == height - 1) && (col == length - 1)) // Bottom right
                {
                    bottom = '-';
                    br = '-';
                    bl = '-';
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = '-';
                    right = '-';
                }
                else if (row == 0) // Top row
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = '-';
                    top = '-';
                    tr = '-';
                    right = currentMap[row][col+1];
                }
                else if (row == height - 1) // Bottom row
                {
                    bottom = '-';
                    br = '-';
                    bl = '-';
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (col == 0) // Left column
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = '-';
                    left = '-';
                    tl = '-';
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];                    
                }
                else if (col == length - 1) // Right column
                {
                    bottom = currentMap[row+1][col];
                    br = '-';
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = '-';
                    right = '-';
                }
                else
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                alter(top, bottom, left, right, tl, tr, bl, br, row, col);
            }
        }
        check = checkStable();
        if (!check)
        {
           copyMap();
        }
    }
}

void Map::mirrorMode()
{

    if (pMethod == "file")
    {
        ofstream mapStream;
        mapStream.open(outFile);
        mapStream << "Welcome to mirror mode!\n\n";
        mapStream.close();
    }
    else
    {
        cout << endl << "Welcome to mirror mode!" << endl << endl;
    }
 
    generation = 0;
    bool check = false;

    while(!check)
    {
        printMap();
        generation++;

        for(int row = 0; row < height; ++row)
        {
            for(int col = 0; col < length; ++col)
            {
                char left;
                char right;
                char top;
                char bottom;
                char tr; // top right
                char tl; // top left
                char br; // bottom right
                char bl; // bottom left

                // Special cases (all side cells)
                if (row == 0 && col == 0) // top left
                {
                    top = currentMap[row][col];
                    tl = currentMap[row][col];
                    tr = currentMap[row][col+1];
                    left = currentMap[row][col];
                    bl = currentMap[row+1][col];
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    right = currentMap[row][col+1];
                }
                else if ((row == height - 1) && col == 0) // bottom left
                {
                    bottom = currentMap[row][col];
                    br = '-';
                    bl = currentMap[row][col];
                    left = currentMap[row][col];
                    tl = '-';
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (row == 0 && col == length - 1) // Top right
                {
                    bottom = currentMap[row+1][col];
                    br = '-';
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = '-';
                    top = currentMap[row][col];
                    tr = currentMap[row][col];
                    right = currentMap[row][col];      
                }
                else if ((row == height - 1) && (col == length - 1)) // Bottom right
                {
                    bottom = '-';
                    br = '-';
                    bl = '-';
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = '-';
                    right = '-';
                }
                else if (row == 0) // Top row
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row][col-1];
                    top = currentMap[row][col];
                    tr = currentMap[row][col+1];
                    right = currentMap[row][col+1];
                }
                else if (row == height - 1) // Bottom row
                {
                    bottom = currentMap[row][col];
                    br = currentMap[row][col+1];
                    bl = currentMap[row][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (col == 0) // Left column
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col];
                    left = currentMap[row][col];
                    tl = currentMap[row-1][col];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];                    
                }
                else if (col == length - 1) // Right column
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col];
                    right = currentMap[row][col];
                }
                else
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                alter(top, bottom, left, right, tl, tr, bl, br, row, col);
            }
        }
        check = checkStable();
        if (!check)
        {
           copyMap();
        }
    }
}

void Map::donutMode()
{
    if (pMethod == "file")
    {
        ofstream mapStream;
        mapStream.open(outFile);
        mapStream << "Welcome to donut mode!\n\n";
        mapStream.close();
    }
    else
    {
        cout << endl << "Welcome to donut mode!" << endl << endl;
    }

    generation = 0;
    bool check = false;

    while(!check)
    {
        printMap();
        generation++;

        for(int row = 0; row < height; ++row)
        {
            for(int col = 0; col < length; ++col)
            {
                char left;
                char right;
                char top;
                char bottom;
                char tr; // top right
                char tl; // top left
                char br; // bottom right
                char bl; // bottom left

                // Special cases (all side cells)
                if (row == 0 && col == 0) // top left
                {
                    top = currentMap[row + height-1][col];
                    tl = currentMap[row + height-1][col + length-1];
                    tr = currentMap[row + height-1][col+1];
                    left = currentMap[row][col + length-1];
                    bl = currentMap[row+1][col + length-1];
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    right = currentMap[row][col+1];
                }
                else if ((row == height - 1) && col == 0) // bottom left
                {
                    bottom = currentMap[row - height+1][col];
                    br = currentMap[row - height+1][col+1];
                    bl = currentMap[row - height+1][col + length-1];
                    left = currentMap[row][col + length-1];
                    tl = currentMap[row-1][col + length-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (row == 0 && col == length - 1) // Top right
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col - length+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row + height-1][col-1];
                    top = currentMap[row + height-1][col];
                    tr = currentMap[row + height-1][col - length+1];
                    right = currentMap[row][col - length+1];      
                }
                else if ((row == height - 1) && (col == length - 1)) // Bottom right
                {
                    bottom = currentMap[row - height+1][col];
                    br = currentMap[row - height+1][col - length+1];
                    bl = currentMap[row - height+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col - length+1];
                    right = currentMap[row][col - length+1];
                }
                else if (row == 0) // Top row
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row + height-1][col-1];
                    top = currentMap[row + height-1][col];
                    tr = currentMap[row + height-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (row == height - 1) // Bottom row
                {
                    bottom = currentMap[row - height+1][col];
                    br = currentMap[row - height+1][col+1];
                    bl = currentMap[row - height+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                else if (col == 0) // Left column
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col + length-1];
                    left = currentMap[row][col + length-1];
                    tl = currentMap[row-1][col + length-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];                    
                }
                else if (col == length - 1) // Right column
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col - length+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col - length+1];
                    right = currentMap[row][col - length+1];
                }
                else
                {
                    bottom = currentMap[row+1][col];
                    br = currentMap[row+1][col+1];
                    bl = currentMap[row+1][col-1];
                    left = currentMap[row][col-1];
                    tl = currentMap[row-1][col-1];
                    top = currentMap[row-1][col];
                    tr = currentMap[row-1][col+1];
                    right = currentMap[row][col+1];
                }
                alter(top, bottom, left, right, tl, tr, bl, br, row, col);
            }
        }
        check = checkStable();
        if (!check)
        {
           copyMap();
        }
    }
}
