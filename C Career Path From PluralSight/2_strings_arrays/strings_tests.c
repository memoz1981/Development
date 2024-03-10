#include <string.h>
#include "../unity/unity.h"

void strings_end_with_null_character_default_behaviour(void)
{
    //arrange
    char name[] = "Mehdi"; 
    char* namePointer = name; 
    
    //act

    //assert
    TEST_ASSERT_EQUAL_CHAR('M', *namePointer); 

    namePointer ++;
    TEST_ASSERT_EQUAL_CHAR('e', *namePointer); 

    namePointer ++;
    TEST_ASSERT_EQUAL_CHAR('h', *namePointer); 

    namePointer ++;
    TEST_ASSERT_EQUAL_CHAR('d', *namePointer); 
    
    namePointer ++;
    TEST_ASSERT_EQUAL_CHAR('i', *namePointer); 

    namePointer ++;
    TEST_ASSERT_EQUAL_CHAR('\0', *namePointer); 
}

/* Well - need to identify if this may under any circumstances result in unexpected behaviour - since the mutation is within the string index 
- how is it different that mutating a char, or an int etc.? need a bit of research on this
On the other hand, the sole purpose of this test is to demonstrate that the string that's read - stops at the first null character...*/
void strings_end_with_null_character_string_mutation_within_string_index(void)
{
    //arrange
    char name[10] = "Mehdi"; 
    char* namePointer = name; 
    
    //act
    namePointer++;
    namePointer++;
    namePointer++;
    *namePointer = '\0';

    //assert
    TEST_ASSERT_EQUAL_STRING("Meh", name); 
}

/* Same as above - don't expect any unexpected behaviour. Need to check. */
void strings_end_with_null_character_string_mutation_within_string_index_new(void)
{
    //arrange
    char name[10] = "Mehdi"; 
    char* namePointer = name; 
    
    //act
    namePointer++;
    namePointer++;
    namePointer++;
    namePointer++;
    namePointer++;

    *namePointer = 'm';
    namePointer++;
    *namePointer = '\0';

    //assert
    TEST_ASSERT_EQUAL_STRING("Mehdim", name); 
}


void trying_to_mutate_strings_beyond_index_will_result_in_unexpected_behaviour_ignored(void)
{
    TEST_IGNORE(); 

    //arrange
    char name[10] = "Mehdi"; 
    char* namePointer = name; 
    
    //act
    namePointer++;
    namePointer++;
    namePointer++;
    namePointer++;

    namePointer++;
    *namePointer = '1';
     namePointer++;
    *namePointer = '2';
     namePointer++;
    *namePointer = '3';
     namePointer++;
    *namePointer = '4';
     namePointer++;
    *namePointer = '5';
    namePointer++;
    *namePointer = '6';
    namePointer++;
    *namePointer = '\0';

    //assert
    TEST_ASSERT_EQUAL_STRING("Mehdi123456", name); 
}

void string_length_size_expected_behaviour(void)
{
    //arrange
    char name[10] = "Mehdi"; 
    
    //act
    
    //assert
    TEST_ASSERT_EQUAL_INT(5, strlen(name)); 
    TEST_ASSERT_EQUAL_INT(10, sizeof(name)); 
}

/* Normally this will result in unexpected behavious - as anything beyond index 10 is out of control of the name variable... The sole purpose of this test is to 
demonstate that the length function just calculates till the next null operator */
void string_length_size_unexpected_behaviour_ignored(void)
{
    TEST_IGNORE(); 
    //arrange
    char name[10] = "Mehdi"; 
    char* namePointer = name; 

    namePointer++;
    namePointer++;
    namePointer++;
    namePointer++;

    namePointer++;
    *namePointer = '1';
     namePointer++;
    *namePointer = '2';
     namePointer++;
    *namePointer = '3';
     namePointer++;
    *namePointer = '4';
     namePointer++;
    *namePointer = '5';
    namePointer++;
    *namePointer = '6';
    namePointer++;
    *namePointer = '\0';
    
    //act
    
    //assert
    TEST_ASSERT_EQUAL_INT(11, strlen(name)); 
    TEST_ASSERT_EQUAL_INT(10, sizeof(name)); 
}

