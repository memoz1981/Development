#include <stdlib.h>
#include "../unity/unity.h"

//this method doesn't test possibility of returning null when trying to allocate dynamic memory... 
void malloc_will_allocate_dynamic_memory_and_return_void_pointer_which_can_be_freed_using_free(void)
{
    //arrange

    //act
    int* pointerToMemory = (int*)malloc(4 * sizeof(int)); 

    //assert
    TEST_ASSERT_NOT_EQUAL(pointerToMemory, NULL); 
    
    free(pointerToMemory); 
}

void calloc_will_allocate_dynamic_memory_and_return_void_pointer_which_can_be_freed_using_free(void)
{
    //arrange

    //act
    int* pointerToMemory = (int*)calloc(4, sizeof(int)); 

    //assert
    TEST_ASSERT_NOT_EQUAL(pointerToMemory, NULL); 
    
    free(pointerToMemory);  
}

void realloc_will_allocate_dynamic_memory_and_return_void_pointer_which_can_be_freed_using_free(void)
{
    //arrange

    //act
    int* pointerToMemory = (int*)malloc(4 * sizeof(int)); 
    if(!pointerToMemory)
    {
        return; 
    }
    int* newPointer = (int*)realloc(pointerToMemory, 5); 
    //assert
    TEST_ASSERT_NOT_EQUAL(newPointer, NULL); 
    
    free(newPointer); 
}

void dynamic_memory_requests_will_return_a_null_pointer_if_memory_cannot_be_allocated(void)
{
    //arrange
    //act
    int* pointerToMemory = (int*)calloc(100000000, sizeof(int[100000000][10000000])); 

    //act
    

    //assert
    TEST_ASSERT_EQUAL(NULL, pointerToMemory); 
}

/*asked for clarification - skipping*/
void pointers_to_pointers_should_be_used_when_trying_to_dynamically_allocate_memory_in_a_separate_function(void)
{
    //arrange

    //act

    //assert
}

void dymamic_multi_dimensional_arrays_can_be_instantiated_as_pointers_to_arrays_using_malloc_as_array_data_type_and_will_have_row_major_layout(void)
{
    //arrange
    int (*arr)[2][3] = malloc(sizeof(int[2][3])); 
 
    //act
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            (*arr)[i][j] = 10 * i + j; 
        }
    }
    
    //assert
    TEST_ASSERT_NOT_EQUAL(NULL, arr);
   
    
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
        {
            int *ptr = arr[0][0] + 3*i + j; // this is to provide the row major layout, i.e. elements are ordered by rows, then columns...
            TEST_ASSERT_EQUAL_INT(10 * i + j, *ptr); 
        }
    }

    free(arr); 
}

void run_memory_management_tests(void)
{
    UNITY_BEGIN();

    RUN_TEST(malloc_will_allocate_dynamic_memory_and_return_void_pointer_which_can_be_freed_using_free); 
    RUN_TEST(calloc_will_allocate_dynamic_memory_and_return_void_pointer_which_can_be_freed_using_free);
    RUN_TEST(realloc_will_allocate_dynamic_memory_and_return_void_pointer_which_can_be_freed_using_free);
    RUN_TEST(dynamic_memory_requests_will_return_a_null_pointer_if_memory_cannot_be_allocated);
    RUN_TEST(dymamic_multi_dimensional_arrays_can_be_instantiated_as_pointers_to_arrays_using_malloc_as_array_data_type_and_will_have_row_major_layout);

    UNITY_END();
}