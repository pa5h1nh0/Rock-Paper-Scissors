#include "acutest.h"
#include "common.hpp"

// clang-format off
struct
{
  const char* description;
  const char *str1, *str2;
  const bool expected;
} test_data[] = {
  {
    .description = "equal-1",
    .str1 = "stuff",
    .str2 = "stuFF",
    .expected = true
  },
  {
    .description = "not-equal-1",
    .str1 = "stuff",
    .str2 = "staFf",
    .expected = false
  },
  {
    .description = "equal-2",
    .str1 = "stufF",
    .str2 = "STUFf",
    .expected = true
  },
  {
    .description = "not-equal-2",
    .str1 = "stuff",
    .str2 = "stuf",
    .expected = false
  },
  {
    .description = "equal-3",
    .str1 = "stuff",
    .str2 = "stuff",
    .expected = true
  }
};
// clang-format on

void test_striequals(void)
{
  printf("\n");

  for (auto& test_item : test_data) {
    printf("Checking [%s]\n", test_item.description);
    TEST_CASE(test_item.description);

    const auto res = utils::striequals(test_item.str1, test_item.str2);
    TEST_CHECK(res == test_item.expected);

    TEST_MSG("expected: %s", test_item.expected ? "true" : "false");
    TEST_MSG("produced: %s", res ? "true" : "false");
  }
}

TEST_LIST = {
    {"case_insensitive_string_equals", test_striequals},
    {NULL, NULL}  // zeroed record marking the end of the list
};