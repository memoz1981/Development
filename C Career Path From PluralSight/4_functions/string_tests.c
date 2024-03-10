#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../helper_functions/helper.h"

/*
-----------------------------String Manipulation Functions-------------------------------------

char* strcpy(char* destination, const char* source) - Copies a given source string, including 
the null terminator to the destination string.
char* strncpy(char* destination, const char* source, size_t n) - Copies “n” characters from the source 
string to the destination string
char* strcat(char* destination, const char* source) - Appends the source string to the end of 
the destination string
char* strncat(char* destination, const char* source, size_t n) - Appends “n” characters from the source 
string on to the end of the destination string
size_t strxfrm(char* destination, const char* source, size_t n) - Transforms up to “n” characters from the 
source string into the current locale and puts them in the destination string
char* strtok(char* str, const char* delimiter) - Tokenizes the given string using the given 
delimiter

-----------------------------String Comparison Functions-------------------------------------

int strcmp(const char* str1, const char* str2) - Compares two strings for equality and returns zero 
if the strings are equal
int strncmp(const char* str1, const char* str2, size_t n) - Compares two strings for equality up to a max of 
“n” characters and returns zero if the strings are equal
int strcoll(const char* str1, const char* str2) - Compares two strings using the locale defined by 
the LC_COLLATE macro variable and returns zero if the strings are equal

-----------------------------String Metadata Functions-------------------------------------

size_t strlen(const char* str) - Returns the length of the string not including the 
null terminator character
char* strchr(const char* str, int character) - Finds the first occurrence of the given character 
within the given string
char* strrchr(const char* str, int character) - Finds the last occurrence of the given character 
within the given string
size_t strspn(const char* str1, const char* str2) - Returns the count of matching characters from the 
beginning of str1 that match characters in str2
size_t strcspn(const char* str1, const char* str2) - Returns the count of non-matching characters from 
the beginning of str1 when compared with str2
char* strpbrk(const char* str1, const char* str2) - Finds the first character in str1 that matches any 
character in str2 not including the null terminator character
char* strstr(const char* str1, const char* str2) - Finds and returns a pointer to the first occurrence 
of the substring str2 within str1 not counting null terminator characters

-----------------------------Error Handling Functions-------------------------------------

char* strerror(int error_number) - Works with the errno.h header file to print the error 
string associated with a given library or system error 
defined by the errno thread-local global variable.

-----------------------------Memory Functions-------------------------------------

void* memset(void* mem, int character, size_t n) - Given a pointer to some memory, a character 
and a size in bytes, memset fills the memory with the value of the given character up to the 
given size
void* memcpy(void* dest, const void* source, size_t n) - Copies “n” bytes in memory from the source to 
the destination. Assumes that these two chunks of memory do not overlap
void* memmove(void* dest, const void* source, size_t n) - Does the same thing as memcpy except the 
two chunks of memory can overlap
int memcmp(const void* mem1, const void* mem2, size_t n) - Compares up to “n” bytes of two chunks of 
memory and returns zero if they are equal
void* memchr(const void* mem, int character, size_t n) - Finds the first occurrence of the given 
character within the first “n” bytes of the given block of memory

*/

/*----------------------------------String Manipulation Functions ---------------------------------------*/

//the pros of this method is - it will copy the null terminating character as well
//the cons of this method is - it's unsafe, careful consideration is required. 
void strcpy_will_copy_source_string_to_destination_string_including_null_terminator(void)
{
    //arrange
    char source[10]="Source"; 
    char destination[20] = "Destination"; 

    //act
    strcpy(destination, source); 

    //assert
    int result = strcmp("Source", destination); 
    TEST_ASSERT_EQUAL_INT(0, result); 
    TEST_ASSERT_EQUAL_CHAR('t', destination[7]); 
}

void strcpy_will_cause_overflow_if_destination_string_length_is_less_than_source(void)
{
    //arrange
    char* source="veryLongSource"; 
    char destination[12] = "destination"; 

    //act
    strcpy(destination, source); 

    //assert
    int result = strcmp("veryLongSource", destination); 
    TEST_ASSERT_EQUAL_INT(0, result); 
}

