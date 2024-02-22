#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer *lexer_new(const char *input) {
  if (strlen(input) == 0)
    return NULL;
  Lexer *lexer = malloc(sizeof(Lexer));
  if (lexer == NULL)
    return NULL;
  char *lexer_input = malloc(sizeof(char) * strlen(input));
  lexer->input = lexer_input;
  lexer->current_pos = -1;
  lexer->read_pos = 0;
  lexer->ch = '\0';
  strcpy(lexer->input, input);
  read_char(lexer);
  return lexer;
}

void read_char(Lexer *l) {
  if (l->read_pos >= strlen(l->input)) {
    l->ch = '\0'; // finished reading
  } else {
    l->ch = l->input[l->read_pos];
  }
  l->current_pos = l->read_pos;
  l->read_pos++;
}

Token *next_token(Lexer *l) {
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
  case '\0':
    tok = token_new_from_char(TEOF, '\0');
    break;
  }

  read_char(l);

  return tok;
}