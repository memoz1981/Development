#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
Commonly Used Math Functions
double ceil(double x) - Calculates the smallest integer greater than or equal to x
double floor(double x) - Calculates the largest integer less than or equal to x
double fabs(double x) - This is the floating-point equivalent to “abs” and 
“labs” – functions which both reside within the stdlib.h header file
double log(double x) - Calculates the base-e logarithm of x
double pow(double x, double y) - Calculates the value of x raised to the power of y
double sqrt(double x) - Calculates the square root of x
double exp(double x) - Calculates the value of e raised to the xth power

Other math functons
Trigonometric functions
Exponential functions
Floating point functions

Full list available under below link: 
https://en.wikipedia.org/wiki/C_mathematical_functions
*/

void ceil_should_calculate_the_ceiling_for_positive_and_negative_double_numbers(void)
{
    //arrange
    double pos = 2.5;
    double neg = -12.788887771; 

    //act
    double posCeil = ceil(pos); 
    double negCeil = ceil(neg); 

    //assert
    TEST_ASSERT_EQUAL_DOUBLE(3, posCeil); 
    TEST_ASSERT_EQUAL_DOUBLE(-12, negCeil); 
}

void floor_should_calculate_the_floor_for_positive_and_negative_double_numbers(void)
{
    //arrange
    double pos = 2.5;
    double neg = -12.788887771; 

    //act
    double posFloor = floor(pos); 
    double negFloor = floor(neg); 

    //assert
    TEST_ASSERT_EQUAL_DOUBLE(2, posFloor); 
    TEST_ASSERT_EQUAL_DOUBLE(-13, negFloor); 
}

void fabs_will_return_absolute_value_for_double_positive_and_negative_numbers(void)
{
    //arrange
    double pos = 2.5;
    double neg = -12.788887771; 

    //act
    double posAbs = fabs(pos); 
    double negAbs = fabs(neg); 

    //assert
    TEST_ASSERT_EQUAL_DOUBLE(pos, posAbs); 
    TEST_ASSERT_EQUAL_DOUBLE(-neg, negAbs); 
}

void log_will_return_logarithm_base_e_for_a_double_number(void)
{
    //arrange
    int num = 5; 
    double ex = exp(num); 

    //act
    double result = log(ex); 

    //assert
    TEST_ASSERT_EQUAL_DOUBLE(num, result); 
}

void pow_will_return_first_argument_power_second_argument(void)
{
    //arrange
    int num = 2; 
    int exp = 3; 

    //act
    double result = pow(num, exp); //casting of int to double

    //assert 
    TEST_ASSERT_EQUAL_DOUBLE(8, result);   
}

void sqrt_will_return_square_root_for_a_double_number(void)
{
    //arrange
    double number = 0.04;

    //act
    double result = sqrt(number); 

    //assert
    TEST_ASSERT_EQUAL_DOUBLE(0.2, result); 
}

void run_math_tests(void)
{
    UNITY_BEGIN();
    RUN_TEST(ceil_should_calculate_the_ceiling_for_positive_and_negative_double_numbers);
    RUN_TEST(floor_should_calculate_the_floor_for_positive_and_negative_double_numbers); 
    RUN_TEST(fabs_will_return_absolute_value_for_double_positive_and_negative_numbers); 
    RUN_TEST(log_will_return_logarithm_base_e_for_a_double_number); 
    RUN_TEST(pow_will_return_first_argument_power_second_argument); 
    RUN_TEST(sqrt_will_return_square_root_for_a_double_number); 
    UNITY_END(); 
}