/* Basic rotation cipher */
#include <stdio.h>

char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char lower[] = "abcdefghijklmnopqrstuvwxyz";

/* Rotate every letter in text by shift places. Other characters stay. */
void rotate(char *text, int shift)
{
    int i;
    int j;

    shift = shift % 26;
    if (shift < 0) {
        shift = shift + 26;
    }

    for (i = 0; text[i] != '\0'; i++) {
        for (j = 0; j < 26; j++) {
            if (text[i] == upper[j]) {
                text[i] = upper[(j + shift) % 26];
                break;
            }
            if (text[i] == lower[j]) {
                text[i] = lower[(j + shift) % 26];
                break;
            }
        }
    }
}

/* Console test only. Skipped when main.c (the menu) includes this file. */
#ifndef MENU_PROGRAM
int main(void)
{
    char text[1000];
    int choice;
    int shift;
    int c;

    printf("1 = Encrypt, 2 = Decrypt: ");
    scanf("%d", &choice);

    printf("How many places to rotate? ");
    scanf("%d", &shift);

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    printf("Text: ");
    fgets(text, 1000, stdin);

    switch (choice) {
    case 1:
        rotate(text, shift);
        break;
    case 2:
        /* times 25 rotates backward by shift places */
        rotate(text, (shift % 26) * 25);
        break;
    default:
        printf("Please choose 1 or 2.\n");
        return 1;
    }

    printf("Result: %s", text);
    return 0;
}
#endif