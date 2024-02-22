#include "lexer.h"
#include <stdlib.h>
#include <string.h>

Lexer *lexer_new(const char *input) {
  if (strlen(input) == 0)
    return NULL;
  Lexer *lexer = malloc(sizeof(Lexer));
  char *lexer_input = malloc(sizeof(char) * strlen(input));
  lexer->input = lexer_input;
  lexer->current_pos = -1;
  lexer->read_pos = 0;
  lexer->ch = -1;
  strcpy(lexer->input, input);
  return lexer;
}