#include "App.hpp"
#include <fstream>

App::App(Interface& interface) : interface(interface) {
  std::ifstream fin("data.txt");
  if (fin.is_open()) {
    size_t number;
    fin >> number;
    logins.reserve(number);
    for (size_t i = 0; i < number; ++i) {
      Player new_player;
      fin >> new_player.login >> new_player.password >> new_player.wins >> new_player.games;
      logins.push_back(new_player.login);
      data[new_player.login] = new_player;
    }
  }
}
  
void App::Execute() {
  Commands command;
  while (command != Commands::exit) {
    command = interface.RequestCommand();
    switch(command) {
      case Commands::new_game:
        Play();
        break;
      case Commands::check_in:
        Registrate();
        break;
      case Commands::rate:
        interface.ShowRate(GetRate());
        break;
      case Commands::uncorrect:
        interface.UncorrectRequestNotice();
    }
  }
}
  
App::~App() {
  std::ofstream fout("data.txt");
  fout << logins.size() << '\n';
  for (size_t i = 0; i < logins.size(); ++i) {
    Player& player = data[logins[i]];
    fout << player.login << ' ' << player.password << ' ' << player.wins << ' ' << player.games << '\n';
  }
}

std::vector<Player> App::GetRate() {
  std::vector<Player> rate;
  rate.reserve(data.size());
  for (size_t i = 0; i < logins.size(); ++i) {
    rate.push_back(data[logins[i]]);
  }
  std::sort(rate.begin(), rate.end(), ComparePlayers);
  return rate;
}

void App::Play() {
  Player* first;
  Player* second;
  first = Login();
  do {
    second = Login();
  } while (first == second);
  Initializator initializator(interface, first, second);
  Game game;
  PrepareGame(interface, game, initializator, 0);
  PrepareGame(interface, game, initializator, 1);
  Player* winner = Fight(interface, game, initializator);
  (winner->wins)++;
  (first->games)++;
  (second->games)++;
}

void App::Registrate() {
  Player new_player;
  new_player.login = interface.RequestLogin();
  new_player.password = interface.RequestPassword(new_player.login);
  while (isPlayerExist(new_player.login)) {
    interface.UncorrectRequestNotice();
    new_player.login = interface.RequestLogin();
    new_player.password = interface.RequestPassword(new_player.login);
  }
  logins.push_back(new_player.login);
  data[new_player.login] = new_player;
}

Player* App::Login() {
  std::string login, password;
  login = interface.RequestLogin();
  password = interface.RequestPassword(login);
  while (!isPlayerExist(login) || data[login].password != password) {
    interface.UncorrectRequestNotice();
    login = interface.RequestLogin();
    password = interface.RequestPassword(login);
  } 
  return &data[login];
}

bool App::isPlayerExist(std::string login) {
  for (size_t i = 0; i < logins.size(); ++i) {
    if (logins[i] == login) {
      return true;
    }
  }
  return false; 
}