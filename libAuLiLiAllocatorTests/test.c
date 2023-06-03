#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include "test.h"

	/* Tests 
	 */

int test_alloc_single_thread(){
	/* Warning! Theese tests uses other functions which need to test too. It can cause strange side-effects.
		For example: To test insert_next_to_list use memcmp, not item_data
		I am a "professional" and ... have no time :)
	 */

	list_t   list_one = {NULL, 0};
	list_t * list_one_PTR;
	char buf[SPRINTF_BUFF_SIZE] = {'\0'};
	char valid_buf[SPRINTF_BUFF_SIZE] = {'\0'};

	printf("  [alloc_single_thread] Start\n");


	list_one_PTR = &list_one; /* point to start of list */
	/* empty check */

	printf("   test count_list_items() / insert_next_to_list() \n");
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


	printf("   test remove_next_from_list() & count_list_items()\n");
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

	if(VERBOSE) printf("         check for list empty\n");
	assert(count_list_items(list_one_PTR) == 0);

	printf("   test item_data()\n");
	list_one_PTR = &list_one; /* point to start of list */
	if(VERBOSE) printf("         writing data\n");
	for (size_t i = 0; i < 256; i++)
	{
		if(VERBOSE) printf("         [i=%d]trying insert 0x%x [PTR=0x%x] \n",i,i, list_one_PTR);
		insert_next_to_list(list_one_PTR, i); /* insert test val */

		
		if(VERBOSE) printf("         [i=%d]count_list_items returns %d\n",i, count_list_items(&list_one));

		/* test count growth  */
		assert(count_list_items(&list_one) == i+1);

		/* user must keep last pointer to the list */
		list_one_PTR = list_one_PTR->next;
	}

	if(VERBOSE) printf("         checking data\n");
	list_one_PTR = &list_one; /* point to start of list */
	for (size_t i = 0; i < 256; i++)
	{
		/* skip 1st empty cell */
		list_one_PTR = list_one_PTR->next;

		memset(valid_buf, '\0', SPRINTF_BUFF_SIZE); /* flush valid buff cause we comparing raw bytes not strings */
		sprintf(valid_buf, "%d", i); /* generate valid value */
		item_data(list_one_PTR, buf); /* getting data via testing func */

		if(VERBOSE) printf("         [i=%d]compare valid %s with %s\n",i,valid_buf, buf);
		assert(memcmp(valid_buf, buf, SPRINTF_BUFF_SIZE) == 0);
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

