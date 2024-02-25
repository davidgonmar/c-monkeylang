#include "lexer.h"
#include "token.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer *lexer_new(const char *input) {
  if (strlen(input) == 0)
    return NULL;
  Lexer *lexer = malloc(sizeof(Lexer));
  if (lexer == NULL)
    return NULL;
  char *lexer_input =
      malloc(sizeof(char) * (strlen(input) + 1)); // + 1 for null termination
  lexer->input = lexer_input;
  lexer->current_pos = -1;
  lexer->read_pos = 0;
  lexer->ch = '\0';
  strcpy(lexer->input, input);
  lexer_read_char(lexer);
  return lexer;
}

void lexer_read_char(Lexer *l) {
  if (l->read_pos >= strlen(l->input)) {
    l->ch = '\0'; // finished reading
  } else {
    l->ch = l->input[l->read_pos];
  }
  l->current_pos = l->read_pos;
  l->read_pos++;
}

TokenType lexer_lookup_ident(const char *ident) {
  if (strcmp(ident, "fn") == 0) {
    return FUNCTION;
  } else if (strcmp(ident, "let") == 0) {
    return LET;
  } else {
    return IDENT;
  }
}

void lexer_skip_whitespace(Lexer *l) {
  while (isspace(l->ch)) {
    lexer_read_char(l);
  }
}

char *lexer_read_identifier(Lexer *l) {
  int start_pos = l->current_pos;
  while (isalpha(l->ch)) {
    lexer_read_char(l);
  }

  size_t size = l->current_pos - start_pos;
  char *c = malloc(sizeof(char) * (size + 1)); // + 1 for null termination
  assert(strlen(l->input) > size);
  memcpy(c, l->input + start_pos, size);
  c[size] = '\0';

  return c;
}

char *lexer_read_number(Lexer *l) {
  int start_pos = l->current_pos;
  while (isdigit(l->ch)) {
    lexer_read_char(l);
  }

  size_t size = l->current_pos - start_pos;
  char *c = malloc(sizeof(char) * (size + 1)); // + 1 for null termination
  assert(strlen(l->input) > size);
  memcpy(c, l->input + start_pos, size);
  c[size] = '\0';

  return c;
}

Token *lexer_next_token(Lexer *l) {
  lexer_skip_whitespace(l);

  Token *tok = NULL;

  switch (l->ch) {
  case '=':
    tok = token_new_from_char(ASSIGN, '=');
    break;
  case ';':
    tok = token_new_from_char(SEMICOLON, ';');
    break;
  case '(':
    tok = token_new_from_char(LPAREN, '(');
    break;
  case ')':
    tok = token_new_from_char(RPAREN, ')');
    break;
  case ',':
    tok = token_new_from_char(COMMA, ',');
    break;
  case '+':
    tok = token_new_from_char(PLUS, '+');
    break;
  case '{':
    tok = token_new_from_char(LBRACE, '{');
    break;
  case '}':
    tok = token_new_from_char(RBRACE, '}');
    break;
  case '-':
    tok = token_new_from_char(MINUS, '-');
    break;
  case '!':
    tok = token_new_from_char(BANG, '!');
    break;
  case '/':
    tok = token_new_from_char(SLASH, '/');
    break;
  case '*':
    tok = token_new_from_char(ASTERISK, '*');
    break;
  case '<':
    tok = token_new_from_char(LT, '<');
    break;
  case '>':
    tok = token_new_from_char(GT, '>');
    break;
  case '\0':
    tok = token_new_from_char(TEOF, '\0');
    break;
  default:
    if (isalpha(l->ch)) {
      char *c = lexer_read_identifier(l);
      TokenType type = lexer_lookup_ident(c);
      tok = token_new_from_str(type, c);
    } else if (isdigit(l->ch)) {
      tok = token_new_from_str(INT, lexer_read_number(l));
    } else {
      tok = token_new_from_str(ILLEGAL, "illegal!");
    }
    return tok; // since we don't wanna read_char(l) we return early!!
  }
  lexer_read_char(l);

  return tok;
}