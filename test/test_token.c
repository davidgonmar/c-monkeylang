#include "token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_new_token_from_char() {
  Token *tok = token_new_from_char(ASSIGN, '=');
  TEST_ASSERT_NOT_NULL(tok);
  TEST_ASSERT_EQUAL_INT(ASSIGN, tok->type);
  TEST_ASSERT_EQUAL_STRING("=", tok->literal);
  free(tok);
}

void test_new_token_from_str() {
  Token *tok = token_new_from_str(IDENT, "foobar");
  TEST_ASSERT_NOT_NULL(tok);
  TEST_ASSERT_EQUAL_INT(IDENT, tok->type);
  TEST_ASSERT_EQUAL_STRING("foobar", tok->literal);
  free(tok);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_new_token_from_char);
  RUN_TEST(test_new_token_from_str);
  return UNITY_END();
}