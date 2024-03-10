#include "func_tests.h"
#include "../unity/unity.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "../helper_functions/helper.h"
#include <stdarg.h>

/*---------------------------------------File Operations FUNCTIONS-------------------------------------------------*/

/*
FILE* fopen(const char* filename, const char* mode)
Opens a file in the given mode. The list of possible modes are as below
"r" - Opens a file for reading. The file must exist.
"w" - Creates an empty file for writing. 
If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
"a" - Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
"r+" - Opens a file to update both reading and writing. The file must exist.
"w+" - Creates an empty file for both reading and writing.
"a+" - Opens a file for reading and appending.
*/

void fopen_trying_to_open_non_existing_file_in_r_mode_should_result_in_exception(void)
{
    //arrange

    //act
    fopen("../bin/file_not_existing.txt", "r"); 

    //assert
    char* errNoValue = strerror(errno); 
    int len = strlen(errNoValue); 
    TEST_ASSERT_EQUAL(ENOENT, errno); 
    TEST_ASSERT_GREATER_OR_EQUAL_INT32(1, len); 
}

void fopen_in_filemode_w_should_result_in_creating_new_file(void)
{
    //arrange
    FILE* file; 
    const char* content = "Hello world!!!";
    const char* fileName = "../bin/fileNew.txt"; 

    remove(fileName); //this ensures that file will not be present when opening the file in w mode
    const int BUFFER_SIZE = 100; 
    char fileContent[BUFFER_SIZE]; 

    //act
    file = fopen(fileName, "w"); 
    fputs(content, file); 
    fclose(file); //could rewind here, and then read the stream. preferred to open a new stream. 

    file = fopen(fileName, "r"); 
    fgets(fileContent, BUFFER_SIZE, file); 
    int result = strcmp(content, fileContent); 

    //assert
    fclose(file);
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void fopen_trying_to_update_file_opened_in_r_mode_should_set_errno(void)
{
    //arrange
    char* fileName = "../bin/file.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w"); //to ensure file is created
    fclose(file); 
    file = fopen(fileName, "r");
    const char* content = "Hello world!!!";

    //act
    fputs(content, file); 

    //assert
    char* errNoValue = strerror(errno); 
    int len = strlen(errNoValue); 
    TEST_ASSERT_EQUAL(EBADF, errno); 
    TEST_ASSERT_GREATER_OR_EQUAL_INT32(1, len);
}

/*
int fclose(FILE* stream)
Closes a file and flushes buffers
Returns zero if the stream is successfully closed. On failure, EOF is returned.
Note: it doesn't set the pointer to NULL
*/
void flose_will_close_the_file_and_flushes_buffers(void)
{
    //arrange
    FILE* file; 
    const char* fileName = "../bin/fileNew.txt"; 

    //act
    file = fopen(fileName, "r"); 
    int result = fclose(file);

    //assert
    TEST_ASSERT_EQUAL_INT(0, result); 
}

/*
FILE* freopen(const char* filename, const char* mode, FILE* stream)
Reopens a closed file
Modes are same as the ones used in fopen
Because of some known bugs - it's not recommended to use this function. 
PS: Seems that it can also be used to associate a different filename with current stream. 
https://stackoverflow.com/questions/4169263/whats-the-difference-between-fopen-and-freopen
*/
void freopen_opens_closed_file(void)
{
    //arrange
    FILE* file; 
    FILE* fileReopened; 
    const char* fileName = "../bin/fileNew.txt"; 
    const char* content = "Hello world!!!";
    const int BUFFER_SIZE = 100; 
    char fileContent[BUFFER_SIZE]; 

    //act
    file = fopen(fileName, "r"); 
    fgets(fileContent, BUFFER_SIZE, file); 
    fclose(file);

    fileReopened = freopen(fileName, "r", file); 
    fgets(fileContent, BUFFER_SIZE, file); 
    int result = strcmp(content, fileContent); 
    fclose(fileReopened); 

    //assert
    TEST_ASSERT_EQUAL_INT(0, result); 
}

