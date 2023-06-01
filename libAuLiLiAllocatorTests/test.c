#include <stdio.h>
#include <assert.h>
#include "test.h"

	/* Tests 
	 */

int test_alloc_single_thread(){
	list_t   list_one;
	list_t * list_one_PTR = &list_one;

	printf("    [alloc_single_thread] Start\n");

	/* empty check */
	assert(count_list_items(list_one_PTR) == 0);

	for (size_t i = 0; i < TEST_LINKED_LIST_SIZE; i++)
	{
		if(VERBOSE) printf("         [i=%d]testing insert 0x%x to 0x%x \n",i,i+10, list_one_PTR);
		insert_next_to_list(list_one_PTR, i+10);

		if(VERBOSE) printf("         [i=%d]count_list_items returns %d\n",i, count_list_items(&list_one));

		/* test count growth  */
		assert(count_list_items(&list_one) == i+1);

		/* user must keep last pointer to the list */
		list_one_PTR = list_one_PTR->next;
	}

	printf("    [alloc_single_thread] End!\n");

	

	return 0;
}
	
int main(){
    printf("[tests] Start\n");
	assert(test_alloc_single_thread() == 0);
    printf("[tests] Done!\n");
	return 0;
}

