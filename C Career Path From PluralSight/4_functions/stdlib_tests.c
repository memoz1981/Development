#include "func_tests.h"
#include "../unity/unity.h"
#include <stdlib.h>
#include <string.h>

/*---------------------------------------SECTION CONVERSION FUNCTIONS-------------------------------------------------*/

//int atoi(const char* str)
void atoi_function_should_convert_string_to_integer_up_to_first_invalid_digit_character(void)
{
    //arrange
    const char * str = "111abcd00"; 

    //act
    int converted = atoi(str); 

    //assert
    TEST_ASSERT_EQUAL_INT(111, converted); 
}

void atoi_function_should_return_zero_if_string_is_not_a_valid_number(void)
{
    //arrange
    const char * str = "A113"; 

    //act
    int converted = atoi(str); 

    //assert
    TEST_ASSERT_EQUAL_INT(0, converted); 
}

//long int atol(const char* str
void atol_function_should_convert_string_to_long_integer_up_to_first_invalid_digit_character(void)
{
    //arrange
    const char * str = "1119989988abcd00"; 

    //act
    long converted = atol(str); 

    //assert
    TEST_ASSERT_EQUAL_INT64(1119989988, converted); 
}

//double atof(const char* str)
void atof_function_should_convert_string_to_double_up_to_first_invalid_digit_character(void)
{
    //arrange
    const char * str = "44.3abcd00"; 

    //act
    double converted = atof(str); 

    //assert
    TEST_ASSERT_EQUAL_DOUBLE(44.3, converted); 
}

/* 
double strtod(const char* str, char** outptr)
Converts the first number found within a C string to a double and sets the outptr to 
the rest of the string after conversion
*/
void strtod_function_should_return_first_found_double_in_a_string_and_return_pointer_to_the_remaining_string(void)
{
    //arrange
    const char * str = "99.555abcde"; 
    char * output; 

    //act
    double converted = strtod(str, &output); 
    
    //assert
    TEST_ASSERT_EQUAL_DOUBLE(99.555, converted);
    TEST_ASSERT_EQUAL(str + 6, output); 
}

/* 
long int strtol(const char* str, char** outptr, int base)
Converts the first number found within a C string to a long integer in the right base 
and sets the outptr to the rest of the string after the conversion
*/
void strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_10(void)
{
    //arrange
    const char * str = "99.555abcde"; 
    char * output; 

    //act
    long converted = strtol(str, &output, 10); 
    
    //assert
    TEST_ASSERT_EQUAL_INT64(99, converted);
    TEST_ASSERT_EQUAL(str + 2, output); 
}

void strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_2(void)
{
    //arrange
    const char * str = "10019abcde"; 
    char * output; 

    //act
    long converted = strtol(str, &output, 2); 
    
    //assert
    TEST_ASSERT_EQUAL_INT64(9, converted);
    TEST_ASSERT_EQUAL(str + 4, output); 
}

void strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_16(void)
{
    //arrange
    const char * str = "ABC1gabcde"; //note that lower case letters a-f also count as base 16 numbers 10-15
    char * output; 

    //act
    long converted = strtol(str, &output, 16); 
    
    //assert
    TEST_ASSERT_EQUAL_INT64(43969, converted);
    TEST_ASSERT_EQUAL(str + 4, output); 
}

void strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_16_for_negative_numbers(void)
{
    //arrange
    const char * str = "-ABC1gabcde"; //note that lower case letters a-f also count as base 16 numbers 10-15
    char * output; 

    //act
    long converted = strtol(str, &output, 16); 
    
    //assert
    TEST_ASSERT_EQUAL_INT64(-43969, converted);
    TEST_ASSERT_EQUAL(str + 5, output); 
}

/*
unsigned long int strtoul(const char* str, char** outptr, int base)
Converts the first number found within a C string to an unsigned long integer in the 
right base and sets the outptr to the rest of the string after the conversion.

IMPORTANT NOTE: When changing the string to start with minus, and having converted variable as long, seems that the function
returns -99 for some reason. Didn't spend much time on investigating this. 
*/
void strtoul_function_should_return_first_found_unsigned_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_10(void)
{
    //arrange
    const char * str = "99.555abcde"; 
    char * output; 

    //act
    unsigned long converted = strtoul(str, &output, 10); 
    
    //assert
    TEST_ASSERT_EQUAL_INT64(99, converted);
    TEST_ASSERT_EQUAL(str + 2, output); 
}