/*
int setvbuf(FILE* stream, char* buffer, int mode, size_t size)
Sets the buffer of a given stream
stream − This is the pointer to a FILE object that identifies an open stream.
buffer − This is the user allocated buffer. If set to NULL, the function automatically allocates a buffer of the specified size.
mode − This specifies a mode for file buffering −
_IOFBF: Full buffering − On output, data is written once the buffer is full. 
On Input the buffer is filled when an input operation is requested and the buffer is empty.
_IOLBF : Line buffering − On output, data is written when a newline character is inserted into the stream or when the buffer is full, 
what so ever happens first. On Input, the buffer is filled till the next newline character when an input operation is requested and buffer is empty.
_IONBF: No buffering − No buffer is used. Each I/O operation is written as soon as possible. 
The buffer and size parameters are ignored.
*/

/*
int fflush(FILE* stream)
Flushes the buffer of a stream
This function returns a zero value on success. If an error occurs, EOF is returned and the error indicator is set (i.e. feof).
*/

void full_buffer_in_output_mode_should_write_when_buffer_flushed(void)
{
    //arrange
    char* fileName = "../bin/fileNew.txt"; 
    int buffer_size = 64;
    remove(fileName); 
    char buffer[buffer_size];
    FILE * file = fopen(fileName, "w+");
    memset(buffer, '\0', buffer_size); 

    //act
    setvbuf(file, buffer, _IOFBF, buffer_size);

    //assert
    fputs ("123", file);
    int result1 = strcmp("123", buffer); 
    TEST_ASSERT_EQUAL_INT(0, result1); 

    fputs ("456", file);
    int result2 = strcmp("123456", buffer); 
    TEST_ASSERT_EQUAL_INT(0, result2); 

    fflush(file); 
    
    fputs ("abcd", file);
    int result3 = strcmp("abcd56", buffer); 
    TEST_ASSERT_EQUAL_INT(0, result3); 

    fflush(file); 

    fclose(file); 
    
    file = fopen(fileName, "r");
    fgets(buffer, sizeof buffer, file);
   
    int result4 = strcmp("123456abcd", buffer);
    TEST_ASSERT_EQUAL_INT(0, result4); 
}

void full_buffer_in_output_mode_should_write_when_buffer_is_full(void)
{
    //arrange
    int buffer_size = 8;
    char* fileName = "../bin/fileNew.txt"; 
    remove(fileName); 
    char buffer[buffer_size];
    FILE * file = fopen(fileName, "w+");
    memset(buffer, '\0', buffer_size); 

    //act
    setvbuf(file, buffer, _IOFBF, buffer_size);

    //assert
    fputs ("abcdef", file);
    int result1 = strcmp("abcdef", buffer); //correspondingly nothing is written to the file yet
    TEST_ASSERT_EQUAL_INT(0, result1); 

    fputs ("ghijkl", file);

    /*Check file thru a separate stream - element count should be same as buffer size*/
    FILE* file2 = fopen(fileName, "r"); 
    char buffer2[32];
    fgets(buffer2, 32, file2); 
    int resultNew = strcmp("abcdefgh", buffer2); 
    TEST_ASSERT_EQUAL_INT(0, resultNew); 
    fclose(file2); 
    
    //now since the array is 8 characters long, and doesn't end with null terminating character
    //directly trying to compare with a string results in undefined behaviour. 
    //thus declaring a new array to compare the buffer. 
    char bufferNew[9];
    memset(bufferNew, '\0', 9); 
    copyArray(bufferNew, buffer, sizeof(buffer)); 
    int result2 = strcmp("ijklefgh", bufferNew);   
    TEST_ASSERT_EQUAL_INT(0, result2); 

    fflush(file); 
    
    fputs ("1234", file);
    copyArray(bufferNew, buffer, sizeof(buffer)); 
    int result3 = strcmp("1234efgh", bufferNew); 
    TEST_ASSERT_EQUAL_INT(0, result3); 

    fflush(file); 

    fclose(file); 
    
    file = fopen(fileName, "r");
    fgets(buffer2, sizeof buffer2, file);
   
    int result4 = strcmp("abcdefghijkl1234", buffer2);
    TEST_ASSERT_EQUAL_INT(0, result4); 
}

