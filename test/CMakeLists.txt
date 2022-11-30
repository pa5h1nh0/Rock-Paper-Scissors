# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(rock_paper_scissorsTests LANGUAGES CXX)

# ---- Tests ----

add_executable(rock_paper_scissors_test source/rock_paper_scissors_test.cpp)
# target_link_libraries(rock_paper_scissors_test PRIVATE game player)

target_include_directories(rock_paper_scissors_test ${warning_guard} PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source>"
)

target_compile_options(rock_paper_scissors_test PRIVATE
    -Wno-conversion
    -Wno-sign-conversion
)

target_compile_features(rock_paper_scissors_test PRIVATE cxx_std_20)

add_test(NAME rock_paper_scissors_test COMMAND rock_paper_scissors_test)

# ---- End-of-file commands ----

add_folders(Test)
