#include "../unity/unity.h"

/*Memory fragmentation will decrease the memory availability as well as have performance implications*/
/*Also the request itself is costly*/
void multiple_calls_to_allocate_memory_will_result_in_heap_fragmentation(void)
{

}

void memory_pools_provide_convenient_way_to_decrease_fragmentation_and_decrease_number_of_malloc_calls(void)
{
    TEST_ASSERT_EQUAL(1,1); 

}

void memory_managers_are_the_managers_of_memory_pools_and_interface_to_actual_memory_management(void)
{

}

void not_every_call_to_allocate_memory_will_end_up_in_actual_malloc_call(void)
{

}

void linked_lists_are_suitable_data_structure_to_implement_memory_pools_and_managers(void)
{

}


void run_memory_pool_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(memory_pools_provide_convenient_way_to_decrease_fragmentation_and_decrease_number_of_malloc_calls); 

    UNITY_END(); 
}