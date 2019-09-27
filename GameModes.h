#ifndef GAMEMODES_H
#define GAMEMODES_H

#include <iostream>

class GameModes
{
    public:
      GameModes();
      ~GameModes();

      char** returnMap();

};

class Classic : public GameModes
{
  //  public:
      
};



#endif