#include "ast.h"
#include "lexer.h"
#include "token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_parser_new() {
  char *input = "let x = 5;\n"
                "let y = 10;\n"
                "let foobar = 838383;\n";
  Lexer *lex = lexer_new(input);
  Parser *par = parser_new(lex);
  TEST_ASSERT_NOT_NULL(par);
  TEST_ASSERT_EQUAL(par->currToken->type, LET);
  TEST_ASSERT_EQUAL_STRING(par->currToken->literal, "let");
  TEST_ASSERT_EQUAL(par->peekToken->type, IDENT);
  TEST_ASSERT_EQUAL_STRING(par->peekToken->literal, "x");
}
void test_let() {
  char *input = "let x = 5;\n"
                "let y = 10;\n"
                "let foobar = 838383;\n";
  char *idents[] = {"x", "y", "foobar"};
  Lexer *lex = lexer_new(input);
  TEST_ASSERT_NOT_NULL(lex);
  Parser *par = parser_new(lex);
  TEST_ASSERT_NOT_NULL(par);

  Program *prog = parser_parse_program(par);
  TEST_ASSERT_NOT_NULL(prog);
  TEST_ASSERT_EQUAL_INT(3, prog->n_statements);

  for (int i = 0; i < 3; i++) {
    Statement *st = prog->statements[i];
    TEST_ASSERT_EQUAL_INT(STATEMENT_TYPE_LET, st->type);
    TEST_ASSERT_EQUAL_INT(LET, st->data.letSt.token->type);
    TEST_ASSERT_EQUAL_STRING(st->data.letSt.token->literal, "let");
    TEST_ASSERT_EQUAL_INT(IDENT, st->data.letSt.identifier->token->type);
    TEST_ASSERT_EQUAL_STRING(idents[i],
                             st->data.letSt.identifier->token->literal);
    TEST_ASSERT_EQUAL_STRING(idents[i], st->data.letSt.identifier->value);
    TEST_ASSERT_NOT_NULL(st->data.letSt.value);
  }
}

void test_return() {
  char *input = "return 5;\n"
                "return 10;\n"
                "return 838383;\n";
  Lexer *lex = lexer_new(input);
  TEST_ASSERT_NOT_NULL(lex);
  Parser *par = parser_new(lex);
  TEST_ASSERT_NOT_NULL(par);

  Program *prog = parser_parse_program(par);
  TEST_ASSERT_NOT_NULL(prog);
  TEST_ASSERT_EQUAL_INT(3, prog->n_statements);

  for (int i = 0; i < 3; i++) {
    Statement *st = prog->statements[i];
    TEST_ASSERT_EQUAL_INT(STATEMENT_TYPE_RETURN, st->type);
    TEST_ASSERT_EQUAL_INT(RETURN, st->data.returnSt.token->type);
    TEST_ASSERT_EQUAL_STRING(st->data.returnSt.token->literal, "return");
    TEST_ASSERT_NOT_NULL(st->data.returnSt.retVal);
  }
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_parser_new);
  RUN_TEST(test_let);
  RUN_TEST(test_return);
  return UNITY_END();
}