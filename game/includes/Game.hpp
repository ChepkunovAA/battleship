#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include "Interface.hpp"

struct Initializator {
  Initializator(Interface& interface, Player* first, Player* second);

  void Init (int player);

  Player* players[2];
  Interface& interface;
};

const int kSize = 4;

void PrepareGame(Interface& interface, Game& game, Initializator& initializator, int player);

Player* Fight(Interface& interface, Game& game, Initializator& initializator);

#endif