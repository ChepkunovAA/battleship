#include "Game.hpp"
#include <algorithm>
#include <unordered_map>

class App {
 public:
  App(Interface& interface);
  
  void Execute();
  
  ~App();
 private:
  std::vector<Player> GetRate();

  void Play();

  void Registrate();

  Player* Login();

  bool isPlayerExist(std::string login);

  std::vector<std::string> logins;
  std::unordered_map<std::string, Player> data;
  Interface& interface;
};