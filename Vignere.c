#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the repeating key
void generate_key(char *msg, char *key, char *new_key) {
    int msg_len = strlen(msg);
    int key_len = strlen(key);

    for (int i = 0; i < msg_len; i++) {
        new_key[i] = key[i % key_len];
    }
    new_key[msg_len] = '\0';  // Null-terminate the new key
}

// Function to encrypt the message using Vigenère cipher
void encrypt_vigenere(char *msg, char *key, char *encrypted_text) {
    char new_key[100];
    generate_key(msg, key, new_key);

    for (int i = 0; i < strlen(msg); i++) {
        char ch = msg[i];
        if (isupper(ch)) {
            encrypted_text[i] = (ch + new_key[i] - 2 * 'A') % 26 + 'A';
        } else if (islower(ch)) {
            encrypted_text[i] = (ch + new_key[i] - 2 * 'a') % 26 + 'a';
        } else {
            encrypted_text[i] = ch;  // If not an alphabet, leave unchanged
        }
    }
    encrypted_text[strlen(msg)] = '\0';  // Null-terminate the encrypted text
}

// Function to decrypt the message using Vigenère cipher
void decrypt_vigenere(char *msg, char *key, char *decrypted_text) {
    char new_key[100];
    generate_key(msg, key, new_key);

    for (int i = 0; i < strlen(msg); i++) {
        char ch = msg[i];
        if (isupper(ch)) {
            decrypted_text[i] = (ch - new_key[i] + 26) % 26 + 'A';
        } else if (islower(ch)) {
            decrypted_text[i] = (ch - new_key[i] + 26) % 26 + 'a';
        } else {
            decrypted_text[i] = ch;  // If not an alphabet, leave unchanged
        }
    }
    decrypted_text[strlen(msg)] = '\0';  // Null-terminate the decrypted text
}

int main() {
    char text_to_encrypt[] = "ADITYA";
    char key[] = "KEY";

    char encrypted_text[100];
    char decrypted_text[100];

    encrypt_vigenere(text_to_encrypt, key, encrypted_text);
    printf("Encrypted Text: %s\n", encrypted_text);

    decrypt_vigenere(encrypted_text, key, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}
