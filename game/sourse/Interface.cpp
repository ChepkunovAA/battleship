#include "Interface.hpp"
#include <iostream>
#include <limits>

void ConsoleInterface::ShowField(std::vector<std::vector<char>> presentation, bool is_owner) {
  is_owner ? std::cout << "Ваше поле:\n" : std::cout << "Поле соперника:\n";
  if (!is_owner) {
    for(unsigned int i = 0; i < presentation.size(); ++i) {
      for(unsigned int j = 0; j < presentation[i].size(); ++j) {
        if (presentation[i][j] != '*' && presentation[i][j] != '#') {
          presentation[i][j] = '?';
        }
      }
    }
  }
  std::cout << "%  ";
  for(unsigned int i = 0; i < presentation.size(); ++i) {
    std::cout << i + 1 << ' ';
  }
  std::cout << '\n';
  for(unsigned int i = 0; i < presentation.size(); ++i) {
    std::cout << i + 1;
    if (i != 9) {
      std::cout << ' ';
    }
    for(unsigned int j = 0; j < presentation[i].size(); ++j) {
      std::cout << ' ' << presentation[i][j];
    }
    std::cout << '\n';
  }
}

std::string ConsoleInterface::RequestLogin() {
  std::cout << "\033[2J\033[1;1H";
  std::string input;
  std::cout << "Введите логин:\n";
  std::cin >> input;
  return input;
}

std::string ConsoleInterface::RequestPassword(std::string player) {
  std::string input;
  std::cout << player << ", введите пароль:\n";
  std::cin >> input;
  std::cout << "\033[2J\033[1;1H";
  return input;
}

Commands ConsoleInterface::RequestCommand() {
  std::cout << "\033[2J\033[1;1H";
  std::cout << "Добро пожаловать на борт! Что прикажете?\n";
  std::cout << "1. Новая игра\n";
  std::cout << "2. Зарегистрироваться\n";
  std::cout << "3. Посмотреть рейтинг\n";
  std::cout << "4. Выйти\n";
  std::cout << "Введите номер желаемого действия:\n";
  int x;
  std::cin >> x;
  if (x < 1 || x > 4) {
    x = 5;
  }
  return static_cast<Commands>(x - 1);
}

void ConsoleInterface::ShowResult(Result result) {
  if (result == Result::miss) {
    std::cout << "Мимо!\n";
  }
  if (result == Result::shot) {
    std::cout << "Ранил!\n";
  }
  if (result == Result::murder) {
    std::cout << "Убил!\n";
  }
  std::cin.get(); std::cin.get();
  std::cout << "\033[2J\033[1;1H";
}

Point ConsoleInterface::SetTarget() {
  Point target;
  std::cout << "Введите координаты цели:\n";
  std::cin >> target.x >> target.y;
  --target.x;
  --target.y;
  return target;
}

void ConsoleInterface::DeclareWinner(int winner) {
  std::cout << "Победил игрок " << winner << '\n';
  std::cin.get();
}

MultideckShipCreator ConsoleInterface::RequestMultideckShip(int ship_count, int ship_size) {
  Point head;
  char direct;
  std::cout << "Введите координаты начала " << ship_count <<
  "-го вашего корабля размера " << ship_size << ", сначала по вертикальной, потом по горизонтальной оси, и его направление (V - vertical, H - horizontal)\n";
  std::cin >> head.x >> head.y >> direct;
  --head.x;
  --head.y;
  Point tail = head;
  if (direct == 'V') {
    tail.x += ship_size - 1;
  } else if (direct == 'H') {
    tail.y += ship_size - 1;
  } else {
    return MultideckShipCreator({-1, -1}, {-1, -1});
  }
  MultideckShipCreator creator(head, tail);
  std::cout << "\033[2J\033[1;1H";
  return creator;
}

SingledeckShipCreator ConsoleInterface::RequestSingledeckShip(int ship_count) {
  Point head;
  std::cout << "Введите координаты вашего " << ship_count <<
    "-го корабля размера 1, сначала по вертикальной, потом по горизонтальной оси\n";
  std::cin >> head.x >> head.y;
  --head.x;
  --head.y;
  SingledeckShipCreator creator(head);
  std::cout << "\033[2J\033[1;1H";
  return creator;
}

void ConsoleInterface::UncorrectRequestNotice() {
  std::cout << "Ввод некорректен! Нажмите Enter чтобы продолжить\n";
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
  std::cout << "\033[2J\033[1;1H";
}

void ConsoleInterface::ShowRate(std::vector<Player> players) {
  std::cout << "\033[2J\033[1;1H";
  std::cout << "Текущий рейтинг:\n";
  size_t i = 0;
  for (; i < std::min(kRateLength, players.size()); ++i) {
    std::cout << i + 1 << ". " << players[i].login << ". winrate - " << players[i].wins << "/" << players[i].games << "\n";
  }
  for (; i < kRateLength; ++i) {
    std::cout << i + 1 << ". None\n";
  }
  std::cin.get(); std::cin.get();
}
