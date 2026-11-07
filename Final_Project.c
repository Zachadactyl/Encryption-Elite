#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================================================================
 * CONFIGURATION & DYNAMIC NAMES FOR TEAMMATES
 * Change these names here, and the entire menu updates automatically!
 * ========================================================================= */
#define METHOD_A_NAME "Message Encryption (Symmetric)"
#define METHOD_B_NAME "Key Wrapping (Asymmetric)"

/* =========================================================================
 * STUB FUNCTIONS FOR TEAMMATES TO IMPLEMENT
 * Teammates can replace these blocks with their libsodium implementations.
 * ========================================================================= */

int encrypt_method_a(const unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len) {
    // TODO: Teammate pastes implementation here
    printf("[STUB] Executing Method A (" METHOD_A_NAME ")...\n");
    if (output && input) {
        memcpy(output, input, input_len);
        for(size_t i = 0; i < input_len; i++) output[i] ^= 0x55; // Dummy cipher mock
        *output_len = input_len;
    }
    return 0; 
}

int encrypt_method_b(const unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len) {
    // TODO: Teammate pastes implementation here
    printf("[STUB] Executing Method B (" METHOD_B_NAME ")...\n");
    if (output && input) {
        memcpy(output, input, input_len);
        *output_len = input_len;
    }
    return 0;
}

int decrypt_method_a(const unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len) {
    // TODO: Teammate pastes implementation here
    printf("[STUB] Executing Decryption via Method A...\n");
    if (output && input) {
        memcpy(output, input, input_len);
        for(size_t i = 0; i < input_len; i++) output[i] ^= 0x55; // Reverse dummy cipher mock
        *output_len = input_len;
    }
    return 0;
}

int decrypt_method_b(const unsigned char *input, size_t input_len, unsigned char *output, size_t *output_len) {
    // TODO: Teammate pastes implementation here
    printf("[STUB] Executing Decryption via Method B...\n");
    if (output && input) {
        memcpy(output, input, input_len);
        *output_len = input_len;
    }
    return 0;
}

/* =========================================================================
 * HELPER UTILITIES
 * ========================================================================= */

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int is_plaintext(const unsigned char *data, size_t len) {
    size_t printable_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (isprint(data[i]) || data[i] == '\n' || data[i] == '\r' || data[i] == '\t') {
            printable_count++;
        }
    }
    if (len == 0) return 1;
    return ((double)printable_count / len) >= 0.90;
}

/* =========================================================================
 * OPTION 1 & 2 HANDLERS (Manual Input with Spaces & Special Characters)
 * ========================================================================= */

void handle_manual_encrypt() {
    char sub_choice;
    char input_text[1024];

    while (1) {
        printf("\n--- Encrypt Submenu ---\n");
        printf("  a. %s\n", METHOD_A_NAME);
        printf("  b. %s\n", METHOD_B_NAME);
        printf("  c. Return to Main Menu\n");
        printf("Select sub-option (a/b/c): ");
        
        scanf(" %c", &sub_choice);
        clear_input_buffer();

        if (sub_choice == 'c' || sub_choice == 'C') {
            break; // Return to main menu
        }

        if (sub_choice != 'a' && sub_choice != 'A' && sub_choice != 'b' && sub_choice != 'B') {
            printf("Invalid sub-option. Please choose a, b, or c.\n");
            continue; // Keep the selection menu open
        }

        printf("Enter the text to encrypt (spaces and special characters allowed):\n> ");
        if (fgets(input_text, sizeof(input_text), stdin) != NULL) {
            // Remove trailing newline if present
            input_text[strcspn(input_text, "\r\n")] = 0;
        }

        unsigned char out_buffer[2048];
        size_t out_len = 0;

        if (sub_choice == 'a' || sub_choice == 'A') {
            encrypt_method_a((unsigned char *)input_text, strlen(input_text), out_buffer, &out_len);
        } else {
            encrypt_method_b((unsigned char *)input_text, strlen(input_text), out_buffer, &out_len);
        }

        printf("\n[Result] Encrypted Output (Hex):\n");
        for (size_t i = 0; i < out_len; i++) {
            printf("%02x ", out_buffer[i]);
        }
        printf("\n-------------------------\n");
    }
}

