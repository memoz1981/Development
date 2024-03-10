#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
int isalnum(int c) - Checks whether the character is alphanumeric
int isalpha(int c) - Checks whether the character is alphabetic
int iscntrl(int c) - Checks whether the character is the “control” character
int isdigit(int c) - Checks whether the character is a decimal digit
int isxdigit(int c) - Checks whether the character is a hexadecimal 
digit
int islower(int c) - Checks whether the character is lowercase
int isupper(int c) - Checks whether the character is uppercase
int ispunct(int c) - Checks whether the character is punctuation
int isspace(int c) - Checks whether the character is whitespace
int isprint(int c) - Checks whether the character is printable (any 
character except the ”control” character)
int isgraph(int c) - Checks whether the character can be represented graphically (any printable character 
except whitespace characters)
int tolower(int c) - Converts a character to lowercase
int toupper(int c) - Converts a character to uppercase

*/

void run_isalnum_tests(void)
{
    //arrange

    //act
    int isAlphanumericExpectTrue1 = isalnum('a'); 
    int isAlphanumericExpectTrue2 = isalnum('Z');
    int isAlphanumericExpectTrue3 = isalnum('5');
    int isAlphanumericExpectFalse1 = isalnum(' ');
    int isAlphanumericExpectFalse2 = isalnum(',');
    int isAlphanumericExpectFalse3 = isalnum('\n');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isAlphanumericExpectTrue1); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isAlphanumericExpectTrue2); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isAlphanumericExpectTrue3); 
    TEST_ASSERT_EQUAL_INT(0, isAlphanumericExpectFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isAlphanumericExpectFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isAlphanumericExpectFalse3); 
}

void run_isalpha_tests(void)
{
    //arrange

    //act
    int isAlphabeticTrue1 = isalpha('a'); 
    int isAlphabeticTrue2 = isalpha('Z');

    int isAlphabeticFalse1 = isalpha(' ');
    int isAlphabeticFalse2 = isalpha(',');
    int isAlphabeticFalse3 = isalpha('\n');
    int isAlphabeticFalse4 = isalpha('8');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isAlphabeticTrue1); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isAlphabeticTrue2); 

    TEST_ASSERT_EQUAL_INT(0, isAlphabeticFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isAlphabeticFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isAlphabeticFalse3); 
    TEST_ASSERT_EQUAL_INT(0, isAlphabeticFalse4); 
}

void run_iscntrl_tests(void)
{
    //arrange

    //act
    int isControlTrue1 = iscntrl('\n'); 
    int isControlTrue2 = iscntrl('\0');
    int isControlTrue3 = iscntrl('\r');

    int isControlFalse1 = iscntrl(' ');
    int isControlFalse2 = iscntrl(',');
    int isControlFalse3 = iscntrl('a');
    int isControlFalse4 = iscntrl('8');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isControlTrue1); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isControlTrue2);
    TEST_ASSERT_NOT_EQUAL_INT(0, isControlTrue3); 

    TEST_ASSERT_EQUAL_INT(0, isControlFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isControlFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isControlFalse3); 
    TEST_ASSERT_EQUAL_INT(0, isControlFalse4); 
}

void run_isdigit_tests(void)
{
    //arrange

    //act
    int isDigitTrue1 = isdigit('1'); 
    int isDigitTrue2 = isdigit('0');

    int isDigitFalse1 = isdigit(' ');
    int isDigitFalse2 = isdigit(',');
    int isDigitFalse3 = isdigit('a');
    int isDigitFalse4 = isdigit('\t');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isDigitTrue1); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isDigitTrue2);

    TEST_ASSERT_EQUAL_INT(0, isDigitFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isDigitFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isDigitFalse3); 
    TEST_ASSERT_EQUAL_INT(0, isDigitFalse4); 
}

void run_isxdigit_tests(void)
{
    //arrange

    //act
    int isXDigitTrue1 = isxdigit('9'); 
    int isXDigitTrue2 = isxdigit('0');
    int isXDigitTrue3 = isxdigit('a');
    int isXDigitTrue4 = isxdigit('F');

    int isXDigitFalse1 = isxdigit(' ');
    int isXDigitFalse2 = isxdigit(',');
    int isXDigitFalse3 = isxdigit('\n');
    int isXDigitFalse4 = isxdigit('g');
    int isXDigitFalse5 = isxdigit('Z');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isXDigitTrue1); 
    TEST_ASSERT_NOT_EQUAL_INT(0, isXDigitTrue2);
    TEST_ASSERT_NOT_EQUAL_INT(0, isXDigitTrue3);
    TEST_ASSERT_NOT_EQUAL_INT(0, isXDigitTrue4);

    TEST_ASSERT_EQUAL_INT(0, isXDigitFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isXDigitFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isXDigitFalse3); 
    TEST_ASSERT_EQUAL_INT(0, isXDigitFalse4);
    TEST_ASSERT_EQUAL_INT(0, isXDigitFalse5); 
}

void run_islower_tests(void)
{
    //act
    int isLowerTrue1 = islower('a'); 

    int isLowerFalse1 = islower('Z');
    int isLowerFalse2 = islower('5');
    int isLowerFalse3 = islower(' ');
    int isLowerFalse4 = islower(',');
    int isLowerFalse5 = islower('\n');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isLowerTrue1); 

    TEST_ASSERT_EQUAL_INT(0, isLowerFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isLowerFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isLowerFalse3); 
    TEST_ASSERT_EQUAL_INT(0, isLowerFalse4); 
    TEST_ASSERT_EQUAL_INT(0, isLowerFalse5); 
}

void run_isupper_tests(void)
{
    //act
    int isUpperTrue1 = isupper('Z'); 

    int isUpperFalse1 = isupper('a');
    int isUpperFalse2 = isupper('5');
    int isUpperFalse3 = isupper(' ');
    int isUpperFalse4 = isupper(',');
    int isUpperFalse5 = isupper('\n');

    //assert
    TEST_ASSERT_NOT_EQUAL_INT(0, isUpperTrue1); 

    TEST_ASSERT_EQUAL_INT(0, isUpperFalse1); 
    TEST_ASSERT_EQUAL_INT(0, isUpperFalse2); 
    TEST_ASSERT_EQUAL_INT(0, isUpperFalse3); 
    TEST_ASSERT_EQUAL_INT(0, isUpperFalse4); 
    TEST_ASSERT_EQUAL_INT(0, isUpperFalse5); 
}

void run_ispunct_tests(void)
{
    TEST_IGNORE(); 
}

void run_isspace_tests(void)
{
    TEST_IGNORE(); 
}

void run_isprint_tests(void)
{
    TEST_IGNORE(); 
}

void run_isgraph_tests(void)
{
    TEST_IGNORE(); 
}

void run_tolower_tests(void)
{
    TEST_IGNORE(); 
}

void run_toupper_tests(void)
{
    TEST_IGNORE(); 
}

void run_ctype_tests(void)
{
    UNITY_BEGIN(); 

    RUN_TEST(run_isalnum_tests);
    RUN_TEST(run_isalpha_tests); 
    RUN_TEST(run_iscntrl_tests); 
    RUN_TEST(run_isdigit_tests); 
    RUN_TEST(run_isxdigit_tests); 
    RUN_TEST(run_islower_tests);
    RUN_TEST(run_isupper_tests);  

    RUN_TEST(run_ispunct_tests); 
    RUN_TEST(run_isspace_tests); 
    RUN_TEST(run_isprint_tests); 
    RUN_TEST(run_isgraph_tests); 
    RUN_TEST(run_tolower_tests); 
    RUN_TEST(run_toupper_tests); 
    
    UNITY_END();
}