#include "0_data_types/basic_data_type_tests.h"
#include "0_data_types/enumerated_data_type_tests.h"
#include "0_data_types/void_type_tests.h"
#include "0_data_types/derived_data_type_tests.h"

#include "1_program_flow/conditional_logic_tests.h"
#include "1_program_flow/iterators.h"

#include "2_strings_arrays/string_tests.h"
#include "2_strings_arrays/arrays.h"

#include "3_pointers/pointer_tests.h"

#include "4_functions/func_tests.h"

#include "5_structures/struct_tests.h"

#include "6_memory_management/memory_management_tests.h"

#include "7_cpp/cpp_tests.h"

#include <stdio.h>

int main()
{
    printf("Running tests for basic data types\n");
    run_basic_data_type_tests(); 
    printf("Finished running tests for basic data types\n\n\n\n\n");

    printf("Running tests for enumerated data types\n");
    run_enum_tests(); 
    printf("Finished running tests for enumerated data types\n\n\n\n\n");
    
    printf("Running tests for conditional statements\n");
    run_conditional_logic_tests(); 
    printf("Finished running tests for conditional statements\n\n\n\n\n");

    printf("Running tests for iterators\n");
    run_conditional_logic_tests(); 
    printf("Finished running tests for iterators\n\n\n\n\n");
    
    printf("Running tests for strings\n");
    run_string_tests(); 
    printf("Finished running tests for strings\n\n\n\n\n");

    printf("Running array tests\n");
    run_array_tests(); 
    printf("Finished running array tests\n\n\n\n\n");

    printf("Running pointer tests\n");
    run_pointer_tests(); 
    printf("Finished running pointer tests\n\n\n\n\n");

    printf("Running functions tests\n");
    run_function_tests(); 
    printf("Finished running functions tests\n\n\n\n\n");

    printf("Running functions - stdlib tests\n");
    run_stdlib_tests(); 
    printf("Finished running functions - stdlib tests\n\n\n\n\n");

    printf("Running functions - stdio tests\n");
    run_stdio_tests(); 
    printf("Finished running functions - stdio tests\n\n\n\n\n");

    printf("Running functions - stdarg tests\n");
    run_stdarg_tests(); 
    printf("Finished running functions - stdarg tests\n\n\n\n\n");

    printf("Running functions - time tests\n");
    run_time_tests(); 
    printf("Finished running functions - time tests\n\n\n\n\n");

    printf("Running functions - locale tests\n");
    run_locale_tests(); 
    printf("Finished running functions - locale tests\n\n\n\n\n");

    printf("Running functions - math tests\n");
    run_math_tests(); 
    printf("Finished running functions - math tests\n\n\n\n\n");

    printf("Running functions - string tests\n");
    run_string_function_tests(); 
    printf("Finished running functions - string tests\n\n\n\n\n");

    printf("Running functions - ctype tests\n");
    run_ctype_tests(); 
    printf("Finished running functions - ctype tests\n\n\n\n\n");

    printf("Running functions - errno tests\n");
    run_errno_tests(); 
    printf("Finished running functions - errno tests\n\n\n\n\n");

    printf("Running functions - setjump tests\n");
    run_setjump_tests(); 
    printf("Finished running functions - setjump tests\n\n\n\n\n");

    printf("Running functions - assert tests\n");
    run_assert_tests(); 
    printf("Finished running functions - assert tests\n\n\n\n\n");

    printf("Running functions - signal tests\n");
    run_signal_tests(); 
    printf("Finished running functions - signal tests\n\n\n\n\n");

    printf("Running structs tests\n");
    run_struct_tests(); 
    printf("Finished running structs tests\n\n\n\n\n");

    printf("Running memory management tests\n");
    run_memory_management_tests(); 
    printf("Finished running memory management tests\n\n\n\n\n");

    printf("Running preprocessor tests\n");
    run_cpp_tests(); 
    printf("Finished running preprocessor tests\n\n\n\n\n");

    return 0; 
}