void run_conversion_function_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(atoi_function_should_convert_string_to_integer_up_to_first_invalid_digit_character); 
    RUN_TEST(atoi_function_should_return_zero_if_string_is_not_a_valid_number); 
    RUN_TEST(atol_function_should_convert_string_to_long_integer_up_to_first_invalid_digit_character); 
    RUN_TEST(atof_function_should_convert_string_to_double_up_to_first_invalid_digit_character); 
    RUN_TEST(strtod_function_should_return_first_found_double_in_a_string_and_return_pointer_to_the_remaining_string); 
    RUN_TEST(strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_10); 
    RUN_TEST(strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_2); 
    RUN_TEST(strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_16); 
    RUN_TEST(strtol_function_should_return_first_found_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_16_for_negative_numbers); 
    RUN_TEST(strtoul_function_should_return_first_found_unsigned_long_int_in_a_string_and_return_pointer_to_the_remaining_string_base_10); 

    UNITY_END(); 

}

/*---------------------------------------MEMORY MANAGEMENT FUNCTIONS-------------------------------------------------*/
/* These are covered under a separate section - basically these are malloc, calloc, realloc, free*/

/*---------------------------------------SECTION PROCESS/PROGRAM FUNCTIONS-------------------------------------------------*/

/*
void abort(void)
Causes program execution to terminate abnormally
*/
void abort_will_result_in_program_to_terminate_abnormally(void)
{
    TEST_IGNORE(); //impossible to test, as whole process will be terminated... 
    TEST_ASSERT_EQUAL(1,1);
    abort(); 
}

/*
int atexit(void (*foo) (void))
Specifies that the function “foo” will execute when the program terminates normally
*/

void conclude(void)
{
    printf("Successfully finished running tests..."); 
}

void atexit_keyword_will_result_in_program_to_execute_specified_function_when_normally_terminated(void)
{
    TEST_ASSERT_EQUAL(1,1);
    atexit(*conclude); 
}

/*
void exit(int status)
Causes program execution to terminate normally
*/
void exit_will_cause_program_to_terminate_normally(void)
{
    TEST_IGNORE(); //impossible to test, as whole process will be terminated... 
    TEST_ASSERT_EQUAL(1,1);
    exit(1000); 
}

/*
char* getenv(const char* key)
Returns the value of a process environment variable based on a given key
*/
void getenv_will_return_the_value_of_environment_variable(void)
{
    //arrange
    const char* key = "PATH";

    //act
    char * value = getenv(key); 
    int result = strlen(value); 

    //assert
    TEST_ASSERT_GREATER_THAN_INT32(0, result); 
}

/*
int system(const char* command)
Causes the host environment to execute the given command
*/
void system_will_execute_corresponding_command(void)
{
    TEST_IGNORE(); //ignored as we don't want to run any commands while running the tests...
    
    //arrange
    const char* command = "mspaint";

    //act
    int result = system(command); 

    //assert
    TEST_ASSERT_EQUAL_INT(result,0); 
}


void run_process_program_functions(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(abort_will_result_in_program_to_terminate_abnormally); 
    RUN_TEST(atexit_keyword_will_result_in_program_to_execute_specified_function_when_normally_terminated); 
    RUN_TEST(exit_will_cause_program_to_terminate_normally); 
    RUN_TEST(getenv_will_return_the_value_of_environment_variable); 
    RUN_TEST(system_will_execute_corresponding_command); 
    UNITY_END(); 
}


/*---------------------------------------ALGORITHMS-------------------------------------------------*/

/*
void* bsearch(
const void* item_to_find,
const void* array, 
size_t array_length,
size_t element_size,
int (*compare)(const void *, const void *)
)
Uses the binary search algorithm to locate a given item in a chunk of memory using the given 
comparison function
*/

int compare(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void bsearch_will_perform_binary_search_on_an_array_based_on_provided_compare_function(void)
{
    //arrange
    int array[] = {5,3,6,4,9,1,7,77,55,0}; 
    const int keyAvailable = 3; 
    const int keyNotAvailable = 100; 

    int * ptr = array; 

    //act
    int * resultAvailable = bsearch(&keyAvailable, array, 10, sizeof(int), compare); 
    int * resultUnavailable = bsearch(&keyNotAvailable, array, 10, sizeof(int), compare); 

    //assert
    TEST_ASSERT_EQUAL(ptr + 1, resultAvailable);
    TEST_ASSERT_EQUAL_INT(3, *resultAvailable);
    TEST_ASSERT_NULL(resultUnavailable);
}

/*
void qsort(
const void* array, 
size_t array_length,
size_t element_size,
int (*compare)(const void *, const void *)
)
Sorts the given array using the quicksort algorithm
*/

void qsort_will_sort_the_array_using_quick_sort_algoritm_based_on_given_compare_delegate_function(void)
{
    //arrange
    int array[] = {5,3,6,4,9,1,7,77,55,0}; 
    int * ptrBefore = array; 

    //act
    qsort(array, 10, sizeof(int), compare); 
    int * ptrAfter = array; 

    //assert
    TEST_ASSERT_EQUAL(ptrBefore, ptrAfter); 

    for(int i = 1; i<10; i++)
    {
        TEST_ASSERT_GREATER_OR_EQUAL_INT(array[i-1], array[i]);
    }
}


void run_algorithm_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(bsearch_will_perform_binary_search_on_an_array_based_on_provided_compare_function); 
    RUN_TEST(qsort_will_sort_the_array_using_quick_sort_algoritm_based_on_given_compare_delegate_function); 
    UNITY_END(); 
}

