#include <cassert>
#include <iostream>

#include "player.hpp"

#include "xxhash.hpp"

[[nodiscard]] HandShape Player::playHand()
{
  auto hand = HandShape::invalid;

  if (isHuman) {  // get the user's hand
    char hand_ch {};
    bool valid_input {};
    static const std::string inputs_allowed {"RrPpSs"};

    while (!valid_input) {
      hand_ch = 0;

      printf(
          "Enter [R/r] for 'rock', [P/p] for 'paper', [S/s] for 'scissors'\n");
      printf("%s: ", name.c_str());

      std::string line {};
      std::getline(std::cin, line);  // wait for user input
      hand_ch = (line.empty() ? char {} : line[0]);
      printf("\n");

      valid_input =
          (inputs_allowed.find_first_of(hand_ch) != std::string::npos);
    }

    hand = CharToHandShape(hand_ch);
  } else {  // get the computer's hand
    // the assumption here is that of playing against an adversary that behaves
    // mostly in a random unpredictable way, instead of applying complex and
    // advanced algorithms (e.g., via AI techniques and/or scientific research
    // papers) such as those listed here
    // https://en.wikipedia.org/wiki/Rock_paper_scissors#Algorithms

    hash = xxh::xxhash<32>(&hash, sizeof(hash));
    const auto r = hash % static_cast<uint8_t>(HandShape::invalid);

    assert(r < static_cast<uint8_t>(HandShape::invalid));
    hand = static_cast<HandShape>(r);
  }

  // must return only a valid hand!
  assert(hand != HandShape::invalid);
  return hand;
}