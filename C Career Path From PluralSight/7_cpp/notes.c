/*
4 stages of Compilation Process
Preprocessor - accepts *.c and returns *.i file
- Interprets each line starting with # as preprocessor command
and starts starts processing them. Below are some preprocessor commans
a) #include - Header file inclusion
b) #define - Macro expansion
c) #if...#else - Conditional compilation
d) #line - Line control
e) #error - Diagnostics
- removes comments
Compiler - accepts *.i and returns *.s file
- Checks for syntax errors
- Translates into assembly language
- Optimizes the translated code
Assembler - accepts *.s and returns *.o file
- Translates the assembly language file into machine code
Linker - accepts *.o and returns *.exe file
- Links function calls with their definitions
- Resolves system library function calls
- Adds additional code to start and end the program

Note: the intermediate files created duriong the comilation process can be viewed using below command for
a specific *.c file: 
gcc -o unitytests.exe 4_functions/string_tests.c -save-temps

Understanding CPP Directives

1) #include
- The main purposes of header files are re-usability and separations of concerns. 
- Header files - system defined (<> to include) and user defined("" to include)
Note: For custom defined header files - the names of h and c files don't need to match.
Important point is to include .h file within the .c file implementing the corresponding
function. So as a summary h should be referenced by c file(s) implementing the function and c file(s)
using the function. 

2) (#define) Macros
- Fragment of code identified by a name
- Macro name -> fragment of code
- Two types: Object like macros (#define BUFFER_SIZE 512) and function like macros. 
- Name should be alphanumeric

3) Conditional directives
- Whether to include a chunk of code or not
- Checks: 
a) Arithmetic operations
b) Whether a name is defined as macro
- Six kinds of conditional directives
a) #if
b) #else
c) #elif
d) #if defined - checkes if a macro is defined or not
e) #ifdef - checkes if a macro is defined or not
f) #ifndef - reverse of ifdef... returns true if not defined. 
Note: #endif - Ends all types of conditional directive blocks

4) Diagnostics and Line Control
- The purpose of the diagnostics is having the c preprocessor flag an error, or a warning based 
on a condition
- Two types of diagnostics
a) #error - The C Preprocessor reports a fatal error and stops preprocessing
b) #warning - The C Preprocessors issues a warning and continues preprocessing
usage: 
#if....
#error "Error description..."

5) Working with Pragmas and Special Macros
- pragma is a method to provide additional information to the compiler
- Different compilers have their own set of pragmas 
#pragma
Examples: 
a) #pragma once - when seen when scanning a header file - the file will not be read again
b) #pragma GCC depencency - allows checking dates of the current file and another file. If the other 
file is more recent - a warning is issued. 
c) #pragma GCC poison - continues with a list of identifiers to poison. If those identifiers are
anywhere in code after the directive, it's regarded as error. 
example: #pragma GCC poison printf will cause compilation fail if printf is used.
d) #pragma GCC system_header - regards the following code come from a system header
e) #pragma GCC warning - takes a message as an argument, and causes preprocessor issue a warning with 
that message
f) #pragma GCC error - same as warning - instead provides an error

Special Macros and Directives
__FILE__ - expands to the current input file
__LINE__ - expands to the current input line
__DATE__ - expands to the current date
__TIME__ - expands to the current time
__func__ - expands to the current function name

Working with macros
1) Understanding stringizing and concatenation
a) stringizing - converting macro argument to string (argument and surrounding text)
#define MACRO(arg) #arg
b) Token Concatenation (##)
- Merging to tokens
- Token pasting
- Can be used to concatenate
i) two identifiers
ii) identifier + preprocessing number
iii) two numbers
iv) multi-character operators

2) Variadic Macros
#define MACRO(...) expansion(__VA_ARGS__)
Can be used in one of below three forms: 
a) #define MYPRINTF(...) printf(__VA_ARGS__)
b) #define MYPRINTF(args...) printf(args)
c) #define MYPRINTF(x, ...)
if((x))
{
    printf(__VA_ARGS__); 
}

3) Predefined Macros
- no explicit macro definition required (basically because they have been pre-defined)
- mostly object type
- Types of predefined macros
a) Standard predefined macros (Language level defined)
__LINE__, __FILE__, __DATE__, __TIME__ etc. 
b) Common predefined macros (GNU C extension)
__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__
c) System specific predefined macros (System type)
- These are OS specific, IDE specific and/or Compiler specific
_WIN32

4) Undefining a Macro (#undef)
- Disassociating a macro name
- Using bare macro name
- No effect on non-macro

5) Operating system specific macros
- Windows: _WIN32, _WIN64
- Unix Like: __unix__
- Linux: __linux__
- MacOS: __apple__, __APPLE__   

6) Preprocessor invokation
- Normally compiler automatically invokes the preprocessor
- Manual invokation is possible for a c file using below commands
a) cpp <inputFile> <outputFile>
b) gcc-E <inputFile> <outputFile>

- The purpose of the line control is to specify original line number and source file name
#line lineNumber FileName
usage: 
#line 15 "newfilename"
*/