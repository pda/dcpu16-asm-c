#ifndef INCLUDED_LABEL_TABLE_H
#define INCLUDED_LABEL_TABLE_H

#include <stdint.h>

// TODO: dynamically allocate and grow label table.
#define LABEL_TABLE_SIZE 32

typedef struct {
  int length;
  char * label[LABEL_TABLE_SIZE];
  uint16_t address[LABEL_TABLE_SIZE];
} label_table_t;

/**
 * Initialize an already-allocated label_table_t.
 */
void label_table_init(label_table_t *);

/**
 * Look up a label in the table
 * Return its address, or 0 if not found.
 */
uint16_t label_lookup(label_table_t *, char *);

/**
 * Write a label and address to the table.
 */
void label_write(label_table_t *, char *, uint16_t);

/**
 * Look up a label in the table, returning its address.
 * If it is not found, it is stored, and 0 is returned.
 */
uint16_t label_lookup_write(label_table_t *, label_table_t *, char *, uint16_t);

#endif
