#ifndef GAMEUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>
#include <string>

class GameFunctions
{
    public:
      GameFunctions();
      ~GameFunctions();
      

      void chooseMode();
      void setRandom(bool randy);

      std::string getOut();

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