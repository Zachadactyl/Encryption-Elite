#ifndef VIGENERE_COMMON_H
#define VIGENERE_COMMON_H
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct vigenere_lock {
    char character;
    struct vigenere_lock *next;
} vigenere_lock;

/* Circular linked-list key, preserving the original implementation's design. */
static void vigenere_free_key(vigenere_lock *first) {
    if (!first) return;
    vigenere_lock *current = first->next;
    while (current != first) {
        vigenere_lock *old = current;
        current = current->next;
        free(old);
    }
    free(first);
}

static int vigenere_ascii_letter(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static unsigned char vigenere_upper(unsigned char c) {
    return (c >= 'a' && c <= 'z') ? (unsigned char)(c - 'a' + 'A') : c;
}

static vigenere_lock *vigenere_make_key(const char *key) {
    if (!key || !*key) return NULL;
    vigenere_lock *first = NULL, *last = NULL;
    for (const unsigned char *p = (const unsigned char *)key; *p; ++p) {
        if (!vigenere_ascii_letter(*p)) {
            if (last) last->next = NULL;
            while (first) {
                vigenere_lock *old = first;
                first = first->next;
                free(old);
            }
            return NULL;
        }
        vigenere_lock *node = malloc(sizeof(*node));
        if (!node) {
            while (first) {
                vigenere_lock *old = first;
                first = first->next;
                free(old);
            }
            return NULL;
        }
        node->character = (char)vigenere_upper(*p);
        node->next = NULL;
        if (last) last->next = node;
        else first = node;
        last = node;
    }
    last->next = first;
    return first;
}

/* 0 success; -1 invalid arguments/key or allocation failure. */
static int vigenere_transform(const unsigned char *input, size_t input_len,
                              unsigned char *output, size_t *output_len,
                              const char *key, int decrypt) {
    if (!input || !output || !output_len) return -1;
    *output_len = 0;
    vigenere_lock *first = vigenere_make_key(key);
    if (!first) return -1;
    vigenere_lock *current = first;
    for (size_t i = 0; i < input_len; ++i) {
        unsigned char c = input[i];
        if (vigenere_ascii_letter(c)) {
            int a = vigenere_upper(c) - 'A';
            int k = current->character - 'A';
            output[i] = (unsigned char)('A' + (decrypt ? (a - k + 26) % 26 : (a + k) % 26));
            current = current->next;
        } else {
            output[i] = c;
        }
    }
    *output_len = input_len;
    vigenere_free_key(first);
    return 0;
}
#endif