//the pros of this method is - size is specified, in terms of that it's safer than strcpy
//the cons of this method is - strangely it doesn't copy the null terminating character
void strncpy_will_copy_source_string_to_destination_string_except_for_null_terminator(void)
{
    //arrange
    char source[10]="Source"; 
    char destination1[20] = "Destination"; 
    char destination2[20] = "Destination"; 

    //act
    strncpy(destination1, source, 6); //here only the chars will be moved
    strncpy(destination2, source, 7); //the word and null terminating character will be moved

    //assert
    int result1 = strcmp("Sourceation", destination1); 
    int result2 = strcmp("Source", destination2); 
    TEST_ASSERT_EQUAL_INT(0, result1); 
    TEST_ASSERT_EQUAL_INT(0, result2); 
}

//the pros of this method is - it will copy the null terminating character as well
//the cons of this method is - it's unsafe, careful consideration is required. 
void strcat_will_append_source_string_to_the_end_of_destination_string_including_null_terminator(void)
{
    //arrange
    char source[10]="Source"; 
    char destination[30] = "Destination"; 

    //act
    strcat(destination, source); 

    //assert
    int result = strcmp("DestinationSource", destination); 
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void strcat_will_cause_overflow_if_destination_length_is_not_enough_to_accommodate_source_and_null_terminator(void)
{
    //arrange
    char source[10]="Source"; 
    char destination[15] = "Destination"; 

    //act
    strcat(destination, source); 

    //assert
    int result = strcmp("DestinationSource", destination); 
    TEST_ASSERT_EQUAL_INT(0, result); 
}

//the pros of this method is - size is specified, in terms of that it's safer than strcat
void strncpy_will_append_source_string_to_the_end_of_destination_string_including_the_null_terminator(void)
{
    //arrange
    char source[10]="source"; 
    char destination1[20] = "0123456789abcdefghg"; 
    char destination2[20] = "0123456789abcdefghg"; 
    destination1[10]='\0'; 
    destination2[10]='\0'; 

    //act
    strncat(destination1, source, 5); //here only the chars will be appended
    strncat(destination2, source, 7); //the word and null terminating character will be appended

    //assert
    int result1 = strcmp("0123456789sourc", destination1); 
    int result2 = strcmp("0123456789source", destination2); 
    TEST_ASSERT_EQUAL_INT(0, result1); 
    TEST_ASSERT_EQUAL_INT(0, result2); 
}

void strtok_will_split_the_string_to_tokens_based_on_a_delimiter(void)
{
    //arrange
    char destination[100];
    memset(destination, '\0', 100); 

    char text[] = "This_is_snake_case.";
    char* delimiter = "_";

    //act
    char* token = strtok(text, delimiter);

    while(token != NULL) {
        printf("Next Token: %s\n", token);
        strcat(destination, token); 

        // Pass a NULL pointer in order to keep parsing rest of the tokens from the original string.
        token = strtok(NULL, delimiter); 
    }

    //assert
    int result = strcmp("Thisissnakecase.", destination);
    TEST_ASSERT_EQUAL_INT(0, result); 
}

/*---------------------------------- String Comparison Functions ---------------------------------------*/
void strncmp_will_compare_two_strings_up_to_a_specified_size(void)
{
    //arrange
    char* str1 = "Source1 string";
    char* str2 = "Source2 string"; 

    //act
    int resultWithNormalCompare = strcmp(str1, str2); 
    int resultWithSizedCompare = strncmp(str1, str2, 6); 

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, resultWithNormalCompare); 
    TEST_ASSERT_EQUAL_INT(0, resultWithSizedCompare); 
}

/*----------------------------------String Metadata Functions ---------------------------------------*/

void strlen_will_return_the_size_of_string_till_null_terminating_character(void)
{
    //arrange
    char text[100] = "text1"; 

    //act
    int len = strlen(text); 

    //assert
    TEST_ASSERT_EQUAL_INT(5, len); 
}

void strlen_may_overflow_if_null_terminating_character_is_not_within_array_bounds(void)
{
    //arrange
    char text[6] = "text1"; 
    text[5]='2';

    //act
    int len = strlen(text); 

    //assert
    TEST_ASSERT_GREATER_THAN_INT(6, len); 
}

