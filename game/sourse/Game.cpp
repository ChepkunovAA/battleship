#include "Game.hpp"
#include <iostream>
#include <string>

Initializator::Initializator(Interface& interface, Player* first, Player* second) : interface(interface) {
  players[0] = first;
  players[1] = second;
}

void Initializator::Init(int player) {
  std::string input;
  do {
    input = interface.RequestPassword(players[player]->login);
    if (input != players[player]->password) {
      interface.UncorrectRequestNotice();
    }
  } while (input != players[player]->password);
}


void PrepareGame(Interface& interface, Game& game, Initializator& initializator, int player) {
  initializator.Init(player);
  game.setPlayer(player);
  bool is_correct_request;
  for (int ship_size = kSize; ship_size > 1; --ship_size) {
    for (int ship_count = 0; ship_count <= kSize - ship_size; ++ship_count) {
      do {
        interface.ShowField(game.getPresentation(player), true);
        MultideckShipCreator creator(interface.RequestMultideckShip(ship_count + 1, ship_size));
        is_correct_request = game.addShip(creator);
        if(!is_correct_request) {
          interface.UncorrectRequestNotice();
        }
      } while (!is_correct_request);
    }
  }
  for (int ship_count = 0; ship_count < kSize; ++ship_count) {
    do {
      interface.ShowField(game.getPresentation(player), true);
      SingledeckShipCreator creator(interface.RequestSingledeckShip(ship_count + 1));
      is_correct_request = game.addShip(creator);
      if(!is_correct_request) {
        interface.UncorrectRequestNotice();
      }
    } while (!is_correct_request);
  }
}


Player* Fight(Interface& interface, Game& game, Initializator& initializator) {
  int player = 0;
  while (game.getWinner() < 0) {
    initializator.Init(player);
    game.setPlayer(player);
    Result result;
    do {
      interface.ShowField(game.getPresentation(player), true);
      interface.ShowField(game.getPresentation(1 - player), false);
      Point target = interface.SetTarget();
      result = game.checkShot(target);
      if(result == Result::uncorrect) {
        interface.UncorrectRequestNotice();
      }
    } while (result == Result::uncorrect);
    interface.ShowResult(result);
    if (result == Result::miss) {
      player = 1 - player;
    }
  }
  interface.DeclareWinner(game.getWinner() + 1);
  return initializator.players[game.getWinner()];
}