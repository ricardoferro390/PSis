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



void test_query(){



 char * dummy1 = "one_is_1";

 char * dummy2 = "two_is_2";

 char * dummy3 = "three_is_3";

 char * dummy4 = "four_is_4";

 char * dummy5 = "five_is_5";





 add_message(dummy1);

 add_message(dummy2);

 add_message(dummy3);

 add_message(dummy4);

 add_message(dummy5);







 printf("Query (7,8):\n");

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((query(7,8))), (((void *)0)), (_U_UINT)35, UNITY_DISPLAY_STYLE_INT);





 printf("\nQuery (1,3):\n");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(1,3))), (((void *)0)), (_U_UINT)39, UNITY_DISPLAY_STYLE_INT);





 printf("\nQuery (4,5):\n");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(4,5))), (((void *)0)), (_U_UINT)43, UNITY_DISPLAY_STYLE_INT);





 printf("\nQuery (2,6):\n");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(2,6))), (((void *)0)), (_U_UINT)47, UNITY_DISPLAY_STYLE_INT);





 printf("\nQuery (1,1000):");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(1,1000))), (((void *)0)), (_U_UINT)51, UNITY_DISPLAY_STYLE_INT);

}
