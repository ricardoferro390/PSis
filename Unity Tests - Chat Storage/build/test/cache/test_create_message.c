#include "chat_storage.h"
#include "unity.h"


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





 new_message = create_message(dummy);





 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((strcmp(new_message->message,dummy))), (((void *)0)), (_U_UINT)26, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((new_message->id)), (((void *)0)), (_U_UINT)27, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((new_message->next)), (((void *)0)), (_U_UINT)28, UNITY_DISPLAY_STYLE_INT);

}
