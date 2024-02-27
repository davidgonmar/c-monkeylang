#pragma once
#include "lexer.h"
#include "token.h"

typedef struct Node {
  int x;
} Node;

typedef enum StatementType { STATEMENT_TYPE_LET } StatementType;

typedef struct Expression {
  Node *node;
} Expression;

typedef struct Identifier {
  Token *token;
  char *value;
} Identifier;

typedef struct LetStatement {
  Token *token;
  Expression *value;
  Identifier *identifier;
} LetStatement;

typedef struct Parser {
  Lexer *lexer;
  Token *currToken;
  Token *peekToken;
} Parser;

Parser *parser_new(Lexer *lexer);

void parser_next_token(Parser *parser);

typedef enum ParserError {
  PARSER_ERROR_EXPECTED_IDENTIFIER,
  PARSER_ERROR_UNKNOWN_STATEMENT
} ParserError;

typedef union StatementData {
  LetStatement letSt;
} StatementData;

typedef struct Statement {
  StatementType type;
  StatementData data;
} Statement;

typedef struct Program {
  Statement **statements;
  size_t n_statements;
} Program;

Program *parser_parse_program(Parser *parser);
