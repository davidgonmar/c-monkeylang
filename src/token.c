#include "token.h"
#include "stdlib.h"
#include "string.h"

static Token *token_new(TokenType type, const char *literal) {
  Token *tok = malloc(sizeof(Token));
  if (tok == NULL)
    return tok;
  char *tok_literal = malloc(strlen(literal) * sizeof(char));
  strcpy(tok_literal, literal);
  tok->literal = tok_literal;
  tok->type = type;
  return tok;
}

Token *token_new_from_char(TokenType type, char literal_char) {
  char str[2] = {literal_char, '\0'};
  return token_new(type, str);
}

Token *token_new_from_str(TokenType type, const char *literal) {
  return token_new(type, literal);
}

char *token_type_to_str(TokenType type) {
  switch (type) {
  case ILLEGAL:
    return "ILLEGAL";
  case TEOF:
    return "TEOF";
  case IDENT:
    return "IDENT";
  case INT:
    return "INT";
  case ASSIGN:
    return "ASSIGN";
  case PLUS:
    return "PLUS";
  case COMMA:
    return "COMMA";
  case SEMICOLON:
    return "SEMICOLON";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case LBRACE:
    return "LBRACE";
  case RBRACE:
    return "RBRACE";
  case FUNCTION:
    return "FUNCTION";
  case LET:
    return "LET";
  default:
    return "UNKNOWN";
  }
}