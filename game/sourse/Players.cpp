#include "Players.hpp"

bool ComparePlayers(const Player& first, const Player& second) {
  if (first.games * second.games == 0) {
    return first.wins > second.wins;
  }
  return(first.wins / first.games > second.wins / second.games);
}