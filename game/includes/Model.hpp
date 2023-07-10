#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "Ships.hpp"
#include <string>
#include <vector>

enum class Result { miss, shot, murder, uncorrect};


class Field {
 public:
  Field();

  Result checkShot(const Point& target);

  bool isLose();

  bool addShip(Creator& creator);

  std::vector<std::vector<char>>& getPresentation();

  ~Field();

 private:
  bool checkPoint(const Point& point);
  bool checkShip(const Point& head, const Point& tail);
  const int kLength = 10;
  std::vector<Ship*> ships;
  std::vector<std::vector<char>> presentation;
};

class Game {
 public:
  Result checkShot(const Point& target);

  bool addShip(Creator& creator);

  std::vector<std::vector<char>>& getPresentation(int player);

  void setPlayer(int player);

  int getWinner();

 private:
  int current_player;
  int winner = -1;
  Field fields[2];
};


#endif // MODEL_H_INCLUDED
