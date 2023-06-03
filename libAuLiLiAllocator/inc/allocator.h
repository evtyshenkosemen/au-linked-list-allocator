#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "autoconf.h"

typedef struct list_s
{
        struct list_s *next; /* NULL for the last item in a list */
        int data;
}
list_t;

int  count_list_items(const list_t *head);
void insert_next_to_list(list_t *item, int data);
void remove_next_from_list(list_t *item);
void item_data(const list_t *list, char *buf);

#endif //ALLOCATOR_H