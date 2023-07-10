#ifndef SHIPS_H_INCLUDED
#define SHIPS_H_INCLUDED

#include <utility>

struct Point {
  int x;
  int y;
  Point& operator=(const Point& other) = default;
};

bool operator==(const Point& first, const Point& second);

bool isBetween (const Point& first, const Point& second, const Point& checked);

class Ship {
 public:
  virtual bool isLive() = 0;

  virtual bool checkShot(const Point& target) = 0;

  virtual std::pair<Point&, Point&> getPoints() = 0;

  virtual ~Ship() = default; 
};

class MultideckShip : public Ship {
 public:
  MultideckShip(const Point& head, const Point& tail);

  bool isLive() override;

  bool checkShot(const Point& target) override;

  std::pair<Point&, Point&> getPoints() override;

 private:
  Point head;
  Point tail;
  int lives;
};

class SingledeckShip : public Ship {
 public:
  SingledeckShip(const Point& position);

  bool isLive() override;

  bool checkShot(const Point& target) override;

  std::pair<Point&, Point&> getPoints() override;

 private:
  bool is_live = true;
  Point position;
};

struct Creator{
  virtual Ship* factoryMethod() = 0;
};

struct MultideckShipCreator: Creator{
  MultideckShipCreator(const Point& head, const Point& tail);
  const Point head, tail;
  Ship* factoryMethod();
  
  MultideckShipCreator(const MultideckShipCreator& other);
};

struct SingledeckShipCreator: Creator{
  SingledeckShipCreator(const Point& position);
  const Point position;
  Ship* factoryMethod();

  SingledeckShipCreator(const SingledeckShipCreator& other);
};

#endif // MODEL_H_INCLUDED
