#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

/*
int setjmp(jmp_buf position) - Calling this macro will save the current code 
environment (stack pointer, frame pointer, and program counter) given a jmp_buf position variable.
It returns zero if called directly from setjmp.

void longjmp(jmp_buf position, int value) - Resets the stack pointer, frame pointer and 
program counter such that program execution begins at the point at which you called setjmp
with the given “position” jmp_buf variable

In general, try to stay away from setjmp/longjmp unless you have a very good reason for it.
setjmp/longjmp functionality is very similar to "goto". Using it can make your code very hard to read.
    
setjmp is like "try" and longjmp is like "throw" in other high-level languages like C# or JavaScript

For a well-respected article on how to implement
try/catch/throw/finally in C using macros and setjmp/longjmp,
check out this website: http://groups.di.unipi.it/~nids/docs/longjump_try_trow_catch.html

*/

void setjmp_longjump_can_be_used_to_jump_to_a_section_of_code(void)
{
    jmp_buf buf; 
    int iterator = 0; 
    int sum = 0; 

    if(setjmp(buf) == 10)
    {
        TEST_ASSERT_EQUAL_INT(55, sum); 
    }
    else
    {
        iterator = iterator + 1; 
        sum = sum + iterator; 
        longjmp(buf, iterator);
    }
}

void run_setjump_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(setjmp_longjump_can_be_used_to_jump_to_a_section_of_code); 
    UNITY_END(); 
}