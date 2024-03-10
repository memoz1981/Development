#include "../unity/unity.h"

/*
This section mostly defines best practices:

1) Function prototype (defined in header files or on the top of .c files)
void function_declared();
void function_prototype(void); 
void function_prototype_without_named_parameters(int, int); 
void function_prototype_with_named_parameters(int count, int number); 

2) const
- variables that are readonly should be denoted as const where possible

3) static
- internal private method should be denoted as static - these will be used only inside .c file

4) .h files (header) vs .c files
- Any methods or variables that will be externally available should be in .h files
- Others in c files
- Best practice is to declare private function on top of c files, then implement

5) Functions
- SHould be as short as possible
- Have single responsibility
- Should not use global variables where possible
- Should use const/static keywords where possible. 

6) Pass by ref vs pass by value
- Everything is pass by value in C (even the pointers get copied)

*/

void test(void)
{
    TEST_ASSERT_EQUAL(1,1);
}

void run_function_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(test); 
    UNITY_END(); 
}