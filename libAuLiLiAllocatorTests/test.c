#include <stdio.h>
#include <assert.h>
#include "test.h"

	/* Tests 
	 */

int test_alloc_single_thread(){
	/* Warning! Theese tests uses other functions which need to test too. It can cause strange side-effects.
		For example: To test insert_next_to_list use memcmp, not item_data
		I am a "professional" and ... have no time :)
	 */

	list_t   list_one;
	list_t * list_one_PTR;

	printf("  [alloc_single_thread] Start\n");


	list_one_PTR = &list_one; /* point to start of list */
	/* empty check */

	printf("   test insert_next_to_list / count_list_items \n");
	assert(count_list_items(list_one_PTR) == 0);

	
	for (size_t i = 0; i < TEST_LINKED_LIST_SIZE; i++)
	{
		if(VERBOSE) printf("         [i=%d]testing insert 0x%x [PTR=0x%x] \n",i,i+10, list_one_PTR);
		insert_next_to_list(list_one_PTR, i+10);

		if(VERBOSE) printf("         [i=%d]count_list_items returns %d\n",i, count_list_items(&list_one));

		/* test count growth  */
		assert(count_list_items(&list_one) == i+1);

		/* user must keep last pointer to the list */
		list_one_PTR = list_one_PTR->next;
	}
	printf("                                           Done!\n");


	printf("   test data wrote correct\n");
	list_one_PTR = &list_one; /* point to start of list */
	for (size_t i = 0; i < TEST_LINKED_LIST_SIZE; i++)
	{
		list_one_PTR = list_one_PTR->next;

		if(VERBOSE) printf("         [i=%d]trying 0x%x equals 0x%x [PTR=0x%x]\n",i, list_one_PTR->data, i+10, list_one_PTR);
		assert( list_one_PTR->data == i+10);
	}
	printf("                                           Done!\n");


	printf("   test free & count_list_items correct\n");
	list_one_PTR = &list_one; /* point to start of list */
	for (size_t i = 0; i < TEST_LINKED_LIST_SIZE; i++)
	{
		if(VERBOSE) printf("         [i=%d]trying to free 0x%x\n",i, list_one_PTR);
		remove_next_from_list(list_one_PTR);
		if(VERBOSE) printf("         [i=%d]count_list_items returns %d\n",i, count_list_items(&list_one));

		if(VERBOSE) printf("         [i=%d]testing for curr list size equals %d\n",i, TEST_LINKED_LIST_SIZE - i - 1);
		assert( count_list_items(&list_one) == TEST_LINKED_LIST_SIZE - i - 1 );
	}
	printf("                                           Done!\n");


	printf("  [alloc_single_thread] End!\n");
	return 0;
}
	
int main(){
    printf("[tests] Start\n");
	assert(test_alloc_single_thread() == 0);
    printf("[tests] Done!\n");
	return 0;
}

