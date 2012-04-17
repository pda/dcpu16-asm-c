#include <stdio.h>

#include "label_table.h"
#include "string.h"

void label_table_init(label_table_t * lt)
{
  lt->length = 0;
}

uint16_t label_lookup(label_table_t * lt, char * label)
{
  uint16_t address = 0;

  // TODO: less string comparisons; hash table?
  for (int i = 0; i < lt->length; i++)
    if (strcmp(lt->label[i], label) == 0) address = lt->address[i];

  return address;
}

void label_write(label_table_t * lt, char * label, uint16_t address)
{
  int i = lt->length++;
  lt->label[i] = label; // TODO: malloc & copy?
  lt->address[i] = address;
}

uint16_t label_lookup_write(
  label_table_t * from, label_table_t * to,
  char * label, uint16_t address
)
{
  uint16_t found_address;

  if ((found_address = label_lookup(from, label)))
    return found_address;

  label_write(to, label, address);
  return 0;
}

void label_table_print(label_table_t * t)
{
  for (int i = 0; i < t->length; i++)
    printf("  :%s => 0x%04x\n", t->label[i], t->address[i]);
}
