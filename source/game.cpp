#include <iostream>

#include "game.hpp"

#include "boost/unordered_map.hpp"

void Game::setPlayersNames(const bool p1_is_human,
                           const std::string_view human_player_name,
                           std::string& p1_name,
                           std::string& p2_name)
{
  static constexpr auto computer_player_name = "Computer";

  p1_name = human_player_name;
  p2_name = computer_player_name;

  if (p1_is_human) {  // <valid human player name> vs "Computer"
    if (p1_name.empty() || utils::striequals(p1_name, computer_player_name)) {
      printf(
          "Cannot play with an empty human player name or with the name '%s', "
          "using default '%s'!\n",
          computer_player_name,
          default_human_name);

      p1_name = default_human_name;
    }
  } else {  // "Computer-1" vs "Computer-2"
    using namespace std::string_literals;
    p1_name = computer_player_name + "-1"s;
    p2_name += "-2";
  }

  assert(!p1_name.empty() && !p2_name.empty());
}

void Game::run(const GameMode mode, const std::string_view human_player_name)
{
  if (started) {
    printf("Game already started!\n");
    return;
  }

  const bool player1_is_human {mode == GameMode::human_vs_computer};
  std::string player1_name {}, player2_name {};
  setPlayersNames(
      player1_is_human, human_player_name, player1_name, player2_name);

  // create players
  Player player1(player1_name, player1_is_human), player2(player2_name);

  started = true;
  printf("Game started [mode: %s, player 1: %s, player 2: %s]\n\n",
         ModeToString(mode),
         player1_name.c_str(),
         player2_name.c_str());

  // lambda helper returning the player1's round outcome
  const auto play_round = [&player1, &player2](HandShape& hand1,
                                               HandShape& hand2) -> RoundOutcome
  {
    static constexpr auto rock_u8 = static_cast<uint8_t>(HandShape::rock);
    static constexpr auto paper_u8 = static_cast<uint8_t>(HandShape::paper);
    static constexpr auto scissors_u8 =
        static_cast<uint8_t>(HandShape::scissors);

    // statically build an "outcomes" map from player1's perspective
    static const boost::unordered_map<std::tuple<uint8_t, uint8_t>,
                                      RoundOutcome>
        all_p1_outcomes_map {{{rock_u8, rock_u8}, RoundOutcome::draw},
                             {{paper_u8, paper_u8}, RoundOutcome::draw},
                             {{scissors_u8, scissors_u8}, RoundOutcome::draw},
                             {{rock_u8, scissors_u8}, RoundOutcome::win},
                             {{rock_u8, paper_u8}, RoundOutcome::lose},
                             {{scissors_u8, paper_u8}, RoundOutcome::win},
                             {{scissors_u8, rock_u8}, RoundOutcome::lose},
                             {{paper_u8, rock_u8}, RoundOutcome::win},
                             {{paper_u8, scissors_u8}, RoundOutcome::lose}};

    // get each player's hand
    hand1 = player1.playHand();
    hand2 = player2.playHand();

    // return immediately in case of a draw
    if (hand1 == hand2)
      return RoundOutcome::draw;

    // otherwise perform a lookup in the outcomes map
    const auto hands_played = std::make_tuple(static_cast<uint8_t>(hand1),
                                              static_cast<uint8_t>(hand2));
    assert(all_p1_outcomes_map.contains(hands_played));
    return all_p1_outcomes_map.at(hands_played);
  };

  bool quit {};
  uint32_t num_rounds {};

  do {
    auto hand1 = HandShape::invalid;
    auto hand2 = HandShape::invalid;

    // play a round
    const auto player1_outcome = play_round(hand1, hand2);
    printf("%s plays '%s'\n", player1.name.c_str(), HandShapeToString(hand1));
    printf("%s plays '%s'\n", player2.name.c_str(), HandShapeToString(hand2));

    switch (player1_outcome) {
      case RoundOutcome::win: {
        printf("Outcome: %s wins!\n\n", player1.name.c_str());

        player1.numWins++;
        player2.numLost++;
      } break;

      case RoundOutcome::lose: {
        printf("Outcome: %s wins!\n\n", player2.name.c_str());

        player2.numWins++;
        player1.numLost++;
      } break;

      default: {
        assert(player1_outcome == RoundOutcome::draw);
        printf("Outcome: draw!\n\n");

        player1.numDraws++;
        player2.numDraws++;
      } break;
    }

    printf("Press [Q/q] to quit, anything else to play another round..");
    std::string line {};
    std::getline(std::cin, line);
    const char q {(line.empty() ? char {} : line[0])};

    num_rounds++;
    quit = (std::toupper(q) == 'Q');
    printf("\n");
  } while (!quit);

  started = false;

  const auto p1_rounds = player1.numWins + player1.numLost + player1.numDraws;
  const auto p2_rounds = player2.numWins + player2.numLost + player2.numDraws;
  assert((num_rounds == p1_rounds) && (num_rounds == p2_rounds)
         && (player1.numDraws == player2.numDraws));

  printf("Total rounds played: %u\n", num_rounds);
  printf("Draws: %u\n", player1.numDraws);
  printf("%s wins: %u\n", player1.name.c_str(), player1.numWins);
  printf("%s wins: %u\n", player2.name.c_str(), player2.numWins);
}