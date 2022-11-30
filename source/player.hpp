#pragma once

#include <random>
#include <string>
#include <string_view>

#include "common.hpp"

class Game;

class Player
{
public:
  const std::string name;
  const bool isHuman;

  Player(const std::string_view _name, const bool _isHuman = false)
      : name {_name}
      , isHuman {_isHuman}
  {
    // initialize a random hash seed only once at the very beginning
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<uint32_t> dist(1, 1000);
    hash = dist(rng);
  }

  Player() = delete;  // ctor
  ~Player() = default;  // dtor

  Player(const Player&) = delete;  // copy ctor
  Player(Player&&) = delete;  // move ctor
  Player& operator=(const Player&) = delete;  // copy assignment operator
  Player& operator=(Player&&) = delete;  // move assignment operator

  [[nodiscard]] HandShape playHand();

private:
  // some stats
  unsigned numWins {};
  unsigned numDraws {};
  unsigned numLost {};

  uint32_t hash {};

  // only the 'Game' singleton instance is allowed to modify directly the
  // player's stats, as he is the game's only "trusted judge"
  friend class Game;
};