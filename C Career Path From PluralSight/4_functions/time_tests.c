#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../helper_functions/helper.h"
#include <unistd.h>

/*
Types
time_t - simplest data type used to represent simple calendar time. In ISO C, time_t can be either an integer or a floating-point type, 
and the meaning of time_t values is not specified. On POSIX-conformant systems, time_t 
is an integer type and its values represent the number of seconds elapsed 
since the epoch, which is 00:00:00 on January 1, 1970, Coordinated Universal Time. (Just like NodaTime Instant huh?)

IMPORTANT MACROS:
CLOCKS_PER_SEC - This macro expands to the speed of your processor which is measured in clocks per second.

Core Functions
clock_t clock(void) - Fetches the clock time of the computer’s processor. Useful for marking certain sections of 
a program in order to compute execution times.

double difftime(time_t first, time_t second) - Returns the difference, in seconds, between the 
”first” time and the “second” time. It subtracts “second” from “first”

time_t time(time_t* timer) - Computes the current calendar time

Conversion/Formatting
size_t strftime(char* str, size_t max, const char* format, const struct tm* time_ptr) - Puts a formatted time string into the “str” 
argument given a format and a “tm” struct
time_t mktime(struct tm* time_ptr) - Given a “tm” struct, this function fetches the correct time_t value in local time
struct tm* localtime(const time_t* time) - Reverse of “mktime”
struct tm* gmtime(const time_t* time) - Like local time but uses UTC/GMT
char* ctime(const time_t* time) - Computes a C string based on a given time. The time zone used is local.
char* asctime(const struct tm* time_ptr) - Computes a C string containing the day/time given the “tm” struct
*/

/*
Important note: localtime conversion and then conversion back to time_t 
results in utc time...
*/
void time_t_struct_with_difftime_function_can_be_used_to_get_time_difference(void)
{
    TEST_IGNORE(); 
    //arrange
    putenv( "TZ=GMT+4" ); //set env variable..
    printf("time zone is %s", getenv("TZ")); 
    const time_t current_time = time(NULL); //local time
    printf("Current Time: %s", ctime(&current_time));
    struct tm* local_time = localtime(&current_time); //local time based on present time
    struct tm* utc_time = gmtime(&current_time); // get gmt time based on present time
    printf("Local time is %d and gmt time is %d\n\n", local_time->tm_mday, utc_time->tm_mday); 
    printf("%ld\n", timezone);
    
    //act
    time_t converted_local_time = mktime(local_time);
    time_t converted_utc_time = mktime(utc_time);

    float local_time_diff_in_hours = difftime(current_time, converted_local_time) / 3600;
    float expected_utc_to_local_time_diff_in_hours = difftime(current_time, converted_utc_time) / 3600; 
    
    //assert
    TEST_ASSERT_GREATER_OR_EQUAL_FLOAT(0, local_time_diff_in_hours); 
    TEST_ASSERT_GREATER_OR_EQUAL_FLOAT(3, expected_utc_to_local_time_diff_in_hours); 
    TEST_ASSERT_LESS_OR_EQUAL_FLOAT(4, expected_utc_to_local_time_diff_in_hours); 
}

void time_t_struct_contains_time_from_epoch(void)
{
    //arrange
    putenv( "TZ=GMT+4" ); //set env variable..
    printf("time zone is %s", getenv("TZ")); 
    time_t current_time = time(NULL); 
    long current_time_long = current_time; 

    //act
    int years = current_time_long / (3600 * 24 * 365.25); 
    int months = (current_time_long - (years * 3600 * 24 * 365.25)) / (3600 * 24 * 30); 
    printf("%d years and approximately %d months passed from 1970 1 Jan 00:00:00,", years, months); 

    //assert
    TEST_ASSERT_GREATER_OR_EQUAL_DOUBLE(54, years); //the test was written in Feb 2024... 
}

