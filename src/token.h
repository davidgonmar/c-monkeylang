#pragma once

typedef enum TokenType {
  ILLEGAL,
  TEOF,
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
  LET,
  BANG,
  MINUS,
  SLASH,
  ASTERISK,
  LT,
  GT,
  TRUE,
  FALSE,
  IF,
  ELSE,
  RETURN,
  EQ,
  NEQ
} TokenType;

typedef struct Token {
  TokenType type;
  char *literal;
} Token;

Token *token_new_from_char(TokenType type, const char literal);
Token *token_new_from_str(TokenType type, const char *literal);

char *token_type_to_str(TokenType type);

char *token_to_str(Token *tok);