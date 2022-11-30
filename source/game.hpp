#pragma once

#include <array>

#include "player.hpp"

class Game
{
private:
  // This is a singleton so constructor, destructor, and assignment operators
  // are private
  Game() = default;  // ctor
  ~Game() = default;  // dtor

  Game(const Game&) = delete;  // copy ctor
  Game(Game&&) = delete;  // move ctor
  Game& operator=(const Game&) = delete;  // copy assignment operator
  Game& operator=(Game&&) = delete;  // move assignment operator

  bool started {};

  static void setPlayersNames(const bool p1_is_human,
                              const std::string_view human_player_name,
                              std::string& p1_name,
                              std::string& p2_name);

public:
  [[nodiscard]] static Game& getInstance()
  {
    static Game obj;
    return obj;
  }

  static inline constexpr auto default_human_name = "Dude";

  // runs the game with a default, if not specified otherwise, human player name
  void run(const GameMode mode,
           const std::string_view human_player_name = default_human_name);
};