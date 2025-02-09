/*
 * Authors: Adam Laboissonniere - laboissa@bc.edu, Brian Laboissonniere - laboissb@bc.edu
*/
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void decode_chars(unsigned int input, unsigned char * const plain_chars) {
    for (int i = 0; i < CHARS_PER_INT; ++i) {
        unsigned char count = (input >> (i * COUNT_BITS)) & COUNT_MASK;
        unsigned char rotated_char = (input >> (9 + i * ASCII_BITS)) & ASCII_MASK;
        plain_chars[i] = ((rotated_char >> count) | (rotated_char << (ASCII_BITS - count))) & ASCII_MASK;
    }
}

void decode_file(const char * const input_file, const char * const output_file) {
    FILE * in = fopen(input_file, "rb");
    FILE * out = fopen(output_file, "w");
    unsigned char plain_chars[CHARS_PER_INT] = {0};
    unsigned int encoded;
    while (fread(&encoded, sizeof(unsigned int), 1, in) == 1) {
        decode_chars(encoded, plain_chars);
        for (int i = 0; i < CHARS_PER_INT; ++i) {
            if (plain_chars[i] != 0) {
                fputc(plain_chars[i], out);
            }
        }
    }
    fclose(in);
    fclose(out);
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input-ciphertext-file> <output-plaintext-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char * input_file = argv[1];
    const char * output_file = argv[2];
    decode_file(input_file, output_file);
    return EXIT_SUCCESS;
}
