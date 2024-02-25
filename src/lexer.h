#pragma once

#include "token.h"
#include <stdlib.h>

typedef struct Lexer {
  /// The input code to be lexed
  char *input;
  /// The current position in the input (not read yet)
  int current_pos;
  /// The next position in the input (to be read)
  int read_pos;
  /// The current character under examination
  char ch;
} Lexer;

/**
 * @brief Create a new lexer
 *
 * @param input The input code to be lexed
 *
 * @return Lexer* The lexer instance
 */
Lexer *lexer_new(const char *input);

/**
 * @brief Advances one position in the input and sets the current character
 * (l->ch) to the next character in the input
 *
 * @param lexer Lexer instance
 *
 * @return void
 */
void lexer_read_char(Lexer *lexer);

/**
 * @brief Returns the next token. Advances the lexer's position in the input
 * by calling lexer_read_char. In case it finds an identifier, it will advance
 * appropriately the position in the input.
 *
 * @param lexer Lexer instance
 */
Token *lexer_next_token(Lexer *lexer);

/**
 * @brief Reads an identifier from the lexer's current position and returns
 * it.
 *
 * @param lexer Lexer instance
 */
char *lexer_read_identifier(Lexer *lexer);

/**
 * @brief Returns the token type for a given identifier. It returns IDENT if the
 * identifier is not a reserved keyword
 *
 * @param ident The identifier to be looked up
 *
 * @return TokenType The token type for the given identifier
 */
TokenType lexer_lookup_ident(const char *ident);

/**
 * @brief Skips any whitespace characters in the input until it finds a
 * non-whitespace character
 *
 * @param lexer Lexer instance
 */
void lexer_skip_whitespace(Lexer *lexer);

/**
 * @brief Gets the next character in the input without advancing the lexer's
 * position
 *
 * @param lexer Lexer instance
 */
char lexer_peek_char(Lexer *lexer);