void full_buffer_for_input_mode_should_write_to_file_when_buffer_is_full_or_flushed(void)
{
    //arrange
    char* fileName = "../bin/fileNew.txt"; 
    char helloWorld[15] = "Hello world!!!"; 
    int buffer_size = 8;
    char buffer[buffer_size];
    memset(buffer, '\0', buffer_size); 
    remove(fileName); //i.e. will be removed if exists.
    char buffer_new[buffer_size + 1]; 
    memset(buffer_new, '\0', buffer_size + 1); 

    FILE * file = fopen(fileName, "w"); //create file
    fputs(helloWorld, file);
    fclose(file); 
   
    //act
    file = fopen(fileName, "r");
    setvbuf(file, buffer, _IOFBF, buffer_size);
    char ch; 

    for(int i=0; i < 14; i++)
    {
        ch = fgetc(file); 
        
        //assert
        TEST_ASSERT_EQUAL_CHAR(helloWorld[i], ch); 

        if(i<buffer_size)
        {
            copyArray(buffer_new, buffer, buffer_size); 
            int result = strcmp("Hello wo", buffer_new); 
            TEST_ASSERT_EQUAL_INT(0, result); 
        }
        else
        {
            copyArray(buffer_new, buffer, buffer_size); 
            int result = strcmp("rld!!!wo", buffer_new); 
            TEST_ASSERT_EQUAL_INT(0, result); 
        }
    }
}

/*Renames a file*/
void rename_will_rename_existing_file(void)
{
    //arrange
    char* fileNameOld = "../bin/filebeforerename.txt";
    char* fileNameNew = "../bin/fileafterrename.txt";
    remove(fileNameOld); 
    remove(fileNameNew); 
    FILE * file = fopen(fileNameOld, "w"); //create file
    fputs("Hello world", file); 
    fclose(file); 

    //act
    rename(fileNameOld, fileNameNew); 
     file = fopen(fileNameNew, "r"); 
    char buffer[20]; 
    memset(buffer, '\0', 20); 
    fgets(buffer, 20, file);

    //assert
    int result = strcmp("Hello world", buffer);
    TEST_ASSERT_EQUAL_INT(0, result); 
}

/*Creates a temporary file*/
void tmpfile_will_create_a_temporarily_file(void)
{
    //arrange
    char buffer[20]; 
    memset(buffer, '\0', 20); 

    //act
    FILE * file = tmpfile(); //create file
    fputs("Hello world", file); 
    rewind(file);
    fgets(buffer, 20, file);
    int result = strcmp("Hello world", buffer);
    
    //assert
    TEST_ASSERT_EQUAL_INT(0, result); 
    fclose(file); 
}

void run_file_operations_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(fopen_trying_to_open_non_existing_file_in_r_mode_should_result_in_exception); 
    RUN_TEST(fopen_in_filemode_w_should_result_in_creating_new_file); 
    RUN_TEST(fopen_trying_to_update_file_opened_in_r_mode_should_set_errno); 
    RUN_TEST(flose_will_close_the_file_and_flushes_buffers); 
    RUN_TEST(freopen_opens_closed_file); 
    RUN_TEST(full_buffer_in_output_mode_should_write_when_buffer_flushed); 
    RUN_TEST(full_buffer_in_output_mode_should_write_when_buffer_is_full); 
    RUN_TEST(full_buffer_for_input_mode_should_write_to_file_when_buffer_is_full_or_flushed); 
    RUN_TEST(rename_will_rename_existing_file); 
    RUN_TEST(tmpfile_will_create_a_temporarily_file); 
    UNITY_END(); 
}

/*---------------------------------------File Positioning Functions-------------------------------------------------*/

/*
int fgetpos(FILE* stream, fpos_t* pos) - Puts the current file position of the given stream 
into the value pointed to by the “pos” pointer

int fsetpos(FILE* stream, const fpos_t* pos) - Uses the given position to set the file position of 
the given stream

int fseek(FILE* stream, long int offset, int from) - Given an offset from the position of the “from” 
argument, this function sets the position of the file stream. The SEEK_SET, SEEK_CUR, 
SEEK_END macros are used with this function.
stream − This is the pointer to a FILE object that identifies the stream.
offset − This is the number of bytes to offset from whence.
whence − This is the position from where offset is added. It is specified by one of the following constants −
SEEK_SET: Beginning of file
SEEK_CUR: Current position of the file pointer
SEEK_END: End of file

long int ftell(FILE* stream) - Fetches the file position of the given stream

void rewind(FILE* stream) - Sets the file position of the given stream to the beginning.
*/

