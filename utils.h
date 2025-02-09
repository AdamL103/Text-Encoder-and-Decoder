#include <stdio.h>
#include <stdlib.h>

#define ASCII_BITS 7
#define ASCII_MASK ((1 << ASCII_BITS) - 1)
#define COUNT_BITS 3
#define COUNT_MASK ((1 << COUNT_BITS) - 1)
#define COUNTS_MASK ((1 << (3 * COUNT_BITS)) - 1)
#define CHARS_PER_INT 3

FILE * fopen_checked(const char * filename, const char * mode);