void strchr_will_return_pointer_to_to_the_first_occurence_of_character_in_second_argument(void)
{
    //arrange
    char* source = "Hello world!!!"; 
    char ch = 'l'; 

    //act
    char* substring = strchr(source, ch); 

    //assert
    int result = strcmp("llo world!!!", substring);
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void strchr_will_return_null_pointer_if_character_not_found(void)
{
    //arrange
    char* source = "Hello world!!!"; 
    char ch = 'z'; 

    //act
    char* substring = strchr(source, ch); 

    //assert
    TEST_ASSERT_EQUAL(NULL, substring); 
}

void strstr_will_return_pointer_to_to_the_first_occurence_of_string_in_second_argument(void)
{
    //arrange
    char* source = "Hello world!!!"; 
    char* ch = "ll"; 

    //act
    char* substring = strstr(source, ch); 

    //assert
    int result = strcmp("llo world!!!", substring);
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void strstr_will_return_null_pointer_if_string_not_found(void)
{
    //arrange
    char* source = "Hello world!!!"; 
    char* ch = "z"; 

    //act
    char* substring = strstr(source, ch); 

    //assert
    TEST_ASSERT_EQUAL(NULL, substring); 
}

void strspn_will_return_number_of_characters_in_the_beginning_of_first_string_matching_second_string(void)
{
    //arrange
    char* str1 = "Hello World !!!"; 
    char* str2 = "Hell Mars !!!"; 
    char* str3 = "World record"; 

    //act
    int result1 = strspn(str1, str2); 
    int result2 = strspn(str1, str3); 

    //assert
    TEST_ASSERT_EQUAL_INT(4, result1);
    TEST_ASSERT_EQUAL_INT(0, result2); 
}

void strcspn_will_return_number_of_characters_in_the_beginning_of_first_string_not_matching_any_of_chars_in_second(void)
{
    //arrange
    char* str1 = "Hello World !!!"; 
    char* str2 = "owdl"; 
    char* str3 = "z"; 

    //act
    int result1 = strcspn(str1, str2); 
    int result2 = strcspn(str1, str3); 

    //assert
    TEST_ASSERT_EQUAL_INT(2, result1); //l is the first character found here... 
    TEST_ASSERT_EQUAL_INT(15, result2); //z not found - so should return the index of null terminating character here... 
}

void strpbrk_will_return_pointer_to_first_character_in_first_string_matching_with_any_characters_in_second_string(void)
{
    //arrange
    char* str1 = "Hello World !!!"; 
    char* str2 = "owdl"; 
    char* str3 = "z"; 

    //act
    char* subString1 = strpbrk(str1, str2); 
    char* subString2 = strpbrk(str1, str3); 

    //assert
    int result = strcmp("llo World !!!", subString1);
    TEST_ASSERT_EQUAL_INT(0, result); //l is the first character found here... 
    TEST_ASSERT_EQUAL(NULL, subString2); //z not found - returns NULL... 
}

/*----------------------------------Error Handling Functions ---------------------------------------*/

void strerror_should_return_error_description_based_on_error_id(void)
{
    //arrange
    int err = 1; 

    //act
    char* errorDescription = strerror(err); 

    //assert
    int result = strcmp("Operation not permitted", errorDescription);
    TEST_ASSERT_EQUAL_INT(0, result); 
}


/*---------------------------------- Memory Functions ---------------------------------------*/

void memcpy_will_copy_n_bytes_of_source_to_destination(void)
{
    //arrange
    char* source = "source";
    char destination1[100] = "destination"; 
    char destination2[100] = "destination"; 

    //act
    memcpy(destination1, source, 6);
    memcpy(destination2, source, 7);

    //assert
    int result1 = strcmp("sourceation", destination1);
    int result2 = strcmp("source", destination2); 

    TEST_ASSERT_EQUAL_INT(0, result1);
    TEST_ASSERT_EQUAL_INT(0, result2); 
}

//the advantage of memmove over memcpy is that it can be used in overlapping memory sections... 
void memmove_will_copy_n_bytes_of_source_to_destination(void)
{
    //arrange
    char* source = "source";
    char destination1[100] = "destination"; 
    char destination2[100] = "destination"; 

    //act
    memmove(destination1, source, 6);
    memmove(destination2, source, 7);

    //assert
    int result1 = strcmp("sourceation", destination1);
    int result2 = strcmp("source", destination2); 

    TEST_ASSERT_EQUAL_INT(0, result1);
    TEST_ASSERT_EQUAL_INT(0, result2); 
}

void memcmp_will_compare_two_memory_sections_till_n_th_byte_and_will_return_zero_if_equal(void)
{
    //arrange
    char* str1 = "Hello World !!!";
    char* str2 = "Hello Mars !!!"; 
    char* str3 = "Z"; 

    //act
    int result_1_2_6 = memcmp(str1, str2, 6);
    int result_1_2_7 = memcmp(str1, str2, 7);
    int result_1_2_0 = memcmp(str1, str2, 0); //comparing zero length will result in 0 
    
    int result_1_3_0 = memcmp(str1, str3, 0); //comparing zero length will result in 0 
    int result_1_3_1 = memcmp(str1, str3, 1);

    //assert
    TEST_ASSERT_EQUAL_INT(0, result_1_2_6);
    TEST_ASSERT_NOT_EQUAL_INT(0, result_1_2_7); 
    TEST_ASSERT_EQUAL_INT(0, result_1_2_0); 
    TEST_ASSERT_EQUAL_INT(0, result_1_3_0); 
    TEST_ASSERT_NOT_EQUAL_INT(0, result_1_3_1); 
}

void memchr_will_return_the_substring_with_provided_char_within_first_n_bytes(void)
{
    //arrange
    char* str1 = "Hello World !!!";
    char ch1 = 'd'; 
    char ch2 = 'z'; 

    //act
    char* substring1 = memchr(str1, ch1, 11); 
    char* substring2 = memchr(str1, ch1, 10); 
    char* substring3 = memchr(str1, ch2, strlen(str1)+1); 

    //assert
    int result = strcmp("d !!!", substring1); 
    TEST_ASSERT_EQUAL_INT(0, result); 
    TEST_ASSERT_EQUAL(NULL, substring2); 
    TEST_ASSERT_EQUAL(NULL, substring3); 
}


void run_string_function_tests(void)
{
    UNITY_BEGIN(); 
    //String Manipulations
    RUN_TEST(strcpy_will_copy_source_string_to_destination_string_including_null_terminator);
    RUN_TEST(strcpy_will_cause_overflow_if_destination_string_length_is_less_than_source); 
    RUN_TEST(strncpy_will_copy_source_string_to_destination_string_except_for_null_terminator); 
    RUN_TEST(strcat_will_append_source_string_to_the_end_of_destination_string_including_null_terminator); 
    RUN_TEST(strcat_will_cause_overflow_if_destination_length_is_not_enough_to_accommodate_source_and_null_terminator); 
    RUN_TEST(strncpy_will_append_source_string_to_the_end_of_destination_string_including_the_null_terminator); 
    RUN_TEST(strtok_will_split_the_string_to_tokens_based_on_a_delimiter); 

    //String Comparison
    RUN_TEST(strncmp_will_compare_two_strings_up_to_a_specified_size); 

    //String Metadata
    RUN_TEST(strlen_will_return_the_size_of_string_till_null_terminating_character); 
    RUN_TEST(strlen_may_overflow_if_null_terminating_character_is_not_within_array_bounds); 
    RUN_TEST(strchr_will_return_pointer_to_to_the_first_occurence_of_character_in_second_argument); 
    RUN_TEST(strchr_will_return_null_pointer_if_character_not_found); 
    RUN_TEST(strstr_will_return_pointer_to_to_the_first_occurence_of_string_in_second_argument);
    RUN_TEST(strstr_will_return_null_pointer_if_string_not_found); 
    RUN_TEST(strspn_will_return_number_of_characters_in_the_beginning_of_first_string_matching_second_string); 
    RUN_TEST(strcspn_will_return_number_of_characters_in_the_beginning_of_first_string_not_matching_any_of_chars_in_second); 
    RUN_TEST(strpbrk_will_return_pointer_to_first_character_in_first_string_matching_with_any_characters_in_second_string); 

    //Error Handling
    RUN_TEST(strerror_should_return_error_description_based_on_error_id);

    //Memory Functions
    RUN_TEST(memcpy_will_copy_n_bytes_of_source_to_destination); 
    RUN_TEST(memcmp_will_compare_two_memory_sections_till_n_th_byte_and_will_return_zero_if_equal); 
    RUN_TEST(memcmp_will_compare_two_memory_sections_till_n_th_byte_and_will_return_zero_if_equal); 
    RUN_TEST(memchr_will_return_the_substring_with_provided_char_within_first_n_bytes); 

    UNITY_END(); 
}