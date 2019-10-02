#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <iostream>
#include <string>
#include <algorithm>


class GameModes
{
    public:
      GameModes();
      ~GameModes();
      
      void copyMap();
      void printMap();
      void alter(char top, char bottom, char left, char right, char tl, char tr, char bl, char br, int row, int col);
      bool checkStable();
      void setPrint();

      void classicMode();
      void mirrorMode();
      void donutMode();

      int height;
      int length;
      float density;
      std::string pMethod;
      char **newMap;
      char **currentMap;
      int generation;
      std::string filePath;
      std::string outFile;
};

#endif