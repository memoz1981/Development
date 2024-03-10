#include "../unity/unity.h"
int IsNumberEqualToFiveOrSixUsingIf(int); 
int IsNumberEqualToFiveOrSixUsingSwitchWithBrake(int); 
int IsNumberEqualToFiveOrSixUsingSwitchWithoutBrake(int); 
int IsNumberEqualToFiveOrSixUsingTernary(int); 

void if_else_statements_should_correctly_evaluate_the_condition(void)
{
    //arrange 
    int five = 5;
    int six = 6;
    int seven = 7; 

    //act
    int resultFive = IsNumberEqualToFiveOrSixUsingIf(five);
    int resultSix = IsNumberEqualToFiveOrSixUsingIf(six); 
    int resultSeven = IsNumberEqualToFiveOrSixUsingIf(seven); 

    //assert
    TEST_ASSERT_EQUAL_INT(1, resultFive); 
    TEST_ASSERT_EQUAL_INT(-1, resultSix); 
    TEST_ASSERT_EQUAL_INT(0, resultSeven); 
}

/* Note switch operations can only be used for integral types, not for non-integral types as arrays, strings, pointers, floating numbers etc. 
Also the switch statements are fit for exact match rather than range check, otherwise we go for if/else*/
void switch_statements_should_correctly_evaluate_the_condition_for_integral_types(void)
{
    //arrange 
    int five = 5;
    int six = 6;
    int seven = 7; 

    //act
    int resultFiveCorrect = IsNumberEqualToFiveOrSixUsingSwitchWithBrake(five);
    int resultFiveIncorrect = IsNumberEqualToFiveOrSixUsingSwitchWithoutBrake(five);

    int resultSixCorrect = IsNumberEqualToFiveOrSixUsingSwitchWithBrake(six);
    int resultSixIncorrect = IsNumberEqualToFiveOrSixUsingSwitchWithoutBrake(six);

    int resultSevenCorrect = IsNumberEqualToFiveOrSixUsingSwitchWithBrake(seven);
    int resultSevenIncorrect = IsNumberEqualToFiveOrSixUsingSwitchWithoutBrake(seven);
 
    //assert
    TEST_ASSERT_EQUAL_INT(0, resultFiveIncorrect); 
    TEST_ASSERT_EQUAL_INT(0, resultSixIncorrect); 
    TEST_ASSERT_EQUAL_INT(0, resultSevenIncorrect); 
    
    TEST_ASSERT_EQUAL_INT(1, resultFiveCorrect); 
    TEST_ASSERT_EQUAL_INT(-1, resultSixCorrect); 
    TEST_ASSERT_EQUAL_INT(0, resultSevenCorrect); 
}

void ternary_operator_statements_should_correctly_evaluate_the_condition(void)
{
    //arrange 
    int five = 5;
    int six = 6;
    int seven = 7; 

    //act
    int resultFive = IsNumberEqualToFiveOrSixUsingTernary(five);
    int resultSix = IsNumberEqualToFiveOrSixUsingTernary(six); 
    int resultSeven = IsNumberEqualToFiveOrSixUsingTernary(seven); 

    //assert
    TEST_ASSERT_EQUAL_INT(1, resultFive); 
    TEST_ASSERT_EQUAL_INT(-1, resultSix); 
    TEST_ASSERT_EQUAL_INT(0, resultSeven); 
}

void positive_integers_will_be_evaluated_to_true(void)
{
    //arrange
    int isTrue; 
    int check = 1; 

    //act
    if(check)
    {
        isTrue = 1; 
    }
    else
    {
        isTrue = 0; 
    }

    //assert
    TEST_ASSERT_EQUAL_INT(1, isTrue); 
}

void negative_integers_will_be_evaluated_to_true(void)
{
    //arrange
    int isTrue; 
    int check = -1; 

    //act
    if(check)
    {
        isTrue = 1; 
    }
    else
    {
        isTrue = 0; 
    }

    //assert
    TEST_ASSERT_EQUAL_INT(1, isTrue); 
}

void zero_will_be_evaluated_to_true(void)
{
    //arrange
    int isTrue; 
    int check = 0; 

    //act
    if(check)
    {
        isTrue = 1; 
    }
    else
    {
        isTrue = 0; 
    }

    //assert
    TEST_ASSERT_EQUAL_INT(0, isTrue); 
}

void run_conditional_logic_tests(void)
{
    UNITY_BEGIN();
    RUN_TEST(if_else_statements_should_correctly_evaluate_the_condition);
    RUN_TEST(switch_statements_should_correctly_evaluate_the_condition_for_integral_types);
    RUN_TEST(ternary_operator_statements_should_correctly_evaluate_the_condition);
    RUN_TEST(positive_integers_will_be_evaluated_to_true);
    RUN_TEST(negative_integers_will_be_evaluated_to_true);
    RUN_TEST(zero_will_be_evaluated_to_true); 
    UNITY_END();
}

int IsNumberEqualToFiveOrSixUsingIf(int num)
{
    if(num == 5)
    {
        return 1; 
    }
    else if(num == 6)
    {
        return -1; 
    }
    else
    {
        return 0; 
    }
}

int IsNumberEqualToFiveOrSixUsingSwitchWithBrake(int num)
{
    int result; 
    switch(num)
    {
        case 5: 
            result = 1;
            break; 

        case 6: 
            result = -1;
            break; 
        
        default: 
            result = 0;
    };

    return result; 
}

int IsNumberEqualToFiveOrSixUsingSwitchWithoutBrake(int num)
{
    int result; 
    switch(num)
    {
        case 5: 
            result = 1;

        case 6: 
            result = -1;
        
        default: 
            result = 0;
    };

    return result; 
}

int IsNumberEqualToFiveOrSixUsingTernary(int num)
{
    int result = num == 5 ? 1 : num == 6 ? -1 : 0; 

    return result; 
}