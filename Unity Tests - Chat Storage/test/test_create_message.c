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

void test_create_message(void)
{
	char * dummy = "sample_text";
	cs * new_message;
	
	//create list element with dummy string
	new_message = create_message(dummy);
	
	//test element's fields
	TEST_ASSERT_EQUAL(0, strcmp(new_message->message,dummy));
	TEST_ASSERT_EQUAL(1, new_message->id);
	TEST_ASSERT_EQUAL(NULL, new_message->next);
}
