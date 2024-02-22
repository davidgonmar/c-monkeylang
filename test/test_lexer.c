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
  TEST_ASSERT_EQUAL_INT(0, lexer->current_pos);
  TEST_ASSERT_EQUAL_INT(1, lexer->read_pos);
  TEST_ASSERT_EQUAL_CHAR(lexer->ch, '=');
  TEST_ASSERT_EQUAL_STRING(lexer->input, input);
  free(lexer);
}

void test_next_token() {
  const char input[N_TOKENS] = "=+(){},;";
  const Token *expected[N_TOKENS] = {
      token_new_from_char(ASSIGN, '='), token_new_from_char(PLUS, '+'),
      token_new_from_char(LPAREN, '('), token_new_from_char(RPAREN, ')'),
      token_new_from_char(LBRACE, '{'), token_new_from_char(RBRACE, '}'),
      token_new_from_char(COMMA, ','),  token_new_from_char(SEMICOLON, ';')};

  Lexer *lexer = lexer_new(input);

  for (int i = 0; i < N_TOKENS; i++) {
    Token *tok = next_token(lexer);
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_INT(expected[i]->type, tok->type);
    TEST_ASSERT_EQUAL_STRING(expected[i]->literal, tok->literal);
  }
}
int main() {
  UNITY_BEGIN();
  RUN_TEST(test_new_lexer);
  RUN_TEST(test_next_token);
  return UNITY_END();
}