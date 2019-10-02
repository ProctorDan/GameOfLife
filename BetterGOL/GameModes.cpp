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

GameModes::GameModes()
{
    height = Map().getHeight();
    length = Map().getLength();
    density = Map().getDensity();

} 

GameModes::~GameModes()
{

}

void GameModes::copyMap()
{
    for (int j = 0; j < height; ++j)
    {
        for (int f = 0; f < length; ++f)
        {
          currentMap[j][f] = newMap[j][f];
        }
    }
}

bool GameModes::checkStable()
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


void GameModes::alter(char top, char bottom, char left, char right, char tl, char tr, char bl, char br, int row, int col)
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

void GameModes::setPrint()
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

void GameModes::printMap()
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
        sleep(1);
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
        if (generation == 0)
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

void GameModes::classicMode()
{
    outFile = GameFunctions().getOut();
    generation = 0;
    height = Map().getHeight();
    length = Map().getLength();
    currentMap = Map().getCurrentMap();
    newMap = Map().getNewMap();

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

void GameModes::mirrorMode()
{
    outFile = GameFunctions().getOut();
    generation = 0;
    height = Map().getHeight();
    length = Map().getLength();
    currentMap = Map().getCurrentMap();
    newMap = Map().getNewMap();

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

void GameModes::donutMode()
{

    outFile = GameFunctions().getOut();
    generation = 0;
    height = Map().getHeight();
    length = Map().getLength();
    currentMap = Map().getCurrentMap();
    newMap = Map().getNewMap();

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