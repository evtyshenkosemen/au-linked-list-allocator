#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

/**
    \file
    \brief Linked list allocator library

    1) The following code compiles on Linux. 
    It has a number of problems, however. 
    Please locate as many of those problems as you are able and provide 
    your recommendations regarding how they can be resolved.
*/

	/* Counts the number of items in a list.
	 */
int count_list_items(const list_t *head) {
	int size = 0; /* replace recursive mechanism which can cause a stack overflow & gives incorrect sizes */
	while (head->next)
	{
		head = head->next;
		size++;
	}

	return size;
}

    /* Inserts a new list item after the one specified as the argument.
	 */
void insert_next_to_list(list_t *item, int data) {
	(item->next = malloc(sizeof(list_t)))->next = NULL; /* add NULL-terminator to the end of the list */
	item->next->data = data;
}

    /* Removes an item following the one specificed as the argument.
	 */
void remove_next_from_list(list_t *item) {
	list_t * new_next_PTR; 

	if (item->next) {
		new_next_PTR = item->next->next;
		free(item->next); 
		item->next = new_next_PTR;
	} /* else no next block (just ignore) */
}

	/* Returns item data as text.
	 */
char *item_data(const list_t *list)
{
	char buf[12];

	sprintf(buf, "%d", list->data);
	return buf;
}
