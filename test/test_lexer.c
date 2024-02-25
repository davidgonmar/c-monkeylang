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

char *build_token_mismatch_message(const Token *expected, const Token *actual) {
  char *message = malloc(sizeof(char) * 200);
  sprintf(message, "Token type mismatch, expected %s, got %s",
          token_type_to_str(expected->type), token_type_to_str(actual->type));
  return message;
}
void test_next_token_advanced() {
  const char *input = "let five = 5;\n"
                      "let ten = 10;\n"
                      "\n"
                      "let add = fn(x, y) {\n"
                      "  x + y;\n"
                      "};\n"
                      "!-/*5;\n"
                      "5 < 10 > 5;\n"
                      "let result = add(five, ten);\n"
                      "if (5 < 10) {\n"
                      "  return true;\n"
                      "} else {\n"
                      "  return false;\n"
                      "}"
                      "10 == 10;\n"
                      "10 != 9;\n";

  Lexer *lexer = lexer_new(input);
  Token *expected_tokens[] = {
      token_new_from_str(LET, "let"),      token_new_from_str(IDENT, "five"),
      token_new_from_char(ASSIGN, '='),    token_new_from_str(INT, "5"),
      token_new_from_char(SEMICOLON, ';'), token_new_from_str(LET, "let"),
      token_new_from_str(IDENT, "ten"),    token_new_from_char(ASSIGN, '='),
      token_new_from_str(INT, "10"),       token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(LET, "let"),      token_new_from_str(IDENT, "add"),
      token_new_from_char(ASSIGN, '='),    token_new_from_str(FUNCTION, "fn"),
      token_new_from_char(LPAREN, '('),    token_new_from_str(IDENT, "x"),
      token_new_from_str(COMMA, ","),      token_new_from_str(IDENT, "y"),
      token_new_from_char(RPAREN, ')'),    token_new_from_char(LBRACE, '{'),
      token_new_from_str(IDENT, "x"),      token_new_from_char(PLUS, '+'),
      token_new_from_str(IDENT, "y"),      token_new_from_char(SEMICOLON, ';'),
      token_new_from_char(RBRACE, '}'),    token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(BANG, "!"),       token_new_from_str(MINUS, "-"),
      token_new_from_str(SLASH, "/"),      token_new_from_str(ASTERISK, "*"),
      token_new_from_str(INT, "5"),        token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(INT, "5"),        token_new_from_str(LT, "<"),
      token_new_from_str(INT, "10"),       token_new_from_str(GT, ">"),
      token_new_from_str(INT, "5"),        token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(LET, "let"),      token_new_from_str(IDENT, "result"),
      token_new_from_char(ASSIGN, '='),    token_new_from_str(IDENT, "add"),
      token_new_from_str(LPAREN, "("),     token_new_from_str(IDENT, "five"),
      token_new_from_str(COMMA, ","),      token_new_from_str(IDENT, "ten"),
      token_new_from_char(RPAREN, ')'),    token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(IF, "if"),        token_new_from_str(LPAREN, "("),
      token_new_from_str(INT, "5"),        token_new_from_str(LT, "<"),
      token_new_from_str(INT, "10"),       token_new_from_str(RPAREN, ")"),
      token_new_from_str(LBRACE, "{"),     token_new_from_str(RETURN, "return"),
      token_new_from_str(TRUE, "true"),    token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(RBRACE, "}"),     token_new_from_str(ELSE, "else"),
      token_new_from_str(LBRACE, "{"),     token_new_from_str(RETURN, "return"),
      token_new_from_str(FALSE, "false"),  token_new_from_char(SEMICOLON, ';'),
      token_new_from_str(RBRACE, "}"),     token_new_from_str(INT, "10"),
      token_new_from_str(EQ, "=="),        token_new_from_str(INT, "10"),
      token_new_from_char(SEMICOLON, ';'), token_new_from_str(INT, "10"),
      token_new_from_str(NEQ, "!="),       token_new_from_str(INT, "9"),
      token_new_from_char(SEMICOLON, ';'), token_new_from_char(TEOF, '\0')};

  for (int i = 0; i < 74; i++) {
    Token *tok = lexer_next_token(lexer);
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        expected_tokens[i]->type, tok->type,
        build_token_mismatch_message(expected_tokens[i], tok));
    TEST_ASSERT_EQUAL_STRING(expected_tokens[i]->literal, tok->literal);
  }
}

void test_next_token() {
  const char input[] = "=+(){},;";
  const Token *expected[] = {
      token_new_from_char(ASSIGN, '='), token_new_from_char(PLUS, '+'),
      token_new_from_char(LPAREN, '('), token_new_from_char(RPAREN, ')'),
      token_new_from_char(LBRACE, '{'), token_new_from_char(RBRACE, '}'),
      token_new_from_char(COMMA, ','),  token_new_from_char(SEMICOLON, ';'),
      token_new_from_char(TEOF, '\0')};

  Lexer *lexer = lexer_new(input);

  for (int i = 0; i < 9; i++) {
    Token *tok = lexer_next_token(lexer);
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_INT_MESSAGE(
        expected[i]->type, tok->type,
        build_token_mismatch_message(expected[i], tok));
    TEST_ASSERT_EQUAL_STRING(expected[i]->literal, tok->literal);
  }
}
int main() {
  UNITY_BEGIN();
  RUN_TEST(test_new_lexer);
  RUN_TEST(test_next_token);
  RUN_TEST(test_next_token_advanced);
  return UNITY_END();
}