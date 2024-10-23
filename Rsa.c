#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Define global variables
int prime_set[100];  // Array to store prime numbers
int public_key, private_key, n;
int prime_count = 0;

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to generate prime numbers using the Sieve of Eratosthenes
void generate_primes() {
    bool sieve[250];
    for (int i = 0; i < 250; i++) {
        sieve[i] = true;
    }
    sieve[0] = sieve[1] = false;  // 0 and 1 are not primes

    for (int i = 2; i < 250; i++) {
        if (sieve[i]) {
            for (int j = i * 2; j < 250; j += i) {
                sieve[j] = false;
            }
        }
    }

    // Add primes to the prime_set array
    for (int i = 0; i < 250; i++) {
        if (sieve[i]) {
            prime_set[prime_count++] = i;
        }
    }
}

// Function to select a random prime from the prime_set and remove it
int select_random_prime() {
    int index = rand() % prime_count;
    int selected_prime = prime_set[index];

    // Remove the selected prime from the array
    for (int i = index; i < prime_count - 1; i++) {
        prime_set[i] = prime_set[i + 1];
    }
    prime_count--;

    return selected_prime;
}

// Function to generate public and private keys
void generate_keys() {
    int prime1 = select_random_prime();
    int prime2 = select_random_prime();
    n = prime1 * prime2;
    int phi = (prime1 - 1) * (prime2 - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    public_key = 2;
    while (gcd(public_key, phi) != 1) {
        public_key++;
    }

    // Calculate the private key d such that (d * e) % phi == 1
    private_key = 2;
    while ((private_key * public_key) % phi != 1) {
        private_key++;
    }
}

// Function to encrypt a message
int encrypt_message(int message) {
    int encrypted_text = 1;
    int e = public_key;

    // Perform modular exponentiation
    while (e > 0) {
        encrypted_text *= message;
        encrypted_text %= n;
        e--;
    }

    return encrypted_text;
}

// Function to decrypt a message
int decrypt_message(int encrypted_text) {
    int decrypted_text = 1;
    int d = private_key;

    // Perform modular exponentiation
    while (d > 0) {
        decrypted_text *= encrypted_text;
        decrypted_text %= n;
        d--;
    }

    return decrypted_text;
}

// Function to encode a message
void encode_message(char* message, int* encoded, int len) {
    for (int i = 0; i < len; i++) {
        encoded[i] = encrypt_message((int)message[i]);
    }
}

// Function to decode a message
void decode_message(int* encoded, char* decoded, int len) {
    for (int i = 0; i < len; i++) {
        decoded[i] = (char)decrypt_message(encoded[i]);
    }
    decoded[len] = '\0';  // Null-terminate the decoded string
}

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Generate prime numbers and keys
    generate_primes();
    generate_keys();

    while (1) {
        printf("RSA Encryption/Decryption\n");
        printf("1: Encrypt Text\n");
        printf("2: Decrypt Text\n");
        printf("3: Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char plaintext[100];
            int encoded[100];

            printf("Enter plaintext: ");
            scanf("%s", plaintext);
            int len = strlen(plaintext);

            encode_message(plaintext, encoded, len);

            printf("RSA ciphertext: ");
            for (int i = 0; i < len; i++) {
                printf("%d ", encoded[i]);
            }
            printf("\n");

        } else if (choice == 2) {
            int ciphertext[100];
            char decrypted[100];
            int len;

            printf("Enter the number of ciphertext elements: ");
            scanf("%d", &len);

            printf("Enter ciphertext (space-separated integers): ");
            for (int i = 0; i < len; i++) {
                scanf("%d", &ciphertext[i]);
            }

            decode_message(ciphertext, decrypted, len);
            printf("RSA plaintext: %s\n", decrypted);

        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}