/*Important Notes:
1) TEST_ASSERT_EQUAL(nameSource, nameDest) will return false here, as both arrays are (may be ) different
2) str copy will copy only Mehdi part - it will not copy rest 5 indices (4 actually considering the null character)
- which means that first 6 characters of nameSource and nameDest are guaranteed to be same - which is proven by TEST_ASSERT_EQUAL_STRING
and rest aren't - they are either null character or any garbage that's remaining in memory.  
*/
void str_copy_when_sizes_are_equal(void)
{
    //arrange
    char nameSource[10] = "Mehdi";
    char nameDest[10]; 

    //act
    strcpy(nameDest, nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING(nameSource, nameDest); 
}

/*Expected to behave same as when they are equal*/
void str_copy_when_destination_size_is_larger(void)
{
    //arrange
    char nameSource[10] = "Mehdi";
    char nameDest[20]; 

    //act
    strcpy(nameDest, nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING(nameSource, nameDest); 
}

/*Expected to behave same as when they are equal*/
void str_copy_when_source_size_is_larger_but_still_string_is_within_the_dest_size_including_null_char(void)
{
    //arrange
    char nameSource[10] = "Mehdi";
    char nameDest[6]; 

    //act
    strcpy(nameDest, nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING(nameSource, nameDest); 
}

/*This makes the strcpy unsafe - this will overflow the dest string and write data outside of bounds of the dest string */
void str_copy_when_copied_string_is_longer_than_dest_str_size_unexpected_behaviour_ignored(void)
{
    TEST_IGNORE(); 
    //arrange
    char nameSource[10] = "Mehdi";
    char nameDest[2]; 

    //act
    strcpy(nameDest, nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING(nameSource, nameDest); 
}

void str_concat_when_within_bounds(void)
{
    //arrange
    char name[20] = "My name";

    //act
    strcat(name, " is Mehdi"); 

    //assert
    TEST_ASSERT_EQUAL_STRING("My name is Mehdi", name); 
}

/* This makes the strcopy unsafe - i.e. it may overflow the bounds of the original array, which will end up in unexpected behaviour. 
On the other hand, we expect the test to pass till we declare another variable, which may grab the memory slots used by name. 
*/
void str_concat_when_outside_of_bounds_unsafe_code_will_cause_stack_overflow_test_ignored(void)
{
    TEST_IGNORE();
    //arrange
    char name[10] = "My name";

    //act
    strcat(name, " is Mehdi"); 

    //assert
    ("My name is Mehdi", name); 
}

void str_copy_s_when_dest_can_accept_string_size(void)
{
    //arrange
    char nameSource[10] = "Mehdi";
    char nameDest[6]; 

    //act
    strcpy_s(nameDest, sizeof(nameDest), nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING(nameSource, nameDest); 
}

/* This will throw an exception (EINVAL), based on the validation sizeInBytes should be greater than strlen(nameSource) */
void str_copy_s_specified_size_is_less_than_source_length_thows_parameter_validation_error_ignored(void)
{
    TEST_IGNORE(); 

    //arrange
    printf("running the test...\n"); 
    char nameSource[20] = "Mehdi123456";
    char nameDest[30]; 

    //act
    strcpy_s(nameDest, 6, nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING("Mehdi", nameDest); 
    printf("Finished running\n"); 
}

/* Although strcopy_s is safe, explicitly asking it to overwrite buffer, will actually do, so below is unexpected behaviuor/unsafe... */
/* I'm not sure why they wanted to include separate length parameter, as it could have been defaulted to the buffer length (or minus one, whatever)*/
/* Perhaps the aim also was to have a substring function */
void str_copy_s_specified_size_is_more_than_dest_length_ends_up_in_buffer_overflow_ignored(void)
{
    TEST_IGNORE(); 
    //arrange
    char nameSource[20] = "Mehdi123456";
    char nameDest[6]; 

    //act
    strcpy_s(nameDest, 40, nameSource); 

    //assert
    TEST_ASSERT_EQUAL_STRING(nameSource, nameDest); 
}

void str_cat_s_default_behaviour(void)
{
    //arrange
    char name[11]={ 'I', ' ', 'a', 'm', ' ' };

    //act
    strcat_s(name, sizeof(name), "Mehdi");

    //assert
    TEST_ASSERT_EQUAL_STRING("I am Mehdi", name); 
}

/* Need to check if anything wrong with this - I don't see any issue as long as within the limits. On the other hand, of course you would not use as it. */
void str_cat_s_buffer_size_specied_more_than_available_results_successful_copy(void)
{
    //arrange
    char name[11]={ 'I', ' ', 'a', 'm', ' ' };

    //act
    strcat_s(name, sizeof(name) + 1, "Mehdi");

    //assert
    TEST_ASSERT_EQUAL_STRING("I am Mehdi", name); 
}

void str_cat_s_buffer_size_specied_less_than_available_results_in_error_ignored(void)
{
    TEST_IGNORE(); 
    //arrange
    char name[11]={ 'I', ' ', 'a', 'm', ' ' };

    //act
    strcat_s(name, sizeof(name) - 1, "Mehdi");

    //assert
    TEST_ASSERT_EQUAL_STRING("I am Mehdi", name); 
}

/* UTF encoded characters may occupy more space than a byte */
void special_characters_may_end_up_in_longer_length_than_number_of_characters(void)
{
    //arrange
    char name[20]="ƏĞÖÜŞ"; 

    //act
    int len = strlen(name); 

    //assert
    TEST_ASSERT_GREATER_OR_EQUAL_INT32(6, len); 
}

void str_compare_should_return_zero_if_strings_are_identical(void)
{
    //arrange
    char name1[10] = "Mehdi";
    char name2[20] = "Mehdi";

    //act
    int areSame = strcmp(name1, name2); 

    //assert
    TEST_ASSERT_EQUAL_INT(areSame, 0); 
}

void run_string_tests(void)
{
    UNITY_BEGIN();
    RUN_TEST(strings_end_with_null_character_default_behaviour);
    RUN_TEST(strings_end_with_null_character_string_mutation_within_string_index);
    RUN_TEST(strings_end_with_null_character_string_mutation_within_string_index_new);
    RUN_TEST(trying_to_mutate_strings_beyond_index_will_result_in_unexpected_behaviour_ignored);

    RUN_TEST(string_length_size_expected_behaviour);
    RUN_TEST(string_length_size_unexpected_behaviour_ignored);

    RUN_TEST(str_copy_when_sizes_are_equal);
    RUN_TEST(str_copy_when_destination_size_is_larger);
    RUN_TEST(str_copy_when_source_size_is_larger_but_still_string_is_within_the_dest_size_including_null_char);
    RUN_TEST(str_copy_when_copied_string_is_longer_than_dest_str_size_unexpected_behaviour_ignored);

    RUN_TEST(str_concat_when_within_bounds);
    RUN_TEST(str_concat_when_outside_of_bounds_unsafe_code_will_cause_stack_overflow_test_ignored); //ignored

    RUN_TEST(str_copy_s_when_dest_can_accept_string_size);
    RUN_TEST(str_copy_s_specified_size_is_less_than_source_length_thows_parameter_validation_error_ignored);
    RUN_TEST(str_copy_s_specified_size_is_more_than_dest_length_ends_up_in_buffer_overflow_ignored);

    RUN_TEST(str_cat_s_default_behaviour);
    RUN_TEST(str_cat_s_buffer_size_specied_more_than_available_results_successful_copy);
    RUN_TEST(str_cat_s_buffer_size_specied_less_than_available_results_in_error_ignored);
    RUN_TEST(special_characters_may_end_up_in_longer_length_than_number_of_characters); 

    RUN_TEST(str_compare_should_return_zero_if_strings_are_identical); 

    UNITY_END();
}