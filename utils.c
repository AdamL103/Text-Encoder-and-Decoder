/*
 * Authors: Adam Laboissonniere - laboissa@bc.edu, Brian Laboissonniere - laboissb@bc.edu
*/
#include "utils.h"

FILE * fopen_checked(const char * filename, const char * mode) {
    FILE * file = fopen(filename, mode);
    if (!file) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    return file;
}
