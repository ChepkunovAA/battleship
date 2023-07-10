#include "Ships.hpp"
#include <utility>

bool operator==(const Point& first, const Point& second) {
  return first.x == second.x && first.y == second.y;
}

bool isBetween (const Point& first, const Point& second, const Point& checked) {
  bool check_vertical = !(first.x <= checked.x) ^ (checked.x <= second.x);
  bool check_horizontal = !(first.y <= checked.y) ^ (checked.y<= second.y);
  return check_vertical && check_horizontal;
}


MultideckShip::MultideckShip(const Point& head, const Point& tail): head(head), tail(tail) {
  lives = tail.x - head.x + tail.y - head.y + 1;
}

bool MultideckShip::isLive() {
  return lives > 0;
}

bool MultideckShip::checkShot(const Point& target) {
  if (isBetween(head, tail, target)) {
    --lives;
    return true;
  }
  return false;
}

std::pair<Point&, Point&> MultideckShip::getPoints() { return {head, tail}; }

SingledeckShip::SingledeckShip(const Point& position) : position(position) {
  is_live = true;
}

bool SingledeckShip::isLive() { return is_live; }

bool SingledeckShip::checkShot(const Point& target) {
  if (target == position) {
    is_live = false;
    return true;
  }
  return false;
}

std::pair<Point&, Point&> SingledeckShip::getPoints() { return {position, position};}

MultideckShipCreator::MultideckShipCreator(const Point& head, const Point& tail) : head(head), tail(tail) {}
Ship* MultideckShipCreator::factoryMethod() {
  return new MultideckShip(head, tail);
}

MultideckShipCreator::MultideckShipCreator(const MultideckShipCreator& other) : head(other.head),  tail(other.tail) {}

SingledeckShipCreator::SingledeckShipCreator(const Point& position) : position(position) {}

Ship* SingledeckShipCreator::factoryMethod() {
  return new SingledeckShip(position);
}

SingledeckShipCreator::SingledeckShipCreator(const SingledeckShipCreator& other) : position(other.position) {}
