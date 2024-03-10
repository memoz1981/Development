#include "func_tests.h"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../unity/unity.h"

/*
Variadic Functions – stdarg.h
Variadic Function Macros
void va_start(va_list list, arg_before_list) - This macro initializes a variable argument list 
(i.e. bootstraps)
type va_arg(va_list list, type) - This macro fetches the next argument in the list 
of the given type
void va_end(va_list list) - This macro allows the variadic function to return 
normally by marking that it is done with the variable argument list. This MUST be called once the 
processing of variable arguments end. 

Note: as per below example, normal arguments can be passed for variadic functions... 
*/

void va_print(const char* fileName, const char* formatted_str, ...)
{
    va_list args; 
    va_start(args, formatted_str); 
    time_t timestamp = time(NULL); 
    char* timeString = asctime(gmtime(&timestamp)); 
    
    // Get rid of the trailing newline character that "asctime" generates
    char* new_line_ptr = strchr(timeString, '\n');
    if(new_line_ptr)
        *new_line_ptr = '\0'; 
    
    remove(fileName);  
    FILE* file = fopen(fileName, "w+");
    vfprintf(file, formatted_str, args); 
    vprintf(formatted_str, args); 

    va_end(args); 
    fclose(file); 
}

void va_List_can_be_used_to_access_variadic_arguments_and_three_dots_used_to_denote_variadic_parameters(void)
{
    //arrange
    char* name = "Mark"; 
 
    //act
    const char* fileName = "../bin/vaprint.txt";
    va_print(fileName, "Formatted string: %d %.1f %s", 1, 1.1, name);
    
    FILE* file = fopen(fileName, "r"); 
    char buffer[100]; 
    memset(buffer, '\0', 100); 
    fgets(buffer, 100, file); 

    //assert
    int result = strcmp("Formatted string: 1 1.1 Mark", buffer); 
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void run_stdarg_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(va_List_can_be_used_to_access_variadic_arguments_and_three_dots_used_to_denote_variadic_parameters); 
    UNITY_END(); 
}