#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//// AKS-Primality Test
//bool is_prime(int n)
//{
//
//}

bool is_prime(int n)
{
    int d;
    bool isPrime = false;

    for (d = 2; d <= sqrt(n) && (n % d) != 0; ++d) {}

    if ((n % d) != 0 || n == 2) {
        isPrime = true;
    }

    return isPrime;
}

int main(int argc, char *argv[]) {
    FILE *PiDigits = fopen(argv[1], "r");
    if (PiDigits == NULL) {
        fprintf(stderr, "Error loading file.\n");
    }
    FILE *Prime = fopen("prime.txt", "w");
    if (Prime == NULL) {
        fprintf(stderr, "Error loading file.\n");
    }

    int num_digits = 0;
    int prime_ord = 0;
    printf("Please enter the number of digits you would like your prime to be:\n");
    scanf("%d", &num_digits);
    printf("Please enter the which prime you would like to get back (1st, 2nd, ..., nth):\n");
    scanf("%d", &prime_ord);


    char num_string[num_digits+1];
    for (int i = 0; i < num_digits; ++i) {
        num_string[i] = '0';
    }
    num_string[num_digits] = '\0';

    int num = 0;
    int c = 0;
    int filledSlots = 0;
    int num_primes = 0;
    while ((!is_prime(num) || filledSlots < num_digits || num_primes < prime_ord) && c != EOF) {                        /* fill slots in the array first and then check if prime or EOF */
        c = fgetc(PiDigits);
        ++filledSlots;
        for (int i = 0; i < num_digits-1; ++i) {
            num_string[i] = num_string[i+1];
        }
        num_string[num_digits-1] = (char) c;

        num = (int) strtol(num_string, NULL, 10);
        printf("Testing %s...\n", num_string);
        if (is_prime(num) && filledSlots >= num_digits) {++num_primes;}
    }
    printf("%s tested as prime.", num_string);

    fprintf(Prime, num_string);
    fclose(PiDigits); fclose(Prime);

    return 0;
}