#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "lexer.h"
#include "operand.h"
#include "statement.h"
#include "token.h"
#include "utils.h"

#include "parser.h"

static int parse_statement(lexer_state *, statement_t *);
static void parse_discard_empty_lines(lexer_state *);
static void parse_label(lexer_state *, statement_t *);
static void parse_mnemonic(lexer_state *, statement_t *);
static void parse_operands(lexer_state *, statement_t *);
static void parse_operand(lexer_state *, statement_t *, int index);
static void parse_operand_indirect(lexer_state *, operand_t *);
static uint8_t parser_opcode_for_mnemonic(char *);
static enum operand_type operand_type_for_name(const char *);

parse_result_t * parse(char * source)
{
  int statement_count;
  parse_result_t * pr = (parse_result_t *)malloc(sizeof(parse_result_t));

  lexer_state state;
  lexer_init(&state, source);

  // statement storage
  statement_t * statement_writer =
    (statement_t *)malloc(sizeof(statement_t) * PR_STATEMENTS_LIMIT);

  statement_t ** pointer_writer = pr->statements;
  while (parse_statement(&state, statement_writer))
    *(pointer_writer++) = statement_writer++;

  *(pointer_writer) = 0; // null terminate statement list.

  return pr;
}

void free_parse_result(parse_result_t * pr)
{
  free(pr->statements);
  free(pr);
}

static int parse_statement(lexer_state * state, statement_t * s)
{
  token_t * t;
  statement_init(s);

  parse_discard_empty_lines(state);

  t = peek_token(state, 1);
  if (!t) return 0;

  if (t->type == T_LABEL)
    parse_label(state, s);

  parse_mnemonic(state, s);

  parse_operands(state, s);

  if (peek_token(state, 1)->type == T_COMMENT)
    next_token(state);

  if (next_token(state)->type != T_NEWLINE)
    CRASH("expected T_NEWLINE");

  return 1;
}

static void parse_discard_empty_lines(lexer_state * state)
{
  token_t * t;
  while ((t = peek_token(state, 1)) && (t->type == T_COMMENT || t->type == T_NEWLINE))
    next_token(state);
}

static void parse_label(lexer_state * state, statement_t * s)
{
  token_t * t = next_token(state);
  s->label = (char *)malloc(t->size);
  if (!s->label) CRASH("malloc label");
  memcpy(s->label, t->value, t->size);
}

static void parse_mnemonic(lexer_state * state, statement_t * s)
{
  token_t * t = next_token(state);
  if (t->type != T_NAME) { print_token(t); CRASH("expected T_NAME"); }
  memcpy(s->mnemonic, t->value, 4);
  s->opcode = parser_opcode_for_mnemonic(s->mnemonic);
}

static void parse_operands(lexer_state * state, statement_t * s)
{
  parse_operand(state, s, 0);
  if (next_token(state)->type == T_COMMA)
    parse_operand(state, s, 1);
  else
    s->operand[1].type = O_NULL;
}

static void parse_operand(lexer_state * state, statement_t * s, int index)
{
  operand_t * o = &s->operand[index];
  token_t * t = next_token(state);
  const char * v = t->value;

  switch (t->type)
  {
    case T_BRACKET_L:
      parse_operand_indirect(state, o);
      break;

    case T_NAME:
      o->type = operand_type_for_name(v);
      if (o->type == O_REG)
        operand_set_reg_by_name(o, t->value);
      else if (o->type == O_LITERAL)
        operand_set_label(o, t->value, t->size);
      break;

    case T_INT_HEX:
      o->type = O_NW;
      o->next_word = (uint16_t)strtoul(t->value, 0, 16);
      break;

    case T_INT_DEC:
      o->type = O_NW;
      o->next_word = (uint16_t)strtoul(t->value, 0, 10);
      break;

    default:
      print_token(t);
      CRASH("parse_operand");
      break;
  }
}

static void parse_operand_indirect(lexer_state * state, operand_t * o)
{
  token_t * t = next_token(state);
  switch (t->type)
  {
    case T_NAME:
      // TODO: assuming register; could this be a label?
      if (next_token(state)->type != T_BRACKET_R)
        CRASH("expected T_BRACKET_R");
      o->type = O_INDIRECT_REG;
      break;

    case T_INT_HEX:
      o->next_word = (uint16_t)strtoul(t->value, 0, 16);
      t = next_token(state);
      switch (t->type)
      {
        case T_BRACKET_R:
          o->type = O_INDIRECT_NW;
          break;
        case T_PLUS:
          t = next_token(state);
          if (t->type != T_NAME) CRASH("expected T_NAME");
          o->type = O_INDIRECT_NW_OFFSET;
          operand_set_reg_by_name(o, t->value);
          if (next_token(state)->type != T_BRACKET_R)
            CRASH("expected T_BRACKET_R");
          break;
        default:
          CRASH("expected T_BRACKET_R or T_PLUS");
          break;
      }
      break;

    default:
      CRASH("default");
  }
}

static uint8_t parser_opcode_for_mnemonic(char * m)
{
  // basic opcodes
  if (strcmp(m, "SET") == 0) return 0x1;
  if (strcmp(m, "ADD") == 0) return 0x2;
  if (strcmp(m, "SUB") == 0) return 0x3;
  if (strcmp(m, "MUL") == 0) return 0x4;
  if (strcmp(m, "DIV") == 0) return 0x5;
  if (strcmp(m, "MOD") == 0) return 0x6;
  if (strcmp(m, "SHL") == 0) return 0x7;
  if (strcmp(m, "SHR") == 0) return 0x8;
  if (strcmp(m, "AND") == 0) return 0x9;
  if (strcmp(m, "BOR") == 0) return 0xA;
  if (strcmp(m, "XOR") == 0) return 0xB;
  if (strcmp(m, "IFE") == 0) return 0xC;
  if (strcmp(m, "IFN") == 0) return 0xD;
  if (strcmp(m, "IFG") == 0) return 0xE;
  if (strcmp(m, "IFB") == 0) return 0xF;
  if (strcmp(m, "IFB") == 0) return 0xF;

  // non-basic opcodes
  if (strcmp(m, "JSR") == 0) return 0x10;

  puts(m); CRASH("parser_opcode_for_mnemonic");
  return -1;
}

static enum operand_type operand_type_for_name(const char * n)
{
  char c = *n;
  size_t l = strlen(n);

  // general registers
  if (l == 1 && (
      c == 'A' || c == 'B' || c == 'C' ||
      c == 'X' || c == 'Y' || c == 'Z' ||
      c == 'I' || c == 'J')) return O_REG;

  // special registers
  if (strcmp(n, "PC") == 0) return O_PC;
  if (strcmp(n, "SP") == 0) return O_SP;
  if (strcmp(n, "O") == 0) return O_O;

  // stack operations
  if (strcmp(n, "POP") == 0) return O_POP;
  if (strcmp(n, "PEEK") == 0) return O_PEEK;
  if (strcmp(n, "PUSH") == 0) return O_PUSH;

  // label
  return O_LITERAL;
}