void fgetpos_should_return_the_current_position_of_the_file_stream(void)
{
    //arrange
    char* fileName = "../bin/fgetpos.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    fpos_t position;
    char buffer[100];
    memset(buffer, '\0', 100); 

    //act
    fputs("First line \n", file); 
    fgetpos(file, &position); //this will read current file position to &position pointer
    fputs("Second line", file); 
    fsetpos(file, &position); //this will reset the file position to previous start - i.e. to the beginning of second line
    fputs("This should overwrite the second line", file); 
    rewind(file); 

    //assert
    fgets(buffer, 100, file); 
    int result = strcmp("First line \n", buffer);
    TEST_ASSERT_EQUAL_INT(0, result); 

    memset(buffer, '\0', 100); 
    fgets(buffer, 100, file); 
    result = strcmp("This should overwrite the second line", buffer);
    TEST_ASSERT_EQUAL_INT(0, result); 

    fclose(file); 
}

void fseek_will_set_stream_position_as_per_specified_whence_and_offset(void)
{
    //arrange
    char* fileName = "../bin/fseek.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    char buffer[100];
    memset(buffer, '\0', 100); 

    //act
    fputs("My name is James Bond", file); 
    fseek(file, 11, SEEK_SET);
    fputs("Ethan Hunt", file);
    rewind(file);  
    fgets(buffer, 100, file); 

    //assert
    int result = strcmp("My name is James Bond", buffer);
    TEST_ASSERT_NOT_EQUAL_INT(0, result); 

    int actualResult = strcmp("My name is Ethan Hunt", buffer);
    TEST_ASSERT_EQUAL_INT(0, actualResult); 
    fclose(file); 
}

void ftell_should_return_the_file_position(void)
{
    //arrange
    char* fileName = "../bin/ftell.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    int position;

    //act
    position = ftell(file); 

    //assert
    TEST_ASSERT_EQUAL_INT(0, position); 

    fputs("Hello world", file); 
    position = ftell(file); 

    TEST_ASSERT_EQUAL_INT(11, position); 

    rewind(file); 
    position = ftell(file); 
    TEST_ASSERT_EQUAL_INT(0, position); 
}

void run_file_positioning_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(fgetpos_should_return_the_current_position_of_the_file_stream); 
    RUN_TEST(fseek_will_set_stream_position_as_per_specified_whence_and_offset); 
    RUN_TEST(ftell_should_return_the_file_position);
    UNITY_END(); 
}

/*---------------------------------------Error Handling Functions-------------------------------------------------*/

/*
void clearerr(FILE* stream) - Clears any errors or EOF indicators associated with the given stream

int feof(FILE* stream) - Tests the EOF indicator for the given stream

int ferror(FILE* stream) - Tests the error indicator for the given stream

void perror(const char* str) - This function is used to print an error message after a function may have caused a system error. This 
function works with ”errno” and will print the string given to it followed by a colon, a space and a 
descriptive error that is tied to the current “errno” interpretation
*/

void clearerr_should_clear_the_error_with_file_stream(void)
{
    //arrange
    char* fileName = "../bin/clearerr.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    fputs("Hello world", file);
    fclose(file);
    char buffer[100];
    memset(buffer, '\0', 100); 

    file =  fopen(fileName, "r");//now open the file in read mode only

    //act
    fputs("Hello Mars", file);
    int hasError = ferror(file); 
    TEST_ASSERT_NOT_EQUAL_INT(0, hasError); 

    if(hasError)
    {
        perror("Following error is thrown: "); 
        clearerr(file); 
    }

    fgets(buffer, 100, file); 

    //assert
    int result = strcmp("Hello world", buffer); 
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void feof_should_check_if_end_of_file_reached(void)
{
    //arrange
    char* fileName = "../bin/feof.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    fputs("Hello world", file);
    char buffer[100];
    memset(buffer, '\0', 100); 
    int characterCount = 0; 
    rewind(file); 

    //act
    while(1)
    {
        fgetc(file); 

        if(feof(file))
        {
            break; 
        }
        characterCount++; 
    }

    fclose(file); 

    //assert
    TEST_ASSERT_EQUAL_INT(11, characterCount); 
}

void run_error_handling_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(clearerr_should_clear_the_error_with_file_stream); 
    RUN_TEST(feof_should_check_if_end_of_file_reached); 
    UNITY_END(); 
}

