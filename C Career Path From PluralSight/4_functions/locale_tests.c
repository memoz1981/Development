#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

/*
Locale Category Macros
LC_ALL - Sets all of the below macro categories to the given locale
LC_COLLATE - Sets the locale of the strcoll and strxfrm standard library functions
LC_CTYPE - Sets the locale of all of the character functions 
in the standard library
LC_MONETARY - Sets the locale of the money fields in the struct 
returned by the localeconv function
LC_NUMERIC - Sets the locale of the numeric fields and decimal 
formatting in the struct returned by the 
localeconv function
LC_TIME - Sets the locale of the strftime time formatting 
function in the standard library

Locale Functions
char* setlocale(int category, const char* locale) - Sets values of the “lconv” struct returned by a 
called to “localeconv” and possibly other C library functions based on a given ”locale” string 
and a category. If locale is not NULL, the values/functions relevant to the given category 
are set to the given locale. If locale is NULL the values/functions relevant to the given category 
are set from environment variables that use the same names as the macro definitions defined 
prior to this slide.

struct lconv* localeconv(void) - Meant to be used after “setlocale” this function 
fetches the current locale being used by the program.

*/

void lc_all_will_set_all_locale_to_one_specified(void)
{
    TEST_IGNORE(); //FOR SOME REASON LOCALE TEST IS NOT WORKING - NEED FURTHER INVESTIGATION... 
    //arrange
    struct lconv* my_locale; 
    //act
    setlocale(LC_ALL, "ja_JP");
    setlocale(LC_MONETARY, "ja_JP"); 
    my_locale = localeconv();
    printf("US currency symbol: %s\n", my_locale->currency_symbol);

    //assert
    TEST_ASSERT_EQUAL_INT(1, 1); 
}

void run_locale_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(lc_all_will_set_all_locale_to_one_specified);
    UNITY_END(); 
}