/*---------------------------------------MATH FUNCTIONS-------------------------------------------------*/

/*
int abs(int num)
long int labs(long int num)
Returns the absolute value of num
*/
void abs_returns_absolute_value_of_an_int(void)
{
    //arrange
    int num1 = -5; 
    int num2 = 15; 

    //act
    int res1 = abs(num1); 
    int res2 = abs(num2);

    //assert
    TEST_ASSERT_EQUAL_INT(5, res1);
    TEST_ASSERT_EQUAL_INT(15, res2); 
}

void labs_returns_absolute_value_of_an_long(void)
{
    //arrange
    long num1 = -5; 
    long num2 = 15; 

    //act
    long res1 = abs(num1); 
    long res2 = abs(num2);

    //assert
    TEST_ASSERT_EQUAL_INT64(5, res1);
    TEST_ASSERT_EQUAL_INT64(15, res2); 
}

/*
div_t div(int numerator, int denominator)
ldiv_t ldiv(long int numerator, long int denominator)
Divides the numerator by the denominator
*/

void div_should_divide_an_int_by_other(void)
{
    //arrange
    int num = 9; 
    int den = 4; 

    //act
    div_t result = div(num, den); 

    //assert
    TEST_ASSERT_EQUAL_INT(2, result.quot);
    TEST_ASSERT_EQUAL_INT(1, result.rem); 
}

void ldiv_should_divide_a_long_by_other(void)
{
    //arrange
    long num = 9; 
    long den = 4; 

    //act
    ldiv_t result = ldiv(num, den); 

    //assert
    TEST_ASSERT_EQUAL_INT(2, result.quot);
    TEST_ASSERT_EQUAL_INT(1, result.rem); 
}

/*
int rand(void)
Returns a random number between 0 and RAND_MAX where RAND_MAX is a macro defined by 
the stdlib.h header file.
*/

/*
void srand(unsigned int seed)
This function is used in tandem with the “rand” function. This function seeds the random number 
generator that is used.

*/

void rand_should_return_a_random_int_between_zero_and_rand_max(void)
{
    //arrange
    int min = 0; 
    int max = RAND_MAX; 
    int randomArray[10]; 

    //act
    srand(100); 
    for(int i=0; i<10; i++)
    {
        randomArray[i] = rand(); 
    }

    //assert
    for(int i=0; i<10; i++)
    {
        TEST_ASSERT_GREATER_OR_EQUAL_INT(min, randomArray[i]); 
        TEST_ASSERT_LESS_OR_EQUAL_INT(max, randomArray[i]); 
    }
}

void run_stdlib_math_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(abs_returns_absolute_value_of_an_int); 
    RUN_TEST(labs_returns_absolute_value_of_an_long); 
    RUN_TEST(div_should_divide_an_int_by_other); 
    RUN_TEST(ldiv_should_divide_a_long_by_other); 
    RUN_TEST(rand_should_return_a_random_int_between_zero_and_rand_max); 
    UNITY_END(); 
}

/*---------------------------------------SECTION Multi-byte Character Utility FUNCTIONS-------------------------------------------------*/
/*
These include below functions, didn'd add any specific tests for these. May be investigated if required. rare usage: 

1) size_t mbstowcs(wchar_t* pwcs, const char* str, size_t max)
Converts the multi-byte string “str” to the wide character string “pwcs”. The ”max” 
parameter represents the max number of characters to convert.

2) int mbtowc(wchar_t* pwc, const char* str, size_t max)
Converts one multi-byte character to a wide character

3) int mblen(const char* str, size_t max)
Returns the length of the multi-byte character given the C string “str”. The ”max” 
parameter is the max number of bytes to be checked.

4) size_t wcstombs(char* str, const wchar_t* pwcs, size_t max)
Converts an array of wide characters to multibyte characters

5) int wctomb(char* str, wchar_t* wide_char, size_t max)
Converts a wide character to a multi-byte character

*/


/*---------------------------------------API-------------------------------------------------*/
void run_stdlib_tests(void)
{
    run_conversion_function_tests(); 
    run_process_program_functions(); 
    run_algorithm_tests(); 
    run_stdlib_math_tests(); 
}