/*---------------------------------------File I/O-------------------------------------------------*/

/*
size_t fread(void* array_ptr, size_t size, size_t num_bytes, FILE* stream) - Reads data from the given file stream and puts it into 
the array pointed to by the given void pointer

size_t fwrite(const void* array_ptr, size_t size, size_t num_bytes, FILE* stream) - Writes data to the given file stream from the array 
pointed to by the given void pointer.

ptr − This is the pointer to a block of memory with a minimum size of size*nmemb bytes.
size − This is the size in bytes of each element to be read.
num_bytes − This is the number of elements, each one with a size of size bytes.
stream − This is the pointer to a FILE object that specifies an input stream.\

*/

void fread_will_copy_file_contents_to_an_array(void)
{
    //arrange
    char* fileName = "../bin/fread.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    fputs("Hello world", file);
    char buffer1[20];
    memset(buffer1, '\0', 20); 

    char buffer2[20];
    memset(buffer2, '\0', 20); 

    char buffer3[20];
    memset(buffer3, '\0', 20); 

    //act
    rewind(file); 
    fread(buffer1, 1, 11, file);
    
    rewind(file);
    fread(buffer2, 11, 1, file);

    rewind(file);
    fread(buffer3, 2, 3, file);

    //assert
    int result1 = strcmp("Hello world", buffer1); 
    int result2 = strcmp("Hello world", buffer2); 
    int result3 = strcmp("Hello ", buffer3); 
    
    TEST_ASSERT_EQUAL_INT(0, result1); 
    TEST_ASSERT_EQUAL_INT(0, result2); 
    TEST_ASSERT_EQUAL_INT(0, result3); 
}

void fwrite_will_write_from_array_to_file_stream(void)
{
    //arrange
    char* fileName = "../bin/fwrite.txt"; 
    remove(fileName); 
    FILE* file = fopen(fileName, "w+");
    char buffer[100];
    memset(buffer, '\0', 100); 

    //act
    fwrite("Buffer 1 content, ", 1, 18, file);
    fwrite("Buffer 2 content, ", 18, 1, file);
    fwrite("Buffer 3 content, ", 2, 4, file);

    rewind(file);
    fread(buffer, 1, 44, file); 

    //assert
    int result = strcmp("Buffer 1 content, Buffer 2 content, Buffer 3", buffer); 
    
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void run_file_io_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(fread_will_copy_file_contents_to_an_array); 
    RUN_TEST(fwrite_will_write_from_array_to_file_stream); 
    UNITY_END(); 
}

