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



void test_cs_init(void)

{



 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((cs_list->message)), (((void *)0)), (_U_UINT)20, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((cs_list->id)), (((void *)0)), (_U_UINT)21, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((cs_list->next)), (((void *)0)), (_U_UINT)22, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((number_of_messages)), (((void *)0)), (_U_UINT)23, UNITY_DISPLAY_STYLE_INT);

}
