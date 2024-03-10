#include "cpp_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void conditional_directives_will_check_for_condition_during_preprocessing(void)
{
    //arrange
    #ifdef CUSTOM_NUM
    {
        #define num 1
    }
    #endif

    //act

    //assert
    TEST_ASSERT_EQUAL_INT(1, num); 
}

void line_directive_will_alter_line_and_file_number(void)
{
    //arrange
    int currentLineNumber = __LINE__; //built in macro that returns the current line number
    char *currentFileName = __FILE__; //built in macro that returns the line number

    //act
    #line 10000 "cpp_tests_new.c"
    int newLineNumber = __LINE__; 
    char* newFileName = __FILE__; 

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(currentLineNumber, newLineNumber);
    int areFileNamesEqual = strcmp(currentFileName, newFileName); 
    TEST_ASSERT_NOT_EQUAL_INT(0, areFileNamesEqual); 
}

void test_special_macros(void)
{
    //arrange

    //act
    printf("Special macros: %s, %d, %s, %s, %s", __FILE__, __LINE__, __DATE__, __TIME__, __func__); 

    //assert
    TEST_ASSERT_EQUAL_INT(1, 1);
}

void macro_argument_can_be_stringized(void)
{
    //arrange
    #define func1(s) func2(s)
    #define func2(s) #s //stringization
    #define SOURCE 10

    //act
    char* str1 = func1(SOURCE);
    char* str2 = func2(SOURCE); 

    //assert
    int result1 = strcmp("10", str1); 
    int result2 = strcmp("SOURCE", str2);
    
    TEST_ASSERT_EQUAL_INT(0, result1);
    TEST_ASSERT_EQUAL_INT(0, result2);
}

void variable_names_can_be_concatenated(void)
{
    //arrange
    #define CONCAT(X,Y) X##Y

    int ab = 5;
    int c = CONCAT(a, b); 

    TEST_ASSERT_EQUAL_INT(5, c); 
}

void macro_names_can_be_undefined_and_redefined(void)
{
    //arrange
    #define BUFFER_SIZE 512

    //act
    int sizeInitial = BUFFER_SIZE; 

    #undef BUFFER_SIZE
    #define BUFFER_SIZE 256

    int sizeFinal = BUFFER_SIZE; 

    //assert
    TEST_ASSERT_EQUAL_INT(512, sizeInitial);
    TEST_ASSERT_EQUAL_INT(256, sizeFinal);
}

void run_cpp_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(conditional_directives_will_check_for_condition_during_preprocessing);
    RUN_TEST(line_directive_will_alter_line_and_file_number); 
    RUN_TEST(test_special_macros); 
    RUN_TEST(macro_argument_can_be_stringized); 
    RUN_TEST(variable_names_can_be_concatenated); 
    RUN_TEST(macro_names_can_be_undefined_and_redefined); 
    UNITY_END(); 
}