/*---------------------------------------Formatted I/O-------------------------------------------------*/
/*
int fprintf(FILE* stream, const char* format, …) - Formatted file writing
int fscanf(FILE* stream, const char* format, …) - Formatted file reading
int vfprintf(FILE* stream, const char* format, va_list args) - Formatted file writing with variable arg list
int printf(const char* format, …) - Formatted writing
int scanf(const char* format, …) - Formatted reading
int vprintf(const char* format, va_list args) - Formatted writing with variable arg list
int sprintf(char* str, const char* format, …) - Formatted string writing
int sscanf(const char* str, const char* format, …) - Formatted string reading
int vsprintf(char* str, const char* format, va_list args) - Formatted string writing with variable arg
list

format −  %[flags][width][.precision][length]specifier

specifier & Output:
c - Character
d or i - Signed decimal integer
e - Scientific notation (mantissa/exponent) using e character
E - Scientific notation (mantissa/exponent) using E character
f - Decimal floating point
g - Uses the shorter of %e or %f
o - Signed octal
s - String of characters
u - Unsigned decimal integer
x - Unsigned hexadecimal integer
X - Unsigned hexadecimal integer (capital letters)
p - Pointer address
n - Nothing printed
% - Character

Flags: 
- -> Left-justifies within the given field width; Right justification is
 the default (see width sub-specifier).
+ -> Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. 
By default, only negative numbers are preceded with a -ve sign.
(space) -> If no sign is written, a blank space is inserted before the value.
# -> Used with o, x or X specifiers. The value is preceded with 0, 0x or 0X 
respectively for values different than zero. 
Used with e, E and f, it forces the written output to contain a 
decimal point even if no digits would follow. By default, if no digits follow then 
no decimal point is written. Used with g or G the result is the same as with e or 
E but trailing zeros are not removed.
0 -> Left-pads the number with zeroes (0) instead of spaces, 
where padding is specified (see width sub-specifier).

Width:
(number) -> Minimum number of characters to be printed. If the value to be printed is 
shorter than this number, the result is padded with blank spaces. 
The value is not truncated even if the result is larger.
* -> The width is not specified in the format string, but as an additional integer value argument preceding the
 argument that has to be formatted.

 Precision:
.number -> For integer specifiers (d, i, o, u, x, X) − precision specifies the minimum 
number of digits to be written. If the value to be written is shorter than this number, 
the result is padded with leading zeros. The value is not truncated even if the result 
is longer. A precision of 0 means that no character is written for the value 0. For e, 
E and f specifiers: this is the number of digits to be printed after the decimal point. 
For g and G specifiers: This is the maximum number of significant digits to be printed. 
For s: this is the maximum number of characters to be printed. By default all characters 
are printed until the ending null character is encountered. For c type: it has no effect. 
When no precision is specified, the default is 1. If the period is specified without an 
explicit value for precision, 0 is assumed.
.* -> The precision is not specified in the format string, but as an additional integer 
value argument preceding the argument that has to be formatted.

Length:
h -> The argument is interpreted as a short int or unsigned short int 
(only applies to integer specifiers: i, d, o, u, x and X).
l -> The argument is interpreted as a long int or unsigned long int for integer specifiers 
(i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s.
L -> The argument is interpreted as a long double (only applies to floating point 
specifiers: e, E, f, g and G).

*/

void fprintf_will_write_formatted_output_to_a_stream(void)
{
    //arrange
    char* fileName = "../bin/fprintf.txt"; 
    remove(fileName); 
    FILE* stream = fopen(fileName, "w+");
    char buffer[100];
    memset(buffer, '\0', 100); 

    //act
    fprintf(stream, "%s %+hd %-3.3f", "Numbers are:", 10, 10.12345); 
    printf("%s %+hd %-3.3f", "Numbers are:", 10, 10.12345); 
    printf("\n"); 
    fprintf(stdout, "%s %+hd %-3.3f", "Numbers are:", 10, 10.12345); 
    //last two lines - should write the same message to standard output. 
    
    //assert
    rewind(stream); 
    fgets(buffer, 100, stream); 
    int result = strcmp("Numbers are: +10 10.123", buffer);
    TEST_ASSERT_EQUAL_INT(0, result); 

    rewind(stream); 
    int d;
    float f; 
    char text1[10];
    char text2[10];
    memset(text1, '\0', 10); 
    memset(text2, '\0', 10); 


    fscanf(stream, "%s %s %d %f", text1, text2, &d, &f); 
    int res1 = strcmp("Numbers", text1);
    int res2 = strcmp("are:", text2); 
    TEST_ASSERT_EQUAL_INT(0, res1);
    TEST_ASSERT_EQUAL_INT(0, res2);
    TEST_ASSERT_EQUAL_INT(10, d);
    TEST_ASSERT_EQUAL_FLOAT(10.123, f); 

    fclose(stream); 
}

/*
As I understand it, the method is used to have variable arguments list in a separate method
*/

void write_formatted(FILE *stream, char *format, ...) {
   va_list args;

   va_start(args, format);
   vfprintf(stream, format, args);
   va_end(args);
   fclose(stream); 
}

