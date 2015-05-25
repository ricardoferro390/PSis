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



void test_add_message(void){



 cs*aux;

 char * dummy1 = "sample_text_one";

 char * dummy2 = "sample_text_two";

 char * dummy3 = "CRK2X13xXDJl88bgt25l8UUIOTY5gWZVopxuE5FY4ifmK88vWlk3ri8eSenii5B7hP0qOfPa3eONPA65f8kpakXn9r56kN40s8lzQYiKvQZXF8g3ADRGpjPD7QYlxJQKOi4M1iokBGj1wAlBsBbiueX1L3vvTpNpEtJT1WWCtLjOQhWsrPzuS4ir0u7JpHEjFNyGJ9j4NpYRBNavpWbATMCiucJ4AIPOe7x3hwBEAWcMO2uxRkmh041vmYgNbPmcS8CFf1hJc3JJsgLqAjSgaRABytG8c1714JkumAXyO79fwxMquHC8tEe5eTje0ulnezpY6xuzJQgkpzGJIxwt5pX7sJ5gRomLR0WbRC9osgCHtxVn6ZCeppjr6MpUFXxZe6Cm84kDALqrRkogIDxjrEUt6u13TOzqX57z60ancHyGGVHxNV3vujuJPrhENzWm8P3Pr4MxqRUMffR7PW3y3t2vNawXWAERwNRfgjpI9xYvJU7FViEzZ9gHEePXR5bC177vth1bgAGH2z2vxrwzTB65goZ02wOcwV5IivbgOTt0OiW2b5DqMJUzhiHQ9Z1yMYpj01YED0zYRhrnI24WYWpWGbUFxhhBLw8j2mnqb7HnJMh5AYggk7aISWICSGVm7k5NfxKRx8KEvnxnyTcowRmkKo9ucAB0W8hLlBKRLaZSXiXjxpmaO0Av9PwC7PwrJcFXMahqtbjIScwwGCgpTq4UFPH3gDnXEafePkJlBRPKE9iWQYS54W84mh12YDcc69hWILJowQL07ICZ7BVbGJPvbE4EmcHpq7OPe9Krh6qPHtoONIspHEP5hzYIr5ENNrpRyOc5iBBSEHJXokOlI9DOGBS2F5GpHOgCbAPnZe8sKlN76jMP1f1zkfwPBijUgjjDnT6P2XM358WksyXC5FIk6hmmSh1Y1LWgrg9Lygabca292sn9ayfAwhDPwJXBZlADMOKKGLkqpt5uOGoMe48X6rVIgiuRSqPRJgBrrc0DkZ59n6T24sq7AxM3oxhX";





 add_message(dummy1);

 aux = cs_list->next;





 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((strcmp(aux->message,dummy1))), (((void *)0)), (_U_UINT)29, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((aux->id)), (((void *)0)), (_U_UINT)30, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((aux->next)), (((void *)0)), (_U_UINT)31, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((number_of_messages)), (((void *)0)), (_U_UINT)32, UNITY_DISPLAY_STYLE_INT);





 add_message(dummy2);

 aux = aux->next;





 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((strcmp(aux->message,dummy2))), (((void *)0)), (_U_UINT)39, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((aux->id)), (((void *)0)), (_U_UINT)40, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((aux->next)), (((void *)0)), (_U_UINT)41, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((number_of_messages)), (((void *)0)), (_U_UINT)42, UNITY_DISPLAY_STYLE_INT);





 add_message(dummy3);





 UnityAssertEqualNumber((_U_SINT)((((void *)0))), (_U_SINT)((aux->next)), (((void *)0)), (_U_UINT)48, UNITY_DISPLAY_STYLE_INT);

}
