#include "lexer.h"
#include "token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unity.h>

#define N_TOKENS 8
void setUp() {}
void tearDown() {}

void test_new_lexer() {
  const char input[N_TOKENS] = "=+(){},;";
  Lexer *lexer = lexer_new(input);
  TEST_ASSERT_NOT_NULL(lexer);
  TEST_ASSERT_EQUAL_INT(-1, lexer->current_pos);
  TEST_ASSERT_EQUAL_INT(0, lexer->read_pos);
  TEST_ASSERT_EQUAL_INT(-1, lexer->ch);
  TEST_ASSERT_EQUAL_STRING(lexer->input, input);
  free(lexer);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_new_lexer);
  return UNITY_END();
}