void vprintf_should_write_to_output_based_on_variable_arguments(void)
{
    //arrange
    char* fileName = "../bin/vprintf.txt"; 
    remove(fileName); 
    FILE* stream = fopen(fileName, "w+");
    char buffer[100];
    memset(buffer, '\0', 100); 

    //act
    write_formatted(stream, "%s %+hd %-3.3f", "Numbers are:", 10, 10.12345);

    stream = fopen(fileName, "r");
    fgets(buffer, 100, stream); 
    fclose(stream);

    //assert
    int result = strcmp("Numbers are: +10 10.123", buffer); 
    TEST_ASSERT_EQUAL_INT(0, result); 
}

void sprintf_will_write_formatted_output_to_a_char_pointer(void)
{
    //arrange
    char text[100];
    memset(text, '\0', 100);  

    //act
    sprintf(text, "%s %+hd %-3.3f", "Numbers are:", 10, 10.12345); 
    
    //assert
    int d;
    float f; 
    char text1[10];
    char text2[10];
    memset(text1, '\0', 10); 
    memset(text2, '\0', 10); 

    int result = strcmp("Numbers are: +10 10.123", text);
    TEST_ASSERT_EQUAL_INT(0, result); 

    sscanf(text, "%s %s %d %f", text1, text2, &d, &f);
    int res1 = strcmp("Numbers", text1);
    int res2 = strcmp("are:", text2); 
    TEST_ASSERT_EQUAL_INT(0, res1);
    TEST_ASSERT_EQUAL_INT(0, res2);
    TEST_ASSERT_EQUAL_INT(10, d);
    TEST_ASSERT_EQUAL_FLOAT(10.123, f); 
}

void run_formatted_io_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(fprintf_will_write_formatted_output_to_a_stream); 
    RUN_TEST(vprintf_should_write_to_output_based_on_variable_arguments); 
    RUN_TEST(sprintf_will_write_formatted_output_to_a_char_pointer);
    UNITY_END();
}

/*---------------------------------------Character I/O-----------------------------------------------*/

/*
int fgetc(FILE* stream) - Fetches the next character from the given file stream
char* fgets(char* str, int count, FILE* stream) - Fetches a line from the stream. This 
function stops when either “count – 1” characters are read, a newline 
character is reached or the EOF marker is reached.
int fputc(int char, FILE* stream) - Writes a character to the given file stream
int fputs(const char* str, FILE* stream) - Writes a C string to the given stream, excluding the null 
character
int getchar(void) - Fetches a character from standard input
int putchar(int char) - Writes a character to standard output
int ungetc(int char, FILE* stream) - Puts a character back onto the given stream. You can 
think of this as the opposite to ”fgetc”. 
*/

void fgetc_fputc_ungetc_tests(void)
{
    //arrange
    char initialText[20] = "Initial text"; 
    char* fileName = "../bin/fgetc.txt";
    remove(fileName); 
    FILE* stream = fopen(fileName, "w+"); 
    char* ptr1 = &initialText[0]; 

    //act
    while(1)
    {
        if(*ptr1 == '\0')
        {
            break; 
        }
        fputc(*ptr1, stream); 
        ptr1++; 
    }

    char finalText[20];
    memset(finalText, '\0', 20); 
    char* ptr2 = finalText; 
    rewind(stream); 
    while(1)
    {
        *ptr2 = fgetc(stream); 
        if(ptr2[0] == 'I')
        {
            ungetc('!', stream); 
        }
        if(feof(stream))
        {
            *ptr2 = '\0'; 
            break; 
        }
        
        ptr2++; 
    }

    //assert
    int result = strcmp("I!nitial text", finalText);
    TEST_ASSERT_EQUAL_INT(0, result); 

}

void run_character_io_tests(void)
{
    UNITY_BEGIN(); 
    RUN_TEST(fgetc_fputc_ungetc_tests); 
    UNITY_END(); 
}

/*---------------------------------------API FUNCTION-------------------------------------------------*/
void run_stdio_tests(void)
{
    run_file_operations_tests(); 
    run_file_positioning_tests(); 
    run_error_handling_tests(); 
    run_file_io_tests(); 
    run_formatted_io_tests(); 
    run_character_io_tests(); 
}