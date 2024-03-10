#include "../unity/unity.h"

void for_loop_will_check_condition_and_then_process(void)
{
    //arrange
    int forCount = 0; 
    int maxCount = 5;

    //act
    for(int i=0; i<maxCount;i++)
    {
        forCount++; 
    }

    //assert
    TEST_ASSERT_EQUAL_INT(maxCount, forCount); 
}

void while_loop_will_check_condition_and_then_process(void)
{
    //arrange
    int forCount = 0; 
    int maxCount = 5;
    int i = 0; 

    //act
    while(i < maxCount)
    {
        forCount++; 
        i++; 
    }

    //assert
    TEST_ASSERT_EQUAL_INT(maxCount, forCount); 
}

void do_while_loop_will_execute_first_and_then_check_condition_for_next_cycle(void)
{
    //arrange
    int forCount = 0; 
    int maxCount = 5;
    int i = 0; 

    //act
    do
    {
        forCount++; 
        i++; 
    }
    while(i < maxCount); 

    //assert
    TEST_ASSERT_EQUAL_INT(maxCount, forCount); 
}

void run_iterator_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(for_loop_will_check_condition_and_then_process); 
    RUN_TEST(while_loop_will_check_condition_and_then_process); 
    RUN_TEST(do_while_loop_will_execute_first_and_then_check_condition_for_next_cycle); 
    UNITY_END(); 
}