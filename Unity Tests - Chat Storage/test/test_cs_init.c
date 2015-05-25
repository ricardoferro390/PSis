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

void test_cs_init(void)
{
	//test list initialization values
	TEST_ASSERT_EQUAL(NULL, cs_list->message);
	TEST_ASSERT_EQUAL(0, cs_list->id);
	TEST_ASSERT_EQUAL(NULL, cs_list->next);
	TEST_ASSERT_EQUAL(0, number_of_messages);
}




