#include "../unity/unity.h"

void swap_passing_value(int a, int b)
{
    int tmp = a;
    a = b; 
    b = tmp; 
}

void swap_passing_reference(int *a, int *b)
{
    int tmp = *a;
    *a = *b; 
    *b = tmp; 
}

void variable_swap_with_passing_value_should_not_perform_swap(void)
{
    //arrange
    int a = 1; 
    int b = 2; 

    //act
    swap_passing_value(a, b);

    //assert
    TEST_ASSERT_EQUAL_INT(a, 1);
    TEST_ASSERT_EQUAL_INT(b, 2);
}

void variable_swap_with_passing_reference_should_successfully_perform_the_swap(void)
{
    //arrange
    int a = 1; 
    int b = 2; 

    //act
    swap_passing_reference(&a, &b);

    //assert
    TEST_ASSERT_EQUAL_INT(a, 2);
    TEST_ASSERT_EQUAL_INT(b, 1);
}

void pointers_provide_dereferencing_ability_to_read_variables(void)
{
    //arrange
    int a = 1;
   
    //act
    int * ptrA = &a; 

    //assert
    TEST_ASSERT_EQUAL_INT(1, *ptrA); 
}

void pointers_provide_dereferencing_ability_to_write_to_variables(void)
{
    //arrange
    int a = 1;
   
    //act
    int * ptrA = &a; 
    *ptrA = 5; 

    //assert
    TEST_ASSERT_EQUAL_INT(5, a); 
}

int* get_address_of_passed_value_parameter(int a)
{
    return &a; 
}

void passing_variable_by_value_will_create_a_copy_var_in_memory(void)
{
    //arrange
    int a = 1; 
    int *ptrA = &a; 

    //act
    int *ptr = get_address_of_passed_value_parameter(a); 

    //assert
    TEST_ASSERT_NOT_EQUAL(ptrA, ptr); 

}

int** return_pointer(int** pointerToPointer)
{
    return pointerToPointer; 
}

//this is the intended usage when working with dynamic memory, as we want to keep the original reference to the memory allocated
//which then can be freed using the original pointer.
void passing_variable_by_pointer_to_reference_will_point_to_original_pointer(void)
{
    //arrange
    int a = 1; 
    int * ptrA = &a; 
    int ** ptrptrA = &ptrA; 

    //act
    int ** ptrReturned = return_pointer(ptrptrA); 


    //assert
    TEST_ASSERT_EQUAL(ptrptrA, ptrReturned);
    TEST_ASSERT_EQUAL(*ptrptrA, *ptrReturned); 
    TEST_ASSERT_EQUAL_INT(**ptrptrA, **ptrReturned); 
}

void incrementing_int_pointer_will_move_at_least_the_size_of_an_int(void)
{
    //arrange
    int array[] = { 1,  2 }; 

    //act
    int* ptrB = array + 1; 

    //assert
    TEST_ASSERT_EQUAL_INT(2, *ptrB); 
}


void incrementing_float_pointer_will_move_at_least_the_size_of_a_float(void)
{
    //arrange
    float array[] = { 1,  2 }; 

    //act
    float* ptrB = array + 1; 

    //assert
    TEST_ASSERT_EQUAL_FLOAT(2, *ptrB); 
}

int multiply_two_ints(int a, int b)
{
    return a * b; 
}

int divide_two_ints(int a, int b)
{
    return a / b; 
}

void function_pointers_provide_ability_to_call_functions_at_runtime(void)
{
    //arrange
    int a = 1; 

    int (*func)(int, int); //this means that it will accept 2 integers and return an integer (function signature)

    //act
    if(a)
    {
        func = &multiply_two_ints; 
    }
    else
    {
        func = &divide_two_ints; 
    }
    int result = func(2,3); 

    //assert
    TEST_ASSERT_EQUAL_INT(6, result); 
}

void run_pointer_tests(void)
{
    UNITY_BEGIN();

    RUN_TEST(variable_swap_with_passing_value_should_not_perform_swap); 
    RUN_TEST(variable_swap_with_passing_reference_should_successfully_perform_the_swap); 
    RUN_TEST(pointers_provide_dereferencing_ability_to_read_variables); 
    RUN_TEST(pointers_provide_dereferencing_ability_to_write_to_variables); 
    RUN_TEST(passing_variable_by_value_will_create_a_copy_var_in_memory); 
    RUN_TEST(passing_variable_by_pointer_to_reference_will_point_to_original_pointer); 
    RUN_TEST(incrementing_int_pointer_will_move_at_least_the_size_of_an_int); 
    RUN_TEST(incrementing_float_pointer_will_move_at_least_the_size_of_a_float); 
    RUN_TEST(function_pointers_provide_ability_to_call_functions_at_runtime);

    UNITY_END();
}