/*
 * Authors: Adam Laboissonniere - laboissa@bc.edu, Brian Laboissonniere - laboissb@bc.edu
*/
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

unsigned char ones(unsigned char input) {
    unsigned char count = 0;
    while (input) {
        count += input & 1;
        input >>= 1;
    }
    return count;
}

unsigned char rotate(unsigned char plain, const unsigned char count) {
    unsigned char cipher = 0;
    for (int pos = 0; pos < ASCII_BITS; ++pos, plain >>= 1) {
      cipher |= ((plain & 1) << ((pos + count) % ASCII_BITS));
  }
    return cipher;
}

unsigned int encode_chars(const unsigned char * const plain_chars) {
    unsigned int encoded = 0;

    for (int i = 0; i < CHARS_PER_INT; ++i) {
        unsigned char plain_char = plain_chars[i];
        unsigned char count = ones(plain_char) & COUNT_MASK;
        unsigned char rotated_char = rotate(plain_char, count) & ASCII_MASK;
        encoded |= (count << (i * COUNT_BITS));
        encoded |= (rotated_char << (9 + i * ASCII_BITS));
    }

    return encoded & (COUNTS_MASK | (ASCII_MASK << 9) | (ASCII_MASK << 16) | (ASCII_MASK << 23));
}

void encode_file(const char * const input_file, const char * const output_file) {
    FILE * in = fopen_checked(input_file, "r");
    FILE * out = fopen_checked(output_file, "wb");
    unsigned char plain_chars[CHARS_PER_INT];
    int char_count = 0;
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        plain_chars[char_count++] = (unsigned char)ch;
        if (char_count == CHARS_PER_INT) {
            unsigned int encoded = encode_chars(plain_chars);
            fwrite(&encoded, sizeof(unsigned int), 1, out);
            char_count = 0;
        }
    }
    if (char_count > 0) {
        for (int i = char_count; i < CHARS_PER_INT; i++) {
            plain_chars[i] = 0;
        }
        unsigned int encoded = encode_chars(plain_chars);
        fwrite(&encoded, sizeof(unsigned int), 1, out);
    }
    fclose(in);
    fclose(out);
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input-plaintext-file> <output-ciphertext-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char * input_file = argv[1];
    const char * output_file = argv[2];
    encode_file(input_file, output_file);
    return EXIT_SUCCESS;
}
