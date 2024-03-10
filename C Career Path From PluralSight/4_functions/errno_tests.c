#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
extern int errno - This global variable is used by system calls and C standard library functions in order to 
communicate an error code 

int EDOM - This macro can be compared against the current value of ”errno” and represents a domain error 
when using a mathematical function 

int ERANGE  - This macro can be compared against the current 
value of ”errno” and represents a range error when using a mathematical function
The C standard does not require EDOM be set by math functions

EDOM and ERANGE are just two fo the required macros for errno.h to implement on a given platform.
For a more complete list of error codes you can check out:
https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html

*/

void edom_will_be_set_on_domain_error(void)
{
    //arrange
 
    //act
    double result = sqrt(-1.0); 
    int isnan = isnan(result); //this macro is under math.h

    //assert
    TEST_ASSERT_EQUAL(EDOM, errno); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isnan); 
}

void erange_will_be_set_on_range_error(void)
{
    //arrange
 
    //act
    double result = log(0); 
    int isfinite = isfinite(result); //this macro is under math.h

    //assert
    TEST_ASSERT_EQUAL(ERANGE, errno); 
    TEST_ASSERT_EQUAL_INT(0, isfinite); 
}

void run_errno_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(edom_will_be_set_on_domain_error); 
    RUN_TEST(erange_will_be_set_on_range_error); 
    UNITY_END(); 
}