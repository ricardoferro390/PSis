#include "unity.h"
#include "chat_storage.h"
#include <string.h>

int number_of_messages;
cs * cs_list;

void setUp(void)
{
	cs_init();
}

void tearDown(void)
{
}

void test_query(){
	//set of random messages
	char * dummy1 = "one_is_1";
	char * dummy2 = "two_is_2";
	char * dummy3 = "three_is_3";
	char * dummy4 = "four_is_4";
	char * dummy5 = "five_is_5";
	
	//add them to list
	add_message(dummy1);
	add_message(dummy2);
	add_message(dummy3);
	add_message(dummy4);
	add_message(dummy5);
	
	//do set of queries to illustrate function behaviour (return values)
	//need to verify if query's minimum value is lower than total number of messages
	printf("Query (7,8):\n");
	TEST_ASSERT_EQUAL(0, query(7,8));
	
	//normal query
	printf("\nQuery (1,3):\n");
	TEST_ASSERT_EQUAL(1, query(1,3));
	
	//query to message limit
	printf("\nQuery (4,5):\n");
	TEST_ASSERT_EQUAL(1, query(4,5));
	
	//query with maxvalue higher than message number, return aall messages until the end of list
	printf("\nQuery (2,6):\n");
	TEST_ASSERT_EQUAL(1, query(2,6));
	
	//same behaviour as previous query
	printf("\nQuery (1,1000):");
	TEST_ASSERT_EQUAL(1, query(1,1000));
}
