#pragma once

#include <algorithm>
#include <cctype>
#include <string_view>

enum class GameMode : uint8_t
{
  human_vs_computer,
  computer_vs_computer
};

enum class RoundOutcome : uint8_t
{
  win,
  lose,
  draw
};

enum class HandShape : uint8_t
{
  rock,
  paper,
  scissors,

  invalid
};

[[nodiscard]] static inline const char* ModeToString(const GameMode mode)
{
  switch (mode) {
    case GameMode::human_vs_computer:
      return "human vs computer";

    case GameMode::computer_vs_computer:
      return "computer vs computer";

    default:
      return "unknown";
  }
}

[[nodiscard]] static inline const char* HandShapeToString(const HandShape hand)
{
  switch (hand) {
    case HandShape::rock:
      return "rock";

    case HandShape::paper:
      return "paper";

    case HandShape::scissors:
      return "scissors";

    default:
      return "invalid";
  }
}

[[nodiscard]] static inline HandShape CharToHandShape(const char hand_ch)
{
  switch (std::toupper(hand_ch)) {
    case 'R':
      return HandShape::rock;

    case 'P':
      return HandShape::paper;

    case 'S':
      return HandShape::scissors;

    default:
      return HandShape::invalid;
  }
}

namespace utils
{

// returns true if both strings are equal in a case insensitive way
[[nodiscard]] static inline constexpr bool striequals(
    const std::string_view str1, const std::string_view str2)
{
  return ((str1.size() == str2.size())
          && std::ranges::equal(
              str1,
              str2,
              [](const char ch1, const char ch2) {
                return (ch1 == ch2) || (std::toupper(ch1) == std::toupper(ch2));
              }));
}

}  // namespace utils