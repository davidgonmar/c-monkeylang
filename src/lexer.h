typedef struct Lexer {
  /// The input code to be lexed
  char *input;
  /// The current position in the input
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
 */
Lexer *lexer_new(const char *input);