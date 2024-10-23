#include <stdio.h>
#include <string.h>

// Function to find the position of a character in the matrix
void findPosition(char matrix[5][5], char ch, int *row, int *col) {
    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (matrix[*row][*col] == ch) {
                return;
            }
        }
    }
}

// Function to encrypt using Playfair cipher
void encryptPlayfair(char matrix[5][5], char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int i, row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Use 'X' if the second character is missing

        if (a == b) {
            b = 'X'; // Replace duplicate letters
        }

        findPosition(matrix, a, &row1, &col1);
        findPosition(matrix, b, &row2, &col2);

        if (row1 == row2) {
            // Same row
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            // Same column
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else {
            // Rectangle
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt using Playfair cipher
void decryptPlayfair(char matrix[5][5], char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int i, row1, col1, row2, col2;

    for (i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = ciphertext[i + 1];

        findPosition(matrix, a, &row1, &col1);
        findPosition(matrix, b, &row2, &col2);

        if (row1 == row2) {
            // Same row
            plaintext[i] = matrix[row1][(col1 - 1 + 5) % 5];
            plaintext[i + 1] = matrix[row2][(col2 - 1 + 5) % 5];
        } else if (col1 == col2) {
            // Same column
            plaintext[i] = matrix[(row1 - 1 + 5) % 5][col1];
            plaintext[i + 1] = matrix[(row2 - 1 + 5) % 5][col2];
        } else {
            // Rectangle
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char matrix[5][5] = {
        {'C', 'L', 'O', 'N', 'E'},
        {'A', 'B', 'D', 'F', 'G'},
        {'H', 'I', 'K', 'M', 'P'},
        {'Q', 'R', 'S', 'T', 'U'},
        {'V', 'W', 'X', 'Y', 'Z'}
    };

    char plaintext[] = "ADITYA";
    char ciphertext[50];
    char decryptedText[50];

    // Print matrix
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // Encrypt and display ciphertext
    encryptPlayfair(matrix, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt and display plaintext
    decryptPlayfair(matrix, ciphertext, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
