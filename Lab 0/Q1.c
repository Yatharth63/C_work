#include <stdio.h>


int fac(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 1;
    }
    else {
        return n * fac(n - 1);
    }
}

int main()
{
    int number;
    printf("enter a number:");
    scanf("%d", &number);

    if (number < 0) 
    {
        printf("Factorial is not defined for negative numbers.\n");
    } 
    else 
    {
        printf("Factorial of %d is: %llu\n", number, fac(number));
    }


    return 0;
}