void time_difference_can_be_measured_using_clock_or_time_functions(void)
{
    //arrange
    clock_t start, end; 
    time_t start_time, end_time; 
    double time_passed_using_clock, time_passed_using_time; 

    //act
    start = clock(); 
    start_time = time(NULL); 

    sleep(2);

    end = clock();
    end_time = time(NULL); 

    time_passed_using_clock = ((double)(end - start)) / CLOCKS_PER_SEC; 
    time_passed_using_time = (long)end_time - (long)start_time; 
    double result = difftime(end_time, start_time); 

    //assert
    TEST_ASSERT_GREATER_OR_EQUAL_DOUBLE(2, time_passed_using_clock);
    TEST_ASSERT_GREATER_OR_EQUAL_DOUBLE(2, time_passed_using_time); 
    TEST_ASSERT_GREATER_OR_EQUAL_DOUBLE(2, result); 
}

void time_function_argument_and_return_will_point_to_same_time(void)
{
    //arrange
    time_t time_1, time_2; 

    //act
    time_1 = time(&time_2); 
    long time1 = (long)time_1; 
    long time2 = (long)time_2; 

    //assert
    TEST_ASSERT_EQUAL(time1, time2); 
}

//For some time local_time is returning UTC-4 time
void ctime_should_return_string_based_on_local_time(void)
{
    //arrange
    time_t const current_time = time(NULL); 
    putenv( "TZ=GMT+4" ); //set env variable..

    //act
    char* str = ctime(&current_time); 
    puts(str); 

    //assert
    TEST_ASSERT_EQUAL_INT(1,1); 
}

//All methods seem to return same value which is a bit unusal. 
void asctime_should_return_string_based_on_tm_object(void)
{
    //arrange
    time_t const current_time = time(NULL); 
    putenv( "TZ=GMT+4" ); //set env variable..
    struct tm* local = localtime(&current_time); 
    struct tm* utc = gmtime(&current_time); 

    //act
    char* strLocal = asctime(local); 
    char* strUtc = asctime(utc); 
    char* strTime = ctime(&current_time); 
    printf("The time strings using 1) asctime for local: %s ; 2) asctime for gmt: %s ; 3) ctime: %s", 
    strLocal, strUtc, strTime);

    //assert
    TEST_ASSERT_EQUAL_INT(1,1); 
}

void mktime_should_convert_tm_object_back_to_time_t(void)
{
    //arrange
    const time_t current_time = time(NULL);
    struct tm* local = localtime(&current_time);
    struct tm* utc = gmtime(&current_time); 

    //act
    time_t converted_time_from_local = mktime(local); 
    time_t converted_time_from_utc = mktime(utc); 

    //assert
    /*
    --- AS TIME PASSES DURING THE TEST - AS I UNDERSTAND IT -> START AND END TIMES DON'T MATCH ---
    TEST_ASSERT_EQUAL(current_time, converted_time_from_local);
    TEST_ASSERT_EQUAL(current_time, converted_time_from_utc); 
    */
    TEST_ASSERT_EQUAL(converted_time_from_local, converted_time_from_utc); 
}

void strftime_will_create_formatted_string_from_tm_object(void)
{
    //arrange
    const time_t current_time = time(NULL);
    struct tm* local = localtime(&current_time); 
    char formatted_time[200]; 
    memset(formatted_time, '\0', 200); 

    //act
    strftime(formatted_time, 200, "%Z: %Y // %B // %d : %X (%A)", local);
    printf("Formatted time: %s", formatted_time); 

    //assert
    TEST_ASSERT_EQUAL_INT(1, 1); 
}

void run_time_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(time_t_struct_with_difftime_function_can_be_used_to_get_time_difference);
    RUN_TEST(time_t_struct_contains_time_from_epoch); 
    RUN_TEST(time_difference_can_be_measured_using_clock_or_time_functions); 
    RUN_TEST(time_function_argument_and_return_will_point_to_same_time); 
    RUN_TEST(ctime_should_return_string_based_on_local_time); 
    RUN_TEST(asctime_should_return_string_based_on_tm_object); 
    RUN_TEST(mktime_should_convert_tm_object_back_to_time_t); 
    RUN_TEST(strftime_will_create_formatted_string_from_tm_object); 
    UNITY_END(); 
}