#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *check_malloc(void *input) {
  if (input == NULL) {
    perror("Error allocating memory");
    exit(EXIT_FAILURE);
  }
  return input;
}
int main() {
  char *input = check_malloc(malloc(1));
  input[0] = '\0';

  size_t input_size = 0;
  char *line = NULL;

  printf("Welcome to the monkeylang REPL. Please provide an input: \n");

  while (1) {
    long line_length = getline(&line, &input_size, stdin);
    if (line_length == -1) {
      perror("Error reading input");
      free(input);
      free(line);
      exit(EXIT_FAILURE);
    }

    // End of input is an empty line
    if (strcmp(line, "\n") == 0) {
      break;
    }

    input = realloc(input, strlen(input) + line_length + 1);
    strcat(input, line);
  }
  free(line);
  printf("Tokenizing input: \n");

  Lexer *lexer = lexer_new(input);

  while (1) {
    Token *tok = lexer_next_token(lexer);

    char *str = token_to_str(tok);

    printf("%s\n", str);

    if (tok->type == TEOF) {
      break;
    }
  }

  free(input);

  return 0;
}