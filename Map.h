#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <algorithm>


class Map
{
    public:
      Map();
      ~Map();

      char** getMap();
      int getHeight();
      int getLength();
      float getDensity();
      void setRandom(bool randy);
      void setPrint();
      void printMap();
      void buildRandomMap();
      void buildFileMap();
      bool checkStable();
      void classicMode();

      int height;
      int length;
      float density;
      std::string pMethod;
      char **newMap;
      char **currentMap;
      int generation;
};

#endif