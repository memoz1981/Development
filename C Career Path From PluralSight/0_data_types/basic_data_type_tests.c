#include "../unity/unity.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

//for portable code we shouldn't assume a size - but use size of instead... 
void int_type_will_occupy_between_2_and_4_bytes_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    int max = INT_MAX; 
    int min = INT_MIN; 
    int size = sizeof(int); 

    //assert
    TEST_ASSERT_GREATER_OR_EQUAL_INT(2, size); 
    TEST_ASSERT_LESS_OR_EQUAL_INT(4, size);

    TEST_ASSERT_GREATER_OR_EQUAL(pow((double)2, 8 * size - 1) - 1, max); 
    TEST_ASSERT_LESS_OR_EQUAL(pow((double)2, 8 * size - 1), max);

    TEST_ASSERT_GREATER_OR_EQUAL(-pow((double)2, 8 * size - 1) - 1, min); 
    TEST_ASSERT_LESS_OR_EQUAL(-pow((double)2, 8 * size - 1) + 1, min);
}

void char_type_will_occupy_1_byte_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    int max = CHAR_MAX; 
    int min = CHAR_MIN; 
    int size = sizeof(char); 

    //assert
    TEST_ASSERT_EQUAL_INT(1, size); 
    TEST_ASSERT_EQUAL_INT(127, max); 
    TEST_ASSERT_EQUAL_INT(-128, min); 
}

void short_type_will_occupy_2_bytes_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    int max = SHRT_MAX; 
    int min = SHRT_MIN; 
    int size = sizeof(short); 

    //assert
    TEST_ASSERT_EQUAL_INT(2, size); 
    TEST_ASSERT_EQUAL_INT(32767, max); 
    TEST_ASSERT_EQUAL_INT(-32768, min); 
}

//other variants available like uint8, 16, 64 etc.
void uint32_type_will_occupy_2_to_4_bytes_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    unsigned int max = UINT_MAX; 
    int min = 0; 
    int size = sizeof(uint32_t); 

    //assert
    TEST_ASSERT_EQUAL_INT(4, size); 
    TEST_ASSERT_EQUAL(pow(2, 32) - 1, max); 
    TEST_ASSERT_EQUAL_INT(0, min); 
}

void long_type_will_occupy_4_to_8_bytes_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    int max = LONG_MAX; 
    int min = LONG_MIN; 
    int size = sizeof(long); 

    //assert
    TEST_ASSERT_EQUAL_INT(4, size); 
    TEST_ASSERT_EQUAL(pow(2, 8 * size - 1) - 1, max); 
    TEST_ASSERT_EQUAL(- pow(2, 8 * size - 1), min); 
}

void run_integer_type_tests()
{
    UNITY_BEGIN();
    RUN_TEST(int_type_will_occupy_between_2_and_4_bytes_and_will_have_min_max_values_accordingly);  
    RUN_TEST(char_type_will_occupy_1_byte_and_will_have_min_max_values_accordingly);  
    RUN_TEST(short_type_will_occupy_2_bytes_and_will_have_min_max_values_accordingly);  
    RUN_TEST(uint32_type_will_occupy_2_to_4_bytes_and_will_have_min_max_values_accordingly);  
    RUN_TEST(long_type_will_occupy_4_to_8_bytes_and_will_have_min_max_values_accordingly);  
    UNITY_END(); 

}

//for portable code we shouldn't assume a size - but use size of instead... 
void float_type_will_occupy_4_bytes_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    float max = FLT_MAX; 
    float min = FLT_MIN; 
    int size = sizeof(float); 

    //assert
    TEST_ASSERT_EQUAL_INT(4, size);
} 

//for portable code we shouldn't assume a size - but use size of instead... 
void double_type_will_occupy_8_bytes_and_will_have_min_max_values_accordingly(void)
{
    //arrange
    
    //act
    double max = DBL_MAX; 
    double min = DBL_MIN; 
    int size = sizeof(double); 

    //assert
    TEST_ASSERT_EQUAL_INT(8, size);
} 

void run_float_type_tests()
{
    UNITY_BEGIN();
    RUN_TEST(float_type_will_occupy_4_bytes_and_will_have_min_max_values_accordingly);  
    RUN_TEST(double_type_will_occupy_8_bytes_and_will_have_min_max_values_accordingly);  
    UNITY_END(); 

}

void implicit_conversions_may_be_used_from_int_to_float(void)
{
    //arrange - here the right side of the equation is actually int
    float f = 5; 

    //act

    //assert
    TEST_ASSERT_EQUAL_FLOAT(5, f); 
}

void explicit_conversion_is_required_to_cast_then_evaluate(void)
{
    //arrange
    float f1 = 5/2; // here right side is evaluated as int thus result is an int (2)
    float f2 = (float) 5 / 2; // here 5 is evaluated as float, then divided by 2, resulting in a float... 

    //act

    //assert
    TEST_ASSERT_EQUAL_FLOAT(2, f1); 
    TEST_ASSERT_EQUAL_FLOAT(2.5, f2); 
}

void run_data_type_conversion_tests()
{
    UNITY_BEGIN(); 
    RUN_TEST(implicit_conversions_may_be_used_from_int_to_float);
    RUN_TEST(explicit_conversion_is_required_to_cast_then_evaluate); 
    UNITY_END(); 
}

void run_basic_data_type_tests()
{
    run_integer_type_tests(); 
    run_float_type_tests(); 
    run_data_type_conversion_tests(); 
}