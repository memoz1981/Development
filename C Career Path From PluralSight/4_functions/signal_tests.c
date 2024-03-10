#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/*
Process Signaling Macros

SIGABRT - Signals abnormal program termination
SIGFPE - Signals that a floating-point error occurred
SIGILL - Signals that an illegal operation occurred
SIGINT - Signals that an interrupt occurred (ctrl-c)
SIGSEGV - Signals violation of memory/data access
SIGTERM - Signals program termination

Process Signaling Functions
void ( *signal( int signal, void ( *foo )( int ) ) )( int ) - Given a signal macro (defined on the 
previous slide) and a pointer to a function, foo, that returns void and takes in an integer, 
signal will return a pointer to the given function and also register it as a signal 
handler for the given signal.
int raise(int signal) - This function raises the process signal 
passed to it. This function works in tandem with the macros described on the previous slide.

Predefined Signal Handling Functions
SIG_DFL - Default signal handling function used with the “signal” library function.
SIG_IGN - A macro that expands to a predefined function which ignores a given signal.

*/

void custom_function(int signal); 

void signal_will_assign_custom_function_to_specified_macro(void)
{
    //arrange
    signal(SIGABRT, &custom_function);

    //act
    raise(SIGABRT);

    //assert
}

void assigning_prefefined_ignore_function_will_result_in_nothing(void)
{
    //arrange
    signal(SIGABRT, SIG_IGN);

    //act
    raise(SIGABRT);

    //assert
    TEST_ASSERT_EQUAL_INT(1, 1); 
}

void custom_function(int signal)
{
    printf("Received signal %d", signal); 
    TEST_ASSERT_NOT_EQUAL_INT(0, signal); 
}

void run_signal_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(signal_will_assign_custom_function_to_specified_macro); 
    RUN_TEST(assigning_prefefined_ignore_function_will_result_in_nothing); 
    UNITY_END(); 
}