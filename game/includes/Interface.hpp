#include "Model.hpp"
#include "Players.hpp"

enum class Commands {new_game, check_in, rate, exit, uncorrect};

class Interface {
 public:
  virtual void ShowField(std::vector<std::vector<char>> field, bool is_owner) = 0;

  virtual std::string RequestPassword(std::string player) = 0;

  virtual std::string RequestLogin() = 0;

  virtual Commands RequestCommand() = 0;

  virtual void ShowResult(Result result) = 0;

  virtual Point SetTarget() = 0;

  virtual void DeclareWinner(int winner) = 0;

  virtual MultideckShipCreator RequestMultideckShip(int ship_count, int ship_size) = 0;

  virtual SingledeckShipCreator RequestSingledeckShip(int ship_count) = 0;

  virtual void UncorrectRequestNotice() = 0;
  
  virtual void ShowRate(std::vector<Player> players) = 0;

  virtual ~Interface() = default;
};

const size_t kRateLength = 10;

class ConsoleInterface : public Interface {
 public:

  void ShowField(std::vector<std::vector<char>> field, bool is_owner) override;

  std::string RequestPassword(std::string player) override;

  std::string RequestLogin() override;

  Commands RequestCommand() override;

  void ShowResult(Result result) override;

  Point SetTarget() override;

  void DeclareWinner(int winner) override;

  MultideckShipCreator RequestMultideckShip(int ship_count, int ship_size) override;

  SingledeckShipCreator RequestSingledeckShip(int ship_count) override;
  
  void UncorrectRequestNotice() override;

  void ShowRate(std::vector<Player> players) override;
};