#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <algorithm>


class Map
{
    
    public:

      void setEmptyMaps();

      int height;
      int length;
      float density;
      char **newMap;
      char **currentMap;

      Map();
      ~Map();

      char** getCurrentMap();
      char** getNewMap();
      int getHeight();
      int getLength();
      float getDensity();

      void buildRandomMap();
      void buildFileMap();
};

#endif