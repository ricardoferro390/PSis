#include "chat_storage.h"
#include "unity.h"


int number_of_messages;

cs * cs_list;



void setUp(void)

{

}



void tearDown(void)

{

}



void test_cs_init(void)

{

 cs_init();



 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((cs_list->message)), (((void *)0)), (_U_UINT)20, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((cs_list->id)), (((void *)0)), (_U_UINT)21, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((cs_list->next)), (((void *)0)), (_U_UINT)22, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((number_of_messages)), (((void *)0)), (_U_UINT)23, UNITY_DISPLAY_STYLE_INT);

}



void test_create_message(void)

{

 cs_init();



 char * dummy = "sample_text";

 cs * new_message;



 new_message = create_message(dummy);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((strcmp(new_message->message,dummy))), (((void *)0)), (_U_UINT)35, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((new_message->id)), (((void *)0)), (_U_UINT)36, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((new_message->next)), (((void *)0)), (_U_UINT)37, UNITY_DISPLAY_STYLE_INT);

}



void test_add_message(void){



 cs*aux;



 cs_init();



 char * dummy1 = "sample_text_one";

 char * dummy2 = "sample_text_two";

 char * dummy3 = "CRK2X13xXDJl88bgt25l8UUIOTY5gWZVopxuE5FY4ifmK88vWlk3ri8eSenii5B7hP0qOfPa3eONPA65f8kpakXn9r56kN40s8lzQYiKvQZXF8g3ADRGpjPD7QYlxJQKOi4M1iokBGj1wAlBsBbiueX1L3vvTpNpEtJT1WWCtLjOQhWsrPzuS4ir0u7JpHEjFNyGJ9j4NpYRBNavpWbATMCiucJ4AIPOe7x3hwBEAWcMO2uxRkmh041vmYgNbPmcS8CFf1hJc3JJsgLqAjSgaRABytG8c1714JkumAXyO79fwxMquHC8tEe5eTje0ulnezpY6xuzJQgkpzGJIxwt5pX7sJ5gRomLR0WbRC9osgCHtxVn6ZCeppjr6MpUFXxZe6Cm84kDALqrRkogIDxjrEUt6u13TOzqX57z60ancHyGGVHxNV3vujuJPrhENzWm8P3Pr4MxqRUMffR7PW3y3t2vNawXWAERwNRfgjpI9xYvJU7FViEzZ9gHEePXR5bC177vth1bgAGH2z2vxrwzTB65goZ02wOcwV5IivbgOTt0OiW2b5DqMJUzhiHQ9Z1yMYpj01YED0zYRhrnI24WYWpWGbUFxhhBLw8j2mnqb7HnJMh5AYggk7aISWICSGVm7k5NfxKRx8KEvnxnyTcowRmkKo9ucAB0W8hLlBKRLaZSXiXjxpmaO0Av9PwC7PwrJcFXMahqtbjIScwwGCgpTq4UFPH3gDnXEafePkJlBRPKE9iWQYS54W84mh12YDcc69hWILJowQL07ICZ7BVbGJPvbE4EmcHpq7OPe9Krh6qPHtoONIspHEP5hzYIr5ENNrpRyOc5iBBSEHJXokOlI9DOGBS2F5GpHOgCbAPnZe8sKlN76jMP1f1zkfwPBijUgjjDnT6P2XM358WksyXC5FIk6hmmSh1Y1LWgrg9Lygabca292sn9ayfAwhDPwJXBZlADMOKKGLkqpt5uOGoMe48X6rVIgiuRSqPRJgBrrc0DkZ59n6T24sq7AxM3oxhX";



 add_message(dummy1);

 aux = cs_list->next;



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((strcmp(aux->message,dummy1))), (((void *)0)), (_U_UINT)53, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((aux->id)), (((void *)0)), (_U_UINT)54, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((aux->next)), (((void *)0)), (_U_UINT)55, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((number_of_messages)), (((void *)0)), (_U_UINT)56, UNITY_DISPLAY_STYLE_INT);



 add_message(dummy2);

 aux = aux->next;



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((strcmp(aux->message,dummy2))), (((void *)0)), (_U_UINT)61, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((aux->id)), (((void *)0)), (_U_UINT)62, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((aux->next)), (((void *)0)), (_U_UINT)63, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((number_of_messages)), (((void *)0)), (_U_UINT)64, UNITY_DISPLAY_STYLE_INT);



 add_message(dummy3);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((aux->next)), (((void *)0)), (_U_UINT)67, UNITY_DISPLAY_STYLE_INT);



}



void test_query(){



 cs_init();



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

 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((query(7,8))), (((void *)0)), (_U_UINT)88, UNITY_DISPLAY_STYLE_INT);



 printf("\nQuery (1,3):\n");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(1,3))), (((void *)0)), (_U_UINT)91, UNITY_DISPLAY_STYLE_INT);



 printf("\nQuery (4,5):\n");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(4,5))), (((void *)0)), (_U_UINT)94, UNITY_DISPLAY_STYLE_INT);



 printf("\nQuery (2,6):\n");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(2,6))), (((void *)0)), (_U_UINT)97, UNITY_DISPLAY_STYLE_INT);



 printf("\nQuery (1,1000):");

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((query(1,1000))), (((void *)0)), (_U_UINT)100, UNITY_DISPLAY_STYLE_INT);



}
