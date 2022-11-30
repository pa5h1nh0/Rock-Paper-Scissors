#include "game.hpp"

int main(void)
{
  auto& game = Game::getInstance();
  game.run(GameMode::human_vs_computer);

  return 0;
}