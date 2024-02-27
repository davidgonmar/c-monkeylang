#include "ast.h"
#include "lexer.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

void parser_panic(ParserError err) {
  printf("parser panic with error: %d", err);
  exit(EXIT_FAILURE);
}

Parser *parser_new(Lexer *l) {
  Parser *p = malloc(sizeof(Parser));
  if (p == NULL)
    return NULL;
  p->lexer = l;
  // initialize state
  parser_next_token(p);
  parser_next_token(p);
  return p;
}

void parser_next_token(Parser *p) {
  p->currToken = p->peekToken;
  p->peekToken = lexer_next_token(p->lexer);
}

Statement *statement_new(StatementType type) {
  Statement *st = malloc(sizeof(Statement));
  st->type = type;
  switch (type) {
  case STATEMENT_TYPE_LET:
    st->data.letSt = *(LetStatement *)malloc(sizeof(LetStatement));
    break;
  case STATEMENT_TYPE_RETURN:
    st->data.returnSt = *(ReturnStatement *)malloc(sizeof(ReturnStatement));
    break;
  default:
    parser_panic(PARSER_ERROR_UNKNOWN_STATEMENT);
  }
  return st;
}

static void parser_parse_let_statement(Parser *parser, Program *prog) {
  Statement *st = statement_new(STATEMENT_TYPE_LET);
  st->data.letSt.token = parser->currToken;
  parser_next_token(parser);
  if (parser->currToken->type != IDENT) {
    parser_panic(PARSER_ERROR_EXPECTED_IDENTIFIER);
  }
  Identifier *ident = malloc(sizeof(Identifier));
  ident->token = parser->currToken;
  ident->value = malloc((strlen(ident->token->literal) + 1) * sizeof(char));
  strcpy(ident->value, ident->token->literal);
  st->data.letSt.identifier = ident;
  st->data.letSt.value = malloc(sizeof(Expression));
  prog->statements[prog->n_statements] = st;
  prog->n_statements++;
}

static void parser_parse_return_statement(Parser *parser, Program *prog) {
  Statement *st = statement_new(STATEMENT_TYPE_RETURN);
  st->data.returnSt.token = parser->currToken;
  parser_next_token(parser);
  st->data.returnSt.retVal = malloc(sizeof(Expression));
  prog->statements[prog->n_statements] = st;
  prog->n_statements++;
}

Program *parser_parse_program(Parser *parser) {
  Program *prog = malloc(sizeof(prog));
  prog->n_statements = 0;
  prog->statements = malloc(sizeof(Statement *) * 50); // todo -> dinamic

  while (parser->peekToken->type != TEOF) {
    if (parser->currToken->type == LET) {
      parser_parse_let_statement(parser, prog);
    } else if (parser->currToken->type == RETURN) {
      parser_parse_return_statement(parser, prog);
    }
    parser_next_token(parser);
  }

  return prog;
}
