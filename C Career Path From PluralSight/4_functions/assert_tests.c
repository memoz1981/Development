#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
void assert(int expression) - If the expression fed into this macro evaluates to 
true, nothing happens. If the expression evaluates to false, the macro 
will write a message to stderr and abort program execution
*/

void run_test_true_assertions(void)
{
    //arrange
    char* name1 = "Mehdi"; 
    char* name2 = "Mehdi"; 
    int isTrue = 0; 
    
    //act
    assert(name1 == name2);
    isTrue = 1; 

    //assert
    TEST_ASSERT_EQUAL_INT(1, isTrue); 
}

void run_test_false_assertions(void)
{
    TEST_IGNORE(); 
}

void run_assert_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(run_test_true_assertions);
    RUN_TEST(run_test_false_assertions); 
    UNITY_END(); 
}