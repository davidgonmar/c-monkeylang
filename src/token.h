#pragma once

typedef enum TokenType {
  ILLEGAL,
  EOF,
  IDENT,
  INT,
  ASSIGN,
  PLUS,
  COMMA,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  FUNCTION,
  LET
} TokenType;

typedef struct Token {
  TokenType type;
  char *literal;
} Token;
