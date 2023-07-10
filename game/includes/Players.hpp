#include <string>

struct Player {
  std::string login;
  std::string password;
  int wins = 0;
  int games = 0;
};

bool ComparePlayers(const Player& first, const Player& second);