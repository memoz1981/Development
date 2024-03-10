#include "helper.h"

void copyArray(char* to, char* from, int size)
{
    char * fromCopy = from; 
    char * toCopy = to; 
    for(int i=0; i<size; i++)
    {
        fromCopy = from + i * sizeof(char); 
        toCopy = to + i * sizeof(char); 

        *toCopy = *fromCopy; 
    }
}