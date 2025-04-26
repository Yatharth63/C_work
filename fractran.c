#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

// Function to compute the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to multiply an integer by a fraction
int multiply_fraction(int n, Fraction f) {
    int num = n * f.numerator;
    if (num % f.denominator == 0) {
        return num / f.denominator;
    }
    return -1; // Indicate failure to produce an integer
}

// FRACTRAN interpreter
void fractran(int n, Fraction program[], int program_length, int steps) {
    printf("Starting value: %d\n", n);
    for (int i = 0; i < steps; i++) {
        int changed = 0;
        for (int j = 0; j < program_length; j++) {
            int result = multiply_fraction(n, program[j]);
            if (result != -1) {
                n = result;
                printf("Step %d: %d\n", i + 1, n);
                changed = 1;
                break;
            }
        }
        if (!changed) {
            printf("No further fraction could be applied. Stopping.\n");
            break; // Stop if no fraction can be applied
        }
    }
}

int main() {
    int program_length, steps, n;

    // Input the number of fractions in the program
    printf("Enter the number of fractions in the FRACTRAN program: ");
    scanf("%d", &program_length);

    // Allocate memory for the FRACTRAN program
    Fraction *program = malloc(program_length * sizeof(Fraction));
    if (program == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Input the FRACTRAN program
    printf("Enter the fractions (numerator and denominator separated by space):\n");
    for (int i = 0; i < program_length; i++) {
        printf("Fraction %d: ", i + 1);
        scanf("%d %d", &program[i].numerator, &program[i].denominator);
    }

    // Input the initial value
    printf("Enter the initial value: ");
    scanf("%d", &n);

    // Input the number of steps
    printf("Enter the number of steps to execute: ");
    scanf("%d", &steps);

    // Run the FRACTRAN interpreter
    fractran(n, program, program_length, steps);

    // Free allocated memory
    free(program);

    return 0;
}