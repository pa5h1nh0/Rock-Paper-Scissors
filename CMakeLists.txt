cmake_minimum_required(VERSION 3.10)

include(cmake/prelude.cmake)

project(
    rock_paper_scissors
    VERSION 0.1.0
    DESCRIPTION "A rock paper scissors command line game"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    game OBJECT
    source/game.cpp
)

add_library(
    player OBJECT
    source/player.cpp
)

target_include_directories(
    game ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/third-party>"
)

target_include_directories(
    player ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/third-party>"
)

target_compile_features(game PUBLIC cxx_std_20)
target_compile_features(player PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(rock_paper_scissors_exe source/main.cpp)
add_executable(rock_paper_scissors::exe ALIAS rock_paper_scissors_exe)

target_include_directories(
  rock_paper_scissors_exe ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source/third-party>"
)

set_property(TARGET rock_paper_scissors_exe PROPERTY OUTPUT_NAME rock_paper_scissors)

target_compile_features(rock_paper_scissors_exe PRIVATE cxx_std_20)

target_link_libraries(rock_paper_scissors_exe PRIVATE
  game
  player
)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT rock_paper_scissors_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of rock_paper_scissors"
  )
endif()

include(cmake/dev-mode.cmake)
