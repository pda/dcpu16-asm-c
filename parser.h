#ifndef INCLUDED_PARSER_H
#define INCLUDED_PARSER_H

#include "statement.h"

// TODO: dynamically grow statement allocation.
#define PR_STATEMENTS_LIMIT 64

typedef struct {
  statement_t * statements[PR_STATEMENTS_LIMIT];
  int statement_count;
} parse_result_t;

/**
 * Parses the assembly code into a parse_result_t.
 */
parse_result_t * parse(char *);

/**
 * Releases memory allocated to a parse_result_t and its members.
 */
void free_parse_result(parse_result_t *);

#endif
