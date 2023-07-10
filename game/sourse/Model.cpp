#include "Model.hpp"
#include <string>
#include <vector>
#include <iostream>

Field::Field() {
  presentation.resize(kLength);
  for (int i = 0; i < kLength; ++i) {
    presentation[i].resize(kLength, '.');
  }
}

bool Field::checkPoint(const Point& point) {
  return (point.x >= 0 && point.x < kLength && point.y >= 0 && point.y < kLength);
} 

bool Field::checkShip(const Point& head, const Point& tail) {
  if (!checkPoint(head) || !checkPoint(tail)) {
    return false;
  }
  for (int x = std::max(0, head.x - 1); x <= std::min(kLength - 1, tail.x + 1); ++x) {
    for (int y = std::max(0, head.y - 1); y <= std::min(kLength - 1, tail.y + 1); ++y) {
      if (presentation[x][y] == '$') {
        return false;
      }
    }
  }
  return true;
}

Result Field::checkShot(const Point& target) {
    if (!checkPoint(target) || presentation[target.x][target.y] == '*' || presentation[target.x][target.y] == '#') {
      return Result::uncorrect;
    }
    for (unsigned int i = 0; i < ships.size(); ++i) {
      if (ships[i]->checkShot(target)) {
        presentation[target.x][target.y] = '#';
        if (ships[i]->isLive()) {
          return Result::shot;
        } else {
          std::pair<Point&, Point&> position = ships[i]->getPoints();
          for (int x = std::max(0, position.first.x - 1); x <= std::min(kLength - 1, position.second.x + 1); ++x) {
            for (int y = std::max(0, position.first.y - 1); y <= std::min(kLength - 1, position.second.y + 1); ++y) {
              if (presentation[x][y] != '#') {
                presentation[x][y] = '*';
              }
            }
          }
          delete ships[i];
          ships.erase(ships.begin() + i);
          return Result::murder;
        }
      }
    }
    presentation[target.x][target.y] = '*';
    return Result::miss;
 }

bool Field::isLose() { return ships.empty(); }

bool Field::addShip(Creator& creator) {
  Ship* new_ship = creator.factoryMethod();
  Point& head = new_ship->getPoints().first;
  Point& tail = new_ship->getPoints().second;
  if (!checkShip(head, tail)) {
    return false;
  }
  ships.push_back(new_ship);
  for (int x = head.x; x <= tail.x; ++x) {
    for (int y = head.y; y <= tail.y; ++y) {
      presentation[x][y] = '$';
    }
  }
  return true;
}

std::vector<std::vector<char>>& Field::getPresentation() { return presentation; }

Field::~Field() {
  for (unsigned int i = 0; i < ships.size(); ++i) {
      delete ships[i];
  }
}

Result Game::checkShot(const Point& target) {
  Result result = fields[1 - current_player].checkShot(target);
  if (fields[1 - current_player].isLose()) {
    winner = current_player;
  }
  return result;
}

bool Game::addShip(Creator& creator) {
  return fields[current_player].addShip(creator);
}

std::vector<std::vector<char>>& Game::getPresentation(int player) {
  return fields[player].getPresentation();
}

void Game::setPlayer(int player) {
  current_player = player;
}

int Game::getWinner() { return winner; }