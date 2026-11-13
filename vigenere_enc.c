/* Vigenere encryption using a circular linked-list key. */
#include "vigenere_common.h"

int vigenere_encrypt(const unsigned char *input, size_t input_len,
                     unsigned char *output, size_t *output_len,
                     const char *key) {
    return vigenere_transform(input, input_len, output, output_len, key, 0);
}
