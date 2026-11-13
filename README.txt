Integrated Cipher Menu
======================
Build from this folder:
    gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o cipher_menu
Run:
    ./cipher_menu

Method A: Rotation cipher (original rotationcipher.c)
Method B: Vigenere cipher (circular linked-list key)

main.c includes rotationcipher.c, vigenere_enc.c and vigenere_dec.c,
so compile main.c alone. vigenere_common.h contains the shared key-list
construction, traversal, and cleanup used by the two Vigenere functions.

Method B asks for a key after text has been entered. Keys must contain
letters A-Z only (case insensitive). Output letters are uppercase;
spaces, punctuation, and digits are preserved and do not advance the key.

Note: These classical ciphers are educational, not modern secure encryption.
The original menu's file-status detection is heuristic, not proof that a
file is encrypted. File operations print results but do not save a file.
