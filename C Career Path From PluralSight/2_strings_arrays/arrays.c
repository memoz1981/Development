#include "../unity/unity.h"
#include <stdio.h>

void one_dimensional_arrays_can_be_declared_with_or_without_defining_the_size(void)
{
    //arrange
    int array1[] = {3, 4, 5}; 
    int array2[3];

    //act
    array2[0] = 3; 
    array2[1] = 4; 
    array2[2] = 5;

    //assert
    for(int i = 0; i < 3; i++)
    {
        TEST_ASSERT_EQUAL_INT(array1[i], array2[i]); //values should match as declared above
        TEST_ASSERT_NOT_EQUAL(&array1[i], &array2[i]); //addresses should not match, as these are totally different memory address/slots

    }
}

void char_array_last_element_should_be_null_thus_the_capacity_of_char_array_is_size_minus_one(void)
{
    //arrange
    char array[] = "Hello"; 

    //act

    //assert
    TEST_ASSERT_EQUAL_INT(6, sizeof(array));
}

void arrays_cannot_be_re_initialized(void)
{
    TEST_IGNORE(); 
    //arrange
    int arrayOriginal[] = {1, 3, 5}; 
    int* pointerToOriginalArray = arrayOriginal; 

    //act
    // compiler will not allow to re-initialize an array...  

    //assert
}

void accessing_indexes_beyond_array_range_should_not_throw_any_compiler_errors_but_will_result_in_undefined_behaviour()
{
    TEST_IGNORE(); 
    //arrange
    int array[3] = {1, 2, 3}; 

    //act
    int outOfRangeElement = array[3]; 

    //assert
    //no compiler issues
}

//this is called - arrays decay to pointers
void arrays_can_be_passed_to_functions_having_pointer_parameter(void)
{
    //arrange
    int array[] = {10,12,13}; 

    //act
    int result = test_function(array);

    //assert
    TEST_ASSERT_EQUAL_INT(10, result); 
}

int test_function(int* ptr)
{
    return ptr[0];
}

void using_array_name_is_equivalent_to_the_memory_addres_of_first_element(void)
{
    //arrange
    int array[] = {1,2,3}; 

    //act

    //assert
    TEST_ASSERT_EQUAL(array, &array[0]); 
}

void arrays_reside_on_contiguous_memory_slots(void)
{
    //arrange
    int array[] = {1,2,3,4,5}; 

    //act

    //assert
    for(int i = 1; i < 5; i++)
    {
        int diff = &array[i] - &array[i-1];  
        TEST_ASSERT_EQUAL_INT(1, diff);
    }
}

void array_elements_can_be_accessed_with_O_1_complexity_knowing_array_address_and_index_of_element(void)
{
    //arrange
    int array[10]; 

    //act
    for(int i=0; i<10; i++)
    {
        array[i] = i; 
    }

    int* pointer = array; 

    //assert
    for(int i = 0; i<10; i++)
    {
        int* pointerNew = pointer + i; 
        TEST_ASSERT_EQUAL_INT(*pointerNew, array[i]);   
    }
}

void multi_dimensional_arrays_size_is_required_for_second_and_following_dimensions_not_mandatory_for_first_dimension(void)
{
    //arrange
    int array[][2] = {{1,2}, {3,4}}; 

    //act

    //assert
    TEST_ASSERT_EQUAL_INT(1, array[0][0]); 
    TEST_ASSERT_EQUAL_INT(2, array[0][1]); 
    TEST_ASSERT_EQUAL_INT(3, array[1][0]); 
    TEST_ASSERT_EQUAL_INT(4, array[1][1]); 
}

void multi_dimensional_arrays_cover_contiguous_memory(void)
{
   //arrange
    int array[][2] = {{1,2}, {3,4}}; 

    //act

    //assert
    TEST_ASSERT_EQUAL_INT(3, &array[1][1] - &array[0][0]); 
}

/*normally this would require some kind of validation and/or limiting on the passed size - 
as this would have potential of requiring 
large memory - one option would be to go with dynamic arrays over the lifetime of which the programmer have the control*/
void varialble_length_arrays_can_be_instantiated_by_passing_size_to_a_function(void)
{
    //arrange
    int size = 2; 

    //act
    int array[size];
    for(int i = 0; i < size; i++)
    {
        array[i] = i + 1; 
    }

    //assert
    for(int i = 0; i < size; i++)
    {
        TEST_ASSERT_EQUAL_INT(i+1, array[i]); 
    }
}

void run_array_tests(void)
{
    UNITY_BEGIN();

    RUN_TEST(one_dimensional_arrays_can_be_declared_with_or_without_defining_the_size); 
    RUN_TEST(char_array_last_element_should_be_null_thus_the_capacity_of_char_array_is_size_minus_one); 
    RUN_TEST(arrays_cannot_be_re_initialized); 
    RUN_TEST(accessing_indexes_beyond_array_range_should_not_throw_any_compiler_errors_but_will_result_in_undefined_behaviour); 
    RUN_TEST(arrays_can_be_passed_to_functions_having_pointer_parameter); 
    RUN_TEST(using_array_name_is_equivalent_to_the_memory_addres_of_first_element); 
    RUN_TEST(arrays_reside_on_contiguous_memory_slots); 
    RUN_TEST(array_elements_can_be_accessed_with_O_1_complexity_knowing_array_address_and_index_of_element); 
    RUN_TEST(multi_dimensional_arrays_size_is_required_for_second_and_following_dimensions_not_mandatory_for_first_dimension); 
    RUN_TEST(multi_dimensional_arrays_cover_contiguous_memory); 
    RUN_TEST(varialble_length_arrays_can_be_instantiated_by_passing_size_to_a_function); 

    UNITY_END();
}