void handle_manual_decrypt() {
    char sub_choice;
    char input_text[1024];

    while (1) {
        printf("\n--- Decrypt Submenu ---\n");
        printf("  a. Decrypt via %s\n", METHOD_A_NAME);
        printf("  b. Decrypt via %s\n", METHOD_B_NAME);
        printf("  c. Return to Main Menu\n");
        printf("Select sub-option (a/b/c): ");
        
        scanf(" %c", &sub_choice);
        clear_input_buffer();

        if (sub_choice == 'c' || sub_choice == 'C') {
            break;
        }

        if (sub_choice != 'a' && sub_choice != 'A' && sub_choice != 'b' && sub_choice != 'B') {
            printf("Invalid sub-option. Please choose a, b, or c.\n");
            continue; // Keep submenu open
        }

        printf("Enter the ciphertext input string:\n> ");
        if (fgets(input_text, sizeof(input_text), stdin) != NULL) {
            input_text[strcspn(input_text, "\r\n")] = 0;
        }

        unsigned char out_buffer[2048];
        size_t out_len = 0;

        if (sub_choice == 'a' || sub_choice == 'A') {
            decrypt_method_a((unsigned char *)input_text, strlen(input_text), out_buffer, &out_len);
        } else {
            decrypt_method_b((unsigned char *)input_text, strlen(input_text), out_buffer, &out_len);
        }

        printf("\n[Result] Decrypted Output:\n");
        for (size_t i = 0; i < out_len; i++) {
            putchar(out_buffer[i]);
        }
        printf("\n-------------------------\n");
    }
}

/* =========================================================================
 * OPTION 3: OPEN FILE WORKFLOW WITH METHOD SELECTION
 * ========================================================================= */

void handle_open_file() {
    char filename[256];
    printf("\nEnter the path of the file to open: ");
    if (scanf("%255s", filename) != 1) {
        printf("Error reading input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Could not open file: %s (Make sure it exists locally)\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        printf("File is empty or unreadable.\n");
        fclose(file);
        return;
    }

    unsigned char *buffer = malloc(file_size);
    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    int text_is_plain = is_plaintext(buffer, bytes_read);
    printf("\n[File Analysis] Status: %s\n", text_is_plain ? "Plaintext detected" : "Already encrypted / Binary detected");

    int action_choice;
    printf("\nChoose an action for this file:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Select option (1-2): ");
    if (scanf("%d", &action_choice) != 1) {
        printf("Invalid choice.\n");
        clear_input_buffer();
        free(buffer);
        return;
    }
    clear_input_buffer();

    if (action_choice == 1) {
        if (!text_is_plain) {
            printf("[ERROR] File appears to be already encrypted! Cannot encrypt encrypted data again.\n");
            free(buffer);
            return;
        }
    } else if (action_choice == 2) {
        if (text_is_plain) {
            printf("[ERROR] File appears to be plaintext! Cannot decrypt plain text files.\n");
            free(buffer);
            return;
        }
    } else {
        printf("Invalid action selected.\n");
        free(buffer);
        return;
    }

    // Now select via which method (a or b)
    char method_choice;
    printf("\nSelect processing method:\n");
    printf("  a. %s\n", METHOD_A_NAME);
    printf("  b. %s\n", METHOD_B_NAME);
    printf("Select option (a/b): ");
    scanf(" %c", &method_choice);
    clear_input_buffer();

    unsigned char out_buffer[4096];
    size_t out_len = 0;

    if (action_choice == 1) {
        if (method_choice == 'a' || method_choice == 'A') {
            encrypt_method_a(buffer, bytes_read, out_buffer, &out_len);
        } else {
            encrypt_method_b(buffer, bytes_read, out_buffer, &out_len);
        }
        printf("\n--- File Encryption Result (Hex) ---\n");
        for(size_t i = 0; i < out_len; i++) printf("%02x ", out_buffer[i]);
        printf("\n------------------------------------\n");
    } else {
        if (method_choice == 'a' || method_choice == 'A') {
            decrypt_method_a(buffer, bytes_read, out_buffer, &out_len);
        } else {
            decrypt_method_b(buffer, bytes_read, out_buffer, &out_len);
        }
        printf("\n--- File Decryption Result ---\n");
        for(size_t i = 0; i < out_len; i++) putchar(out_buffer[i]);
        printf("\n------------------------------\n");
    }

    free(buffer);
}

void show_help() {
    printf("\n============================================================\n");
    printf("                     HELP / HOW-TO GUIDE                    \n");
    printf("============================================================\n");
    printf(" 1. Encrypt: Enter text containing spaces/special characters\n");
    printf("    and select method A (%s) or B (%s).\n", METHOD_A_NAME, METHOD_B_NAME);
    printf(" 2. Decrypt: Input ciphertext and reverse via method A or B.\n");
    printf(" 3. Open file: Load a file, validate its encryption status,\n");
    printf("    choose action, and pick which method to run.\n");
    printf(" 4. Help/How to: Display this guide.\n");
    printf(" 5. Exit: Quit the program.\n");
    printf("============================================================\n");
}

/* =========================================================================
 * MAIN MENU LOOP
 * ========================================================================= */

int main() {
    int choice;

    do {
        printf("\n================ ENVELOPE ENCRYPTION TOOL ================\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Open file\n");
        printf("4. Help/How to\n");
        printf("5. Exit\n");
        printf("Select an option (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                handle_manual_encrypt();
                break;
            case 2:
                handle_manual_decrypt();
                break;
            case 3:
                handle_open_file();
                break;
            case 4:
                show_help();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 5.\n");
        }

    } while (choice != 5);